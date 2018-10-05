/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| inthedge.cpp Earl Cox  04/01/93 Show intensification effects|
| This standalone procedure runs through a series of exponent |
| values and shows how the linear and bell shapped curves are |
| affected by this process.                                   |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <stddef.h>
#include <math.h>
#include "FDB.hpp"
#include "HDB.hpp"
#include "fuzzy.hpp"
#include "mtypes.hpp"
#include "mtsptype.hpp"
#include "SSYSctl.hpp"
void main(void)
 {
  FDB    *piFDBptr,*lnFDBptr,*tempFDBptr,*FDBarray[4];
  int     i,j,status,FDBcnt,Powmax=5;
  char   *PgmId="inthedge";
  char    wrkBuff[128];
  double  Center,Width;
  double  Power[]={.2,.3,.5,.7,.9};

  FILE     *mdllog;

  status=0;
  MdlConnecttoFMS(&status);               // Connect to modelling system
  mdllog=MtsGetSystemFile(SYSMODFILE);    // Get default model log file
  if(!(piFDBptr=new FDB))
    {
     status=1;
     MtsSendError(2,PgmId,"outFDB");
     return;
    }
  if(!(lnFDBptr=new FDB))
    {
     status=1;
     MtsSendError(2,PgmId,"outFDB");
     return;
    }
  if(!(tempFDBptr=new FDB))
    {
     status=1;
     MtsSendError(2,PgmId,"outFDB");
     return;
    }
  FzyInitFDB(tempFDBptr);
//--Initialize and then create a PI curve
  FzyInitFDB(piFDBptr);
  strcpy(piFDBptr->FDBid,"PI.Curve");
  piFDBptr->FDBdomain[0]=16;
  piFDBptr->FDBdomain[1]=48;
  Center=    32;
  Width=     Center*.25;
  FzyPiCurve(piFDBptr,Center,Width,&status);
  FzyDrawSet(piFDBptr,SYSMODFILE,&status);
//
//--Initialize and then create a Line Curve
  FzyInitFDB(lnFDBptr);
  strcpy(lnFDBptr->FDBid,"LINE.Curve");
  lnFDBptr->FDBdomain[0]=16;
  lnFDBptr->FDBdomain[1]=48;
  FzyLinearCurve(lnFDBptr,16,48,INCREASE,&status);
  FzyDrawSet(lnFDBptr,SYSMODFILE,&status);
//
  fprintf(mdllog,"%s\n",
    "            I N T E N S I F Y     E F F E C T S    R E P O R T");

  for(i=0;i<Powmax;i++)
    {
     fprintf(mdllog,"%s%10.2f\n","Power: ",Power[i]);
     FzyCopySet(piFDBptr,tempFDBptr,&status);
     for(j=0;j<VECMAX;j++)
        tempFDBptr->FDBvector[j]=(float)pow(tempFDBptr->FDBvector[j],Power[i]);
     FDBarray[0]=piFDBptr;
     FDBarray[1]=tempFDBptr;
     FDBcnt=2;
     FzyPlotSets(" ",FDBarray,FDBcnt,SYSMODFILE,&status);
    }
//
  for(i=0;i<Powmax;i++)
    {
     fprintf(mdllog,"%s%10.2f\n","Power: ",Power[i]);
     FzyCopySet(lnFDBptr,tempFDBptr,&status);
     for(j=0;j<VECMAX;j++)
        tempFDBptr->FDBvector[j]=pow(tempFDBptr->FDBvector[j],Power[i]);
     FDBarray[0]=lnFDBptr;
     FDBarray[1]=tempFDBptr;
     FDBcnt=2;
     FzyPlotSets(" ",FDBarray,FDBcnt,SYSMODFILE,&status);
    }
  return;
 }
