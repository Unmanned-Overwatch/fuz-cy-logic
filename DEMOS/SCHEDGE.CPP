/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| schedge.cpp  Earl Cox  04/01/93 Apply hedges to S-curves    |
| This standalone procedure runes through the default hedges  |
| and applies each one to an S-curve.                         |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <stddef.h>
#include <fdb.hpp>
#include "HDB.hpp"
#include   <fuzzy.hpp>
#include   <mtypes.hpp>
#include <mtsptype.hpp>
#include "SSYSctl.hpp"
void main(void)
 {
  FDB    *FDBptr,*outFDBptr,*FDBarray[4];
  HDB    *HDBptr;
  int     i,status,HdgCnt,FDBcnt,Hedgemax=12;
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
  double    Center,Left,Right;
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
  if(!(outFDBptr=new FDB))
    {
     status=1;
     MtsSendError(2,PgmId,"outFDB");
     return;
    }
  FzyInitFDB(outFDBptr);
  strcpy(outFDBptr->FDBid,"outCurve");
  outFDBptr->FDBdomain[0]=16;
  outFDBptr->FDBdomain[1]=48;
  if(!(FDBptr=new FDB))
    {
     status=1;
     MtsSendError(2,PgmId,"FDB");
     return;
    }
  FzyInitFDB(FDBptr);
  strcpy(FDBptr->FDBid,"S.Curve");
  FDBptr->FDBdomain[0]=16;
  FDBptr->FDBdomain[1]=48;
  fprintf(mdllog,"%s\n",
    "                 H E D G E     E F F E C T S    R E P O R T");
  fprintf(mdllog,"%s\n",
    "                             S-shaped fuzzy sets         "  );
//
//--Create an S-shaped fuzzy set inflected at the middle of the
//--domain. Display the set and examine the memberhsip function.
  Left=      16;
  Center=    32;
  Right=     48;
  FzySCurve(FDBptr,Left,Center,Right,GROWTH,&status);
  FzyDrawSet(FDBptr,SYSMODFILE,&status);
  FzyExamineSet(FDBptr,&status);
//
//--Loop through each of the hedges and apply each hedge to the
//--S-curve. We then print out the overlapping hedge and its
//--hedged version.
  for(i=0;i<Hedgemax;i++)
   {
    fprintf(stdout,"%4d%s%s\n",i+1,". ",HedgeNames[i]);
    strcpy(HDBptr->HDBid,HedgeNames[i]);
     HDBptr->HDBmode=  i+1;
     HDBptr->HDBop=    0;
     HDBptr->HDBvalue= 0.0;
    FzyApplyHedge(FDBptr,HDBptr,outFDBptr,&status);
    FDBarray[0]=FDBptr;
    FDBarray[1]=outFDBptr;
    FDBcnt=2;
    FzyPlotSets("",FDBarray,FDBcnt,SYSMODFILE,&status);
   }
  return;
 }
