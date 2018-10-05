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
#include <fdb.hpp>
#include "HDB.hpp"
#include   <fuzzy.hpp>
#include   <mtypes.hpp>
#include <mtsptype.hpp>
#include "SSYSctl.hpp"
void main(void)
 {
  FDB    *FDBptr,
         *outFDBptr,
         *FDBarray[4];
  HDB    *HDBptr;
  int     i,
          status,
          HdgCnt,
          FDBcnt,
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
  strcpy(FDBptr->FDBid,"LI.Curve");
  FDBptr->FDBdomain[0]=16;
  FDBptr->FDBdomain[1]=48;
  fprintf(mdllog,"%s\n","ABOUT a point                    ");
//Center=32;
//Width=Center*.15;
//FzyPiCurve(FDBptr,Center,Width,&status);
  Center=VECMAX/2;
  FDBptr->FDBvector[Center]=1.00;
  FzyDrawSet(FDBptr,SYSMODFILE,&status);
  FzyExamineSet(FDBptr,&status);
     strcpy(HDBptr->HDBid,"about"      );
     HDBptr->HDBmode=1;
     HDBptr->HDBop=0;
     HDBptr->HDBvalue=0.0;
    FzyApplyHedge(FDBptr,HDBptr,outFDBptr,&status);
    FzyDrawSet(FDBptr,SYSMODFILE,&status);
    FDBarray[0]=FDBptr;
    FDBarray[1]=outFDBptr;
    FDBcnt=2;
    FzyPlotSets("",FDBarray,FDBcnt,SYSMODFILE,&status);
 }
