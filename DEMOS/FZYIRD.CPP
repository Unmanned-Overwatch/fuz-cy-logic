/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| fzyird.cpp   Earl Cox  04/01/93 The InfraRed Dectector      |
| These are the temperature fuzzy sets used in an infrared    |
| intruder decting system.                                    |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fdb.hpp>
#include "SSYSctl.hpp"
#include   <fuzzy.hpp>
#include   <mtypes.hpp>
#include <mtsptype.hpp>
char *FDBnames[]=
  {
   "COLD",
   "COOL",
   "NORMAL",
   "WARM",
   "HOT"
  };
const int FzyTermMax=5;
double Point[]={100,120,180,240,300,360,380};
void main(void)
 {
  FDB   *tempFDBptr[FzyTermMax];
  int    i,k,status,FDBcnt=5;

  status=0;
  MdlConnecttoFMS(&status);

  for(i=0;i<FzyTermMax;i++)
    {
     tempFDBptr[i]=new FDB;
     FzyInitFDB(tempFDBptr[i]);
     strcpy(tempFDBptr[i]->FDBid,FDBnames[i]);
     tempFDBptr[i]->FDBdomain[0]=Point[i];
     tempFDBptr[i]->FDBdomain[1]=Point[i+2];
    }
  FzySCurve(tempFDBptr[0],100,140,180,DECLINE,&status);
  FzyDrawSet(tempFDBptr[0],1,&status);
  k=2;
  for(i=1;i<4;i++)
     {
      FzyPiCurve(tempFDBptr[i],Point[k],Point[k+1]-Point[k],&status);
      FzyDrawSet(tempFDBptr[i],1,&status);
      k++;
     }
  FzySCurve(tempFDBptr[4],300,340,380,GROWTH,&status);
  FzyDrawSet(tempFDBptr[4],1,&status);
  FzyPlotVar("TEMPERATURE",tempFDBptr,FDBcnt,SYSLOGFILE,&status);
  return;
 }
