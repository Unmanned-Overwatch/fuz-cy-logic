/*------------------------------------------------------------*



/*-------------------Procedure Description--------------------*
| fshprc1.cpp   Earl Cox  04/03/93  The Pricing Model         |
| This is the main driver routine that invokes the stand-alone|
| fuzzy pricing model. This pricing model is an example of    |
| how the basic (low level) fuzzy modelling facilities can be |
| used to implement an actual commerical application.         |
|                                                             |
|   salesMargin   = price-directCost                          |
|   grossSales    = volumne*price                             |
|   grossProfit   = salesMargin*volume                        |
|                                                             |
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
static char *Month[]=
 {
  "Jan","Feb","Mar","Apr","May","Jun",
  "Jul","Aug","Sep","Oct","Nov","Dec"
 };
static int MaxMonths=12;
static double competitionPrice[]=
 {
   16.25,16.50,16.75,18.50,18.75,21.25,
   22.00,24.50,26.75,28.25,30.50,31.75
 };
static double directCosts[]=
 {
  8.25, 8.50, 8.75, 9.00, 9.25, 9.50,
  9.75,10.00,10.25,10.50,10.75,11.00
 };
extern unsigned _stklen=50000;
double fshpr5policy(const char**,double,double,float*,int*);
double SVolpolicy(double,float*,int*);
void main(void)
 {
  PDB     *prcPDBptr;
  FDB     *FDBptr[FDBvecmax],*svFDBptr;
  VDB     *VDBptr;
  int      i,status,FDBcnt,Hdgcnt,TryCtl[2];
  float    compidx[12],cindex;
  double   compprice,Price[12],mfgcosts;
  double   salesMargin[12],grossSales[12],grossProfit[12];
  double   TwiceMfgCosts,salesVolume[12];
  double   Domain[2],Parms[4];
  FILE    *mdlout;

  MdlConnecttoFMS(&status);
  prcPDBptr=MdlCreatePolicy("PRICING",MODELADD,&status);
  XSYSctl.XSYScurrPDBptr=prcPDBptr;
  MdlInsertHedges(prcPDBptr,&Hdgcnt,&status);
  mdlout=MtsGetSystemFile(SYSMODFILE);
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
  FzyPlotVar("PRICE",FDBptr,FDBcnt,SYSMODFILE,&status);
//
//--Create an empty fuzzy set as a working area
  FDBptr[0]=FzyCreateSet("NULL",EMPTYSET,Domain,Parms,0,&status);
  MdlLinkFDB(FDBptr[0],prcPDBptr,&status);
//
  Domain[0]=0;Domain[1]=100;
  svFDBptr=FzyCreateSet("HIGH.VOLUME",INCREASE,Domain,Parms,0,&status);
  strcpy(svFDBptr->FDBdesc,"High Sales Volumes");
  FzyDrawSet(svFDBptr,SYSMODFILE,&status);
  MdlLinkFDB(svFDBptr,prcPDBptr,&status);
//
//--Display the rules on the model log and invoke the policy
//
fprintf(mdlout,"%s\n",
  "Fuzzy Pricing Model. (c) 1992 Metus Systems Group.");
fprintf(mdlout,"%s%10.2f\n",
  "[Mean] Competition Price: ",compprice);
fprintf(mdlout,"%s%10.2f\n",
  "Base Manufacturing Costs: ",mfgcosts );
//
  fprintf(mdlout,"%s\n","The Rules:");
  for(i=0;i<Rulemax;i++) fprintf(mdlout,"%s\n",Rules[i]);
  fputc('\n',mdlout);

  for(i=0;i<MaxMonths;i++)
    {
     compprice=competitionPrice[i];
     mfgcosts=directCosts[i];
     fprintf(stdout,"%s%s\n","---calling policy for month: ",Month[i]);
     Price[i]=fshpr5policy(Rules,mfgcosts,compprice,&cindex,&status);
     compidx[i]=cindex;
     salesVolume[i]=SVolpolicy(Price[i],&cindex,&status);
     fprintf(stdout,"%s%10.3f\n","Price       = ",Price[i]);
     fprintf(stdout,"%s%10.3f\n","SalesVolume = ",salesVolume[i]);
     salesMargin[i]=Price[i]-directCosts[i];
     grossSales[i]=salesVolume[i]*Price[i];
     grossProfit[i]=salesMargin[i]*salesVolume[i];
    }
  fprintf(stdout,"\f\n%s\n%s\n%s\n",
   "            Our     Mfg     Sales    Gross    Gross    Comp.        ",
   "    Volume  Price   Cost    Margin   Sales    Profit   Price   UCIdx",
   "--- ------  ------  ------  -------  -------  -------  ------  -----");

  for(i=0;i<MaxMonths;i++)
    {
     fprintf(stdout,"%3.3s%s%6.2f%s%6.2f%s%6.2f%s%7.2f%s%7.2f%s",
      Month[i],           " ",
      salesVolume[i],     "  ",
      Price[i],           "  ",
      directCosts[i],     "  ",
      salesMargin[i],     "  ",
      grossSales[i],      "  ");
     fprintf(stdout,"%7.2f%s%6.2f%s%5.3f\n",
      grossProfit[i],     "  ",
      competitionPrice[i],"  ",
      compidx[i]);
    }
  return;
 }
//===================================================================
double SVolpolicy(double Price,float *CIX,int *statusPtr)
 {
  PDB     *prcPDBptr;
  FDB     *svFDBptr,*LoFDBptr,*FDBptr[2];
  int      FDBcnt,Valcnt;
  double   volume,Values[2];
  float    PremiseTruth;
  FILE    *mdlout;

  *statusPtr=0;
  prcPDBptr=XSYSctl.XSYScurrPDBptr;
  mdlout=MtsGetSystemFile(SYSMODFILE);
  fprintf(mdlout,"%s\n","Sales Volume Estimate Policy Begins....");
//
//--Find the fuzzy sets in the policy dictionary
//
  svFDBptr=MdlFindFDB("HIGH.VOLUME",    prcPDBptr,statusPtr);
  LoFDBptr=MdlFindFDB("LOW",            prcPDBptr,statusPtr);
//
//--if price is low then sales volume is high
//
  volume=FzyMonotonicLogic(
      LoFDBptr,svFDBptr,Price,&PremiseTruth,statusPtr);
  Values[0]=Price; Valcnt=1;
  FzyImplMatrix(LoFDBptr,svFDBptr,Values,Valcnt,statusPtr);
  return(volume);
 }
