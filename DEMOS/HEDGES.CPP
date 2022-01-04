/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| hedges.cpp   Earl Cox  04/01/93 Run thru the default hedges |
| This standalone procedure runs  through the default hedges  |
| and applies each one to a bell curve, an S-curve, and a     |
| linear curve. This provides us with a template to see how   |
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
  FuzzysetDescriptor  *FuzzysetDescriptorptr,*outFuzzysetDescriptorptr,*FuzzysetDescriptorarray[4];
  HDB  *HDBptr;
  int   i,status,HdgCnt,FuzzysetDescriptorcnt,Hedgemax=12;
  char *PgmId="hedges";
  char  wrkBuff[128];
  char *HedgeNames[]=
   {
    "about",
    "above",
    "positively",
    "below",
    "vicinity",
    "generally",
    "close",
    "not",
    "somewhat",
    "very",
    "extremely",
    "slightly"
   };
  double Center,Width,Left,Right;
  FILE *mdllog;

  status=0;
  MdlConnecttoFMS(&status);               // Connect to modelling system
  mdllog=MtsGetSystemFile(SYSMODFILE);    // Get default model log file
     if(!(HDBptr=new HDB))
       {
        status=1;
        MtsSendError(2,PgmId,HedgeNames[i]);
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
  strcpy(FuzzysetDescriptorptr->FuzzysetDescriptorid,"PI.Curve");
  FuzzysetDescriptorptr->FuzzysetDescriptordomain[0]=16;
  FuzzysetDescriptorptr->FuzzysetDescriptordomain[1]=48;
  fprintf(stdout,"%s\n","Phase 2. Bell Curve            ");
  Center=32;
  Width=Center*.15;
  FzyPiCurve(FuzzysetDescriptorptr,Center,Width,&status);
//Left=16;
//Right=48;
//FzyLinearCurve(FuzzysetDescriptorptr,Left,Right,INCREASE,&status);
  FzyDrawSet(FuzzysetDescriptorptr,SYSMODFILE,&status);
  FzyExamineSet(FuzzysetDescriptorptr,&status);
  for(i=0;i<Hedgemax;i++)
   {
    fprintf(stdout,"%4d%s%s\n",i+1,". ",HedgeNames[i]);
     strcpy(HDBptr->HDBid,HedgeNames[i]);
     HDBptr->HDBmode=i+1;
     HDBptr->HDBop=0;
     HDBptr->HDBvalue=0.0;
    FzyApplyHedge(FuzzysetDescriptorptr,HDBptr,outFuzzysetDescriptorptr,&status);
    FuzzysetDescriptorarray[0]=FuzzysetDescriptorptr;
    FuzzysetDescriptorarray[1]=outFuzzysetDescriptorptr;
    FuzzysetDescriptorcnt=2;
    FzyPlotSets("",FuzzysetDescriptorarray,FuzzysetDescriptorcnt,SYSMODFILE,&status);
   }
  return;
 }
