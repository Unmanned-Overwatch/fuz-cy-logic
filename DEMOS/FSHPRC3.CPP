/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| fshprc3.cpp   Earl Cox  04/01/93  The Pricing Model         |
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
#include <math.h>
#include "PDB.hpp"
#include <FuzzysetDescriptor.hpp>
#include "SFZYctl.hpp"
#include "SSYSctl.hpp"
#include   <fuzzy.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
//
//--These are the "logical" rules. In the high level fuzzy modelling
//--system we would enter these rules exactly as shown.
static const char *Rules[]=
 {
  "R1   our price must be very high",
  "R2   our price must be somewhat low",
  "R3   our price must be above around 2*mfgcosts",
  "R4   if the competition.price is not very low",
  "        then our price must be around the competition.price"
 };
static const Rulemax=5;
extern unsigned _stklen=50000;
double fshpr3policy(const char**,double,double,float*,int*);
void main(void)
 {
  PDB     *prcPDBptr;
  FuzzysetDescriptor     *FuzzysetDescriptorptr[FuzzysetDescriptorvecmax],*wrkFuzzysetDescriptorptr;
  HDB     *vryHDBptr;
  VariableDescriptor     *VariableDescriptorptr;
  int      i,status,FuzzysetDescriptorcnt,Hdgcnt,TryCtl[2];
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
  VariableDescriptorptr=VarCreateScalar("PRICE",REAL,Domain,"0",&status);
  MdlLinkVariableDescriptor(VariableDescriptorptr,prcPDBptr,&status);
//
//--Create the basic fuzzy sets (very High and somewhat Low for Price)
//
  FuzzysetDescriptorptr[0]=FzyCreateSet("VERY.HIGH",INCREASE,Domain,Parms,0,&status);
  strcpy(FuzzysetDescriptorptr[0]->FuzzysetDescriptordesc,"Very High for Price");
  for(i=0;i<VECMAX;i++)
   FuzzysetDescriptorptr[0]->FuzzysetDescriptorvector[i]=(float)pow(FuzzysetDescriptorptr[0]->FuzzysetDescriptorvector[i],2);
  MdlLinkFuzzysetDescriptor(FuzzysetDescriptorptr[0],prcPDBptr,&status);

  FuzzysetDescriptorptr[1]=FzyCreateSet("SOMEWHAT.LOW", DECREASE,Domain,Parms,0,&status);
  strcpy(FuzzysetDescriptorptr[1]->FuzzysetDescriptordesc,"Somewhat Low for Price");
  for(i=0;i<VECMAX;i++)
   FuzzysetDescriptorptr[1]->FuzzysetDescriptorvector[i]=(float)pow(FuzzysetDescriptorptr[1]->FuzzysetDescriptorvector[i],.5);
  MdlLinkFuzzysetDescriptor(FuzzysetDescriptorptr[1],prcPDBptr,&status);

  FuzzysetDescriptorcnt=2;
  FzyPlotVar("PRICE",FuzzysetDescriptorptr,FuzzysetDescriptorcnt,SYSMODFILE,&status);

//--create and store the ordinary LOW fuzzy set
  FuzzysetDescriptorptr[1]=FzyCreateSet("LOW", DECREASE,Domain,Parms,0,&status);
  strcpy(FuzzysetDescriptorptr[1]->FuzzysetDescriptordesc,"Low for Price");
  MdlLinkFuzzysetDescriptor(FuzzysetDescriptorptr[1],prcPDBptr,&status);
//
//--Create an empty fuzzy set as a working area
  wrkFuzzysetDescriptorptr=FzyCreateSet("NULL",EMPTYSET,Domain,Parms,0,&status);
  MdlLinkFuzzysetDescriptor(wrkFuzzysetDescriptorptr,prcPDBptr,&status);
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
//--Now create the fuzzy number for above around 2*mfgcosts
//
  Domain[0]=16;Domain[1]=36;
  TwiceMfgCosts=2*mfgcosts;
  Parms[0]=TwiceMfgCosts;
  Parms[1]=TwiceMfgCosts*.10;
  FuzzysetDescriptorptr[0]=FzyCreateSet("Near.2*MfgCosts",PI,Domain,Parms,2,&status);
  FzyDrawSet(FuzzysetDescriptorptr[0],SYSMODFILE,&status);
  vryHDBptr=MdlFindHDB("above",prcPDBptr,&status);
  FuzzysetDescriptorptr[1]=FzyCreateSet("NULL",EMPTYSET,Domain,Parms,0,&status);
  FzyApplyHedge(FuzzysetDescriptorptr[0],vryHDBptr,FuzzysetDescriptorptr[1],&status);
  strcpy(FuzzysetDescriptorptr[1]->FuzzysetDescriptordesc,"Above Near (Around) Twice MfgCosts");
  MdlLinkFuzzysetDescriptor(FuzzysetDescriptorptr[1],prcPDBptr,&status);
  FzyDrawSet(FuzzysetDescriptorptr[1],SYSMODFILE,&status);
  FuzzysetDescriptorcnt=2;
  FzyPlotVar("2*MfgCosts",FuzzysetDescriptorptr,FuzzysetDescriptorcnt,SYSMODFILE,&status);
//
//--Now create the fuzzy number for around compprice
  Parms[0]=compprice;
  Parms[1]=compprice*.15;
  FuzzysetDescriptorptr[0]=FzyCreateSet("Near.CompPrice",PI,Domain,Parms,2,&status);
  strcpy(FuzzysetDescriptorptr[0]->FuzzysetDescriptordesc,"Near (Around) Competition Price");
  MdlLinkFuzzysetDescriptor(FuzzysetDescriptorptr[0],prcPDBptr,&status);
  FzyDrawSet(FuzzysetDescriptorptr[0],SYSMODFILE,&status);
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
  Price=fshpr3policy(Rules,mfgcosts,compprice,&compidx,&status);
  fprintf(stdout,"\n\n\n%s%8.2f%s%8.3f\n",
   "The Recommended Price is: ",Price," with CompIdx of ",compidx);
  return;
 }
