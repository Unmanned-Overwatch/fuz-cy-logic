/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| pihedge.cpp  Earl Cox  04/01/93 apply hedges to PI curves   |
| This standalone procedure runes through the default hedges  |
| and applies each one to a bell curve, in particular a PI    |
| shaped curve. This provides us with a template to see how   |
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
  FuzzysetDescriptor    *FuzzysetDescriptorptr,*outFuzzysetDescriptorptr,*FuzzysetDescriptorarray[4];
  HDB    *HDBptr;
  int     i,status,HdgCnt,FuzzysetDescriptorcnt,Hedgemax=12;
  char   *PgmId="Pihedge";
  char    wrkBuff[128];
  char   *HedgeNames[]=
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
  double  Center,Width;
  FILE     *mdllog;

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
  fprintf(mdllog,"%s\n",
    "                 H E D G E     E F F E C T S    R E P O R T");
  fprintf(mdllog,"%s\n",
    "                          Bell-shaped fuzzy sets         "  );
//
//--Create a PI shaped fuzzy set centered at the middle of the
//--domain. Display the set and examine the memberhsip function.
  Center=    32;
  Width=     Center*.15;
  FzyPiCurve(FuzzysetDescriptorptr,Center,Width,&status);
  FzyDrawSet(FuzzysetDescriptorptr,SYSMODFILE,&status);
  FzyExamineSet(FuzzysetDescriptorptr,&status);
//
//--Loop through each of the hedges and apply each hedge to the
//--PI curve. We then print out the overlapping hedge and its
//--hedged version.
  for(i=0;i<Hedgemax;i++)
   {
    fprintf(stdout,"%4d%s%s\n",i+1,". ",HedgeNames[i]);
    strcpy(HDBptr->HDBid,HedgeNames[i]);
     HDBptr->HDBmode=  i+1;
     HDBptr->HDBop=    0;
     HDBptr->HDBvalue= 0.0;
    FzyApplyHedge(FuzzysetDescriptorptr,HDBptr,outFuzzysetDescriptorptr,&status);
    FuzzysetDescriptorarray[0]=FuzzysetDescriptorptr;
    FuzzysetDescriptorarray[1]=outFuzzysetDescriptorptr;
    FuzzysetDescriptorcnt=2;
    FzyPlotSets("",FuzzysetDescriptorarray,FuzzysetDescriptorcnt,SYSMODFILE,&status);
   }
  return;
 }
