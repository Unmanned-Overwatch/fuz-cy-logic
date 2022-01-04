/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| hedges.cpp   Earl Cox  04/01/93 Test hedge operations       |
| This standalone procedure runs through a suite of the       |
| default hedges, applying each one to linear, PI, and Scurve |
| fuzzy sets.   This provides us with a template to see how   |
| the various hedges operations change basic fuzzy sets.      |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <stddef.h>
#include <FuzzysetDescriptor.hpp>
#include "HDB.hpp"
#include   <fuzzy.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
#include "SSYSctl.hpp"
void main(void)
 {
  FuzzysetDescriptor    *FuzzysetDescriptorptr,
         *outFuzzysetDescriptorptr,
         *FuzzysetDescriptorarray[4];
  HDB    *HDBptr;
  int     i,
          status,
          HdgCnt,
          FuzzysetDescriptorcnt,
          Hedgemax=12;
  char   *PgmId="hedges";
  char    wrkBuff[128];
  double  Center,Width,Left,Right;
  FILE   *mdllog;

  status=0;
  mdllog=MtsGetSystemFile(SYSMODFILE);    // Get default model log file
  MdlConnecttoFMS(&status);               // Connect to modelling system
  if(!(HDBptr=new HDB))
    {
     status=1;
     MtsSendError(2,PgmId,"ABOUT"      );
     return;
    }
  FzyInitHDB(HDBptr);
  if(!(outFuzzysetDescriptorptr=new FuzzysetDescriptor))
    {
     status=1;
     MtsSendError(2,PgmId,"outFuzzysetDescriptor");
     return;
    }
  FzyInitFuzzysetDescriptor(outFuzzysetDescriptorptr);
  strcpy(outFuzzysetDescriptorptr->FuzzysetDescriptorid,"outCurve");
  outFuzzysetDescriptorptr->FuzzysetDescriptordomain[0]=16;
  outFuzzysetDescriptorptr->FuzzysetDescriptordomain[1]=48;
  if(!(FuzzysetDescriptorptr=new FuzzysetDescriptor))
    {
     status=1;
     MtsSendError(2,PgmId,"FuzzysetDescriptor");
     return;
    }
  FzyInitFuzzysetDescriptor(FuzzysetDescriptorptr);
  strcpy(FuzzysetDescriptorptr->FuzzysetDescriptorid,"LI.Curve");
  FuzzysetDescriptorptr->FuzzysetDescriptordomain[0]=16;
  FuzzysetDescriptorptr->FuzzysetDescriptordomain[1]=48;
  fprintf(mdllog,"%s\n","ABOUT a point                    ");
//Center=32;
//Width=Center*.15;
//FzyPiCurve(FuzzysetDescriptorptr,Center,Width,&status);
  Center=VECMAX/2;
  FuzzysetDescriptorptr->FuzzysetDescriptorvector[Center]=1.00;
  FzyDrawSet(FuzzysetDescriptorptr,SYSMODFILE,&status);
  FzyExamineSet(FuzzysetDescriptorptr,&status);
     strcpy(HDBptr->HDBid,"about"      );
     HDBptr->HDBmode=1;
     HDBptr->HDBop=0;
     HDBptr->HDBvalue=0.0;
    FzyApplyHedge(FuzzysetDescriptorptr,HDBptr,outFuzzysetDescriptorptr,&status);
    FzyDrawSet(FuzzysetDescriptorptr,SYSMODFILE,&status);
    FuzzysetDescriptorarray[0]=FuzzysetDescriptorptr;
    FuzzysetDescriptorarray[1]=outFuzzysetDescriptorptr;
    FuzzysetDescriptorcnt=2;
    FzyPlotSets("",FuzzysetDescriptorarray,FuzzysetDescriptorcnt,SYSMODFILE,&status);
 }
