/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| alfacut.cpp  Earl Cox  04/01/93 Show affects of alfa cuts   |
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
  FDB    *FDBptr,*scFDBptr,*FDBarray[4];
  int     i,status,FDBcnt;
  char   *PgmId="alfacut";
  char    wrkBuff[128];
  float   alfas[]={0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
  int     alfacnt=9;
  double  Left,Flexpt,Right;
  FILE     *mdllog;

  status=0;
  MdlConnecttoFMS(&status);               // Connect to modelling system
  mdllog=MtsGetSystemFile(SYSMODFILE);    // Get default model log file
  if(!(scFDBptr=new FDB))
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
  strcpy(FDBptr->FDBid,"S.Curve");
  FDBptr->FDBdomain[0]=16;
  FDBptr->FDBdomain[1]=48;
  fprintf(mdllog,"%s\n",
    "          A L F A C U T     E F F E C T S    R E P O R T");
  fprintf(mdllog,"%s\n",
    "                          Bell-shaped fuzzy sets         "  );
//
//--Create a PI shaped fuzzy set centered at the middle of the
//--domain. Display the set and examine the memberhsip function.
  Left =FDBptr->FDBdomain[0];
  Right=FDBptr->FDBdomain[1];
  Flexpt=Left+((Right-Left)/2);
  FzySCurve(FDBptr,Left,Flexpt,Right,GROWTH,&status);
  FzyDrawSet(FDBptr,SYSMODFILE,&status);
  FzyCopySet(FDBptr,scFDBptr,&status);
  FDBarray[0]=FDBptr;
  FDBarray[1]=scFDBptr;
  FDBcnt=2;
//
//--Loop through each of the hedges and apply each hedge to the
//--PI curve. We then print out the overlapping hedge and its
//--hedged version.
  for(i=0;i<alfacnt;i++)
   {
    sprintf(wrkBuff,"%s%7.3f\n","Alfa-cut: ",alfas[i]);
    strcpy(FDBptr->FDBdesc,wrkBuff);
    FzySCurve(FDBptr,Left,Flexpt,Right,GROWTH,&status);
    FzyApplyAlfa(FDBptr,alfas[i],STRONG);
    FzyDrawSet(FDBptr,SYSMODFILE,&status);
//  FzyPlotSets("S.Curves",FDBarray,FDBcnt,SYSMODFILE,&status);
   }
  return;
 }
