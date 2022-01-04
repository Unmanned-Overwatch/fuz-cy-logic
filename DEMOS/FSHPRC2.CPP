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
#include <FuzzysetDescriptor.hpp>
#include "SFZYctl.hpp"
#include "SSYSctl.hpp"
#include   <fuzzy.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
//
extern unsigned _stklen=50000;
double fshpr2policy(double,double,float*,int*);
void main(void)
 {
  PDB     *prcPDBptr;
  FuzzysetDescriptor     *FuzzysetDescriptorptr[FuzzysetDescriptorvecmax];
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
//--Create the basic fuzzy sets (High and Low for Price)
//
  FuzzysetDescriptorptr[0]=FzyCreateSet("HIGH",INCREASE,Domain,Parms,0,&status);
  strcpy(FuzzysetDescriptorptr[0]->FuzzysetDescriptordesc,"High for Price");
  MdlLinkFuzzysetDescriptor(FuzzysetDescriptorptr[0],prcPDBptr,&status);
  FuzzysetDescriptorptr[1]=FzyCreateSet("LOW", DECREASE,Domain,Parms,0,&status);
  strcpy(FuzzysetDescriptorptr[1]->FuzzysetDescriptordesc,"Low for Price");
  MdlLinkFuzzysetDescriptor(FuzzysetDescriptorptr[1],prcPDBptr,&status);
  FuzzysetDescriptorcnt=2;
  FzyPlotVar("PRICE",FuzzysetDescriptorptr,FuzzysetDescriptorcnt,SYSMODFILE,&status);
//--Create an empty fuzzy set as a working area
  FuzzysetDescriptorptr[0]=FzyCreateSet("NULL",EMPTYSET,Domain,Parms,0,&status);
  MdlLinkFuzzysetDescriptor(FuzzysetDescriptorptr[0],prcPDBptr,&status);
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
  FuzzysetDescriptorptr[0]=FzyCreateSet("Near.2*MfgCosts",PI,Domain,Parms,2,&status);
  strcpy(FuzzysetDescriptorptr[0]->FuzzysetDescriptordesc,"Near (Around) Twice MfgCosts");
  MdlLinkFuzzysetDescriptor(FuzzysetDescriptorptr[0],prcPDBptr,&status);
  FzyDrawSet(FuzzysetDescriptorptr[0],SYSMODFILE,&status);
  FuzzysetDescriptorcnt++;
//
//--Now create the fuzzy number for around compprice
  Parms[0]=compprice;
  Parms[1]=compprice*.15;
  FuzzysetDescriptorptr[0]=FzyCreateSet("Near.CompPrice",PI,Domain,Parms,2,&status);
  strcpy(FuzzysetDescriptorptr[0]->FuzzysetDescriptordesc,"Near (Around) Competition Price");
  MdlLinkFuzzysetDescriptor(FuzzysetDescriptorptr[0],prcPDBptr,&status);
  FzyDrawSet(FuzzysetDescriptorptr[0],SYSMODFILE,&status);
//
//--Display the current data values on the model log
//
fprintf(mdlout,"%s\n",
  "Fuzzy Pricing Model. (c) 1992 Metus Systems Group.");
fprintf(mdlout,"%s%10.2f\n",
  "[Mean] Competition Price: ",compprice);
fprintf(mdlout,"%s%10.2f\n",
  "Base Manufacturing Costs: ",mfgcosts );
//
//--Invoke the pricing policy and display the returned results
//
  Price=fshpr2policy(mfgcosts,compprice,&compidx,&status);
  fprintf(stdout,"\n\n\n%s%8.2f%s%8.3f\n",
   "The Recommended Price is: ",Price," with CompIdx of ",compidx);
  return;
 }
