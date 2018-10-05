/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| fshprc1.cpp   Earl Cox  04/01/93  The Pricing Model         |
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
#include "FDB.hpp"
#include "SFZYctl.hpp"
#include "SSYSctl.hpp"
#include "fuzzy.hpp"
#include "mtypes.hpp"
#include "mtsptype.hpp"
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
extern unsigned _stklen=50000;
double fshpr1policy(const char**,double,double,float*,int*);
void main(void)
 {
  PDB     *prcPDBptr;
  FDB     *FDBptr[FDBvecmax];
  VDB     *VDBptr;
  int      i,status,FDBcnt,Hdgcnt,TryCtl[2];
  float    compidx;
  double   TwiceMfgCosts,mfgcosts=0,compprice=0,Price;
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
//--Create an empty fuzzy set as a working area
  FDBptr[0]=FzyCreateSet("NULL",EMPTYSET,Domain,Parms,0,&status);
  MdlLinkFDB(FDBptr[0],prcPDBptr,&status);
//
//--Prompt for the model Data
//
  TryCtl[0]=8;
  TryCtl[1]=0;

  Domain[0]=8;Domain[1]=16;
  mfgcosts=MtsAskforDBL(
    "mfgcosts",
    "Enter the Manufacturing Costs:",
    Domain,TryCtl,&status);
  if(status!=0) return;
  Domain[0]=16;Domain[1]=36;
  compprice=MtsAskforDBL(
    "compprice",
    "Enter the Competition's Price:",
    Domain,TryCtl,&status);
  if(status!=0) return;
//
//--Now create the fuzzy number for around 2*mfgcosts
//
  Domain[0]=16;Domain[1]=36;
  TwiceMfgCosts=2*mfgcosts;
  Parms[0]=TwiceMfgCosts;
  Parms[1]=TwiceMfgCosts*.25;
  FDBptr[0]=FzyCreateSet("Near.2*MfgCosts",PI,Domain,Parms,2,&status);
  strcpy(FDBptr[0]->FDBdesc,"Near (Around) Twice MfgCosts");
  MdlLinkFDB(FDBptr[0],prcPDBptr,&status);
  FzyDrawSet(FDBptr[0],SYSMODFILE,&status);
  FDBcnt++;
//
//--Now create the fuzzy number for around compprice
  Parms[0]=compprice;
  Parms[1]=compprice*.15;
  FDBptr[0]=FzyCreateSet("Near.CompPrice",PI,Domain,Parms,2,&status);
  strcpy(FDBptr[0]->FDBdesc,"Near (Around) Competition Price");
  MdlLinkFDB(FDBptr[0],prcPDBptr,&status);
  FzyDrawSet(FDBptr[0],SYSMODFILE,&status);
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
  Price=fshpr1policy(Rules,mfgcosts,compprice,&compidx,&status);
  fprintf(stdout,"\n\n\n%s%8.2f%s%8.3f\n",
   "The Recommended Price is: ",Price," with CompIdx of ",compidx);
  return;
 }
