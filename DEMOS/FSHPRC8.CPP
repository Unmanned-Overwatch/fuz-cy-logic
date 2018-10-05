/*------------------------------------------------------------*



/*-------------------Procedure Description--------------------*
| fshprc8.cpp   Earl Cox  04/03/93  The Pricing Model         |
| This is the main driver routine that invokes the stand-alone|
| fuzzy pricing model. This pricing model is an example of    |
| how the basic (low level) fuzzy modelling facilities can be |
| used to implement an actual commerical application.         |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "PDB.hpp"
#include <fdb.hpp>
#include "SFZYctl.hpp"
#include "SSYSctl.hpp"
#include   <fuzzy.hpp>
#include   <mtypes.hpp>
#include <mtsptype.hpp>
//
//--These are the "logical" rules. In the high level fuzzy modelling
//--system we would enter these rules exactly as shown.
static const char *Rules[]=
 {
  "R1   our price must be high",
  "R2   our price must be low",
  "R3   our price must be around 2*mfgcosts",
  "R4   if the competition.price is not very high",
  "        then our price must be around the competition.price"
 };
static const Rulemax=5;
static int MaxMonths=12;
static double CompetitionPrice[]=
 {
   25.75,
   26.00,
   26.25,
   26.50,
   26.75,
   27.00,
   27.25,
   27.50,
   27.75,
   28.00,
   28.25,
   28.50
 };
extern unsigned _stklen=50000;
void fshpr8policy(const char**,double,double[],float[],int,int*);
void main(void)
 {
  PDB     *prcPDBptr;
  FDB     *FDBptr[FDBvecmax];
  VDB     *VDBptr;
  int      i,j,status,FDBcnt,Hdgcnt,TryCtl[2];
  float    CIX[2],maxCIX[12],cenCIX[12],cindex;
  double   compprice,Price[2],maxPrice[12],cenPrice[12],mfgcosts=12.00;
  double   Domain[2],Parms[4];
  FILE    *sysout;

  MdlConnecttoFMS(&status);
  prcPDBptr=MdlCreatePolicy("PRICING",MODELADD,&status);
  XSYSctl.XSYScurrPDBptr=prcPDBptr;
  MdlInsertHedges(prcPDBptr,&Hdgcnt,&status);
  sysout=MtsGetSystemFile(SYSLOGFILE);
//
//--create and insert the control variable
//
  Domain[0]=16;
  Domain[1]=36;
  VDBptr=VarCreateScalar("PRICE",REAL,Domain,"0",&status);
  MdlLinkVDB(VDBptr,prcPDBptr,&status);
//
//--Create the basic fuzzy sets (High and Low for Price)
//
  FDBptr[0]=FzyCreateSet("HIGH",INCREASE,Domain,Parms,0,&status);
  strcpy(FDBptr[0]->FDBdesc,"High for Price");
  MdlLinkFDB(FDBptr[0],prcPDBptr,&status);
  FDBptr[1]=FzyCreateSet("LOW", DECREASE,Domain,Parms,0,&status);
  strcpy(FDBptr[1]->FDBdesc,"Low for Price");
  MdlLinkFDB(FDBptr[1],prcPDBptr,&status);
  FDBcnt=2;
//FzyPlotVar("PRICE",FDBptr,FDBcnt,SYSMODFILE,&status);
//--Create an empty fuzzy set as a working area
  FDBptr[0]=FzyCreateSet("NULL",EMPTYSET,Domain,Parms,0,&status);
  MdlLinkFDB(FDBptr[0],prcPDBptr,&status);
//
//--Display the rules on the model log and invoke the policy
//
fprintf(sysout,"%s\n",
  "Fuzzy Pricing Model. (c) 1992 Metus Systems Group.");
//
  fprintf(sysout,"%s\n","The Rules:");
  for(i=0;i<Rulemax;i++) fprintf(sysout,"%s\n",Rules[i]);
  for(i=0;i<MaxMonths;i++)
    {
     cenPrice[i]=0;  cenCIX[i]=0;
     maxPrice[i]=0;  maxCIX[i]=0;
     for(j=0;j<2;j++)
        {
         Price[j]=0;
         CIX[j]  =0;
        }
     compprice=CompetitionPrice[i];
     fprintf(sysout,"%s%10.2f\n","[Mean] Competition Price: ",compprice);
     fprintf(sysout,"%s%10.2f\n","Base Manufacturing Costs: ",mfgcosts );
     fshpr8policy(Rules,compprice,Price,CIX,i,&status);
     cenPrice[i]=Price[0]; cenCIX[i]=CIX[0];
     maxPrice[i]=Price[1]; maxCIX[i]=CIX[1];
    }
  fputc('\n',sysout);
  fprintf(sysout,"\f\n%s\n%s\n%s\n",
   "        Comp.     ------CENTROID------   -------MAXIMUM--------",
   "No.     Price     Price       CIX         Price       CIX      ",
   "---     -------   ---------   ---------   ---------   ---------");
  for(i=0;i<MaxMonths;i++)
    {
      fprintf(sysout,"%2d.     %7.2f   %9.2f   %9.3f   %9.2f   %9.3f\n",
       i+1,CompetitionPrice[i],
       cenPrice[i],cenCIX[i],maxPrice[i],maxCIX[i]);
     }

  fprintf(sysout,"\f\n%s\n%s\n%s\n",
   "        Comp.     Centroid   Maximum                           ",
   "No.     Price     Price       Price       Diff                 ",
   "---     -------   ---------   ---------   ---------            ");
  for(i=0;i<MaxMonths;i++)
    {
      fprintf(sysout,"%2d.     %7.2f   %9.2f   %9.2f   %9.2f\n",
       i+1,CompetitionPrice[i],
       cenPrice[i],maxPrice[i],(cenPrice[i]-maxPrice[i]));
     }
  return;
 }
