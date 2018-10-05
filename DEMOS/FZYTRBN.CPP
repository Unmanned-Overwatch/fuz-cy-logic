/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| fzytrbn.cpp  Earl Cox  04/01/93 Steam Trubine Fuzzy Sets    |
| These are the fuzzy sets for the TEMPERATURE component of   |
| the fuzzy steam turbine controller.                         |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "FDB.hpp"
#include "SSYSctl.hpp"
#include "fuzzy.hpp"
#include "mtypes.hpp"
#include "mtsptype.hpp"
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
  int    i,status,FDBcnt=5;

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
  FzyShoulderedCurve(tempFDBptr[0],LEFTSHOULDER,120,180,&status);
  FzyDrawSet(tempFDBptr[0],1,&status);
  for(i=1;i<4;i++)
     {
      FzyTriangleCurve(tempFDBptr[i],Point[i],Point[i+1],Point[i+2],&status);
      FzyDrawSet(tempFDBptr[i],1,&status);
     }
  FzyShoulderedCurve(tempFDBptr[4],RITESHOULDER,360,300,&status);
  FzyDrawSet(tempFDBptr[4],1,&status);
  FzyPlotVar("TEMPERATURE",tempFDBptr,FDBcnt,SYSLOGFILE,&status);
  return;
 }
