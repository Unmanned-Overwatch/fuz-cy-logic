/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| normlz.cpp   Earl Cox  04/01/93 Normalizing fuzzy sets      |
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
  FDB    *FDBptr,*piFDBptr,*FDBarray[4];
  int     i,status,FDBcnt;
  char   *PgmId="normlz";
  char    wrkBuff[128];
  double  Center,Width;
  FILE     *mdllog;

  status=0;
  MdlConnecttoFMS(&status);               // Connect to modelling system
  mdllog=MtsGetSystemFile(SYSMODFILE);    // Get default model log file
  if(!(piFDBptr=new FDB))
    {
     status=1;
     MtsSendError(2,PgmId,"FDB");
     return;
    }
  if(!(FDBptr=new FDB))
    {
     status=1;
     MtsSendError(2,PgmId,"FDB");
     return;
    }
  FzyInitFDB(FDBptr);
  strcpy(FDBptr->FDBid,"Pi.Curve");
  FDBptr->FDBdomain[0]=16;
  FDBptr->FDBdomain[1]=48;
  fprintf(mdllog,"%s\n",
    "          N O R M A L I Z E    E F F E C T S    R E P O R T");
  fprintf(mdllog,"%s\n",
    "                          Bell-shaped fuzzy sets         "  );
//
//--Create a PI shaped fuzzy set centered at the middle of the
//--domain. Display the set and examine the memberhsip function.
  Center=    32;
  Width=     Center*.15;
  FzyPiCurve(FDBptr,Center,Width,&status);
  FzyDrawSet(FDBptr,SYSMODFILE,&status);
  FzyCopySet(FDBptr,piFDBptr,&status);
  FDBarray[0]=FDBptr;
  FDBarray[1]=piFDBptr;
  FDBcnt=2;
  for(i=0;i<VECMAX;i++) FDBptr->FDBvector[i]=FDBptr->FDBvector[i]*.5;
  FzyPlotSets("S.Curves",FDBarray,FDBcnt,SYSMODFILE,&status);
  return;
 }
