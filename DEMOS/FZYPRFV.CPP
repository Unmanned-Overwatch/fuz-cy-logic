/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| fzyprfv.cpp  Earl Cox  04/01/93 The profit fuzzy sets       |
| This stand-alone program creates a series of over-lapping   |
| fuzzy regions that define the underlying semantics for      |
| the idea of corporate profitabiliy.                         |
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
   "LN",
   "SN",
   "ZR",
   "SP",
   "LP"
  };
char *FDBdesc[]=
  {
   "Large Negative",
   "Small Negative",
   "Zero",
   "Small Positive",
   "Large Positive"
  };
const int FzyTermMax=5;
double Point[]={-150,-100,-50,  0, 50,100,150};
void main(void)
 {
  FDB   *prftFDBptr[FzyTermMax];
  int    i,k,status,FDBcnt=5;

  status=0;
  MdlConnecttoFMS(&status);

  for(i=0;i<FzyTermMax;i++)
    {
     prftFDBptr[i]=new FDB;
     FzyInitFDB(prftFDBptr[i]);
     strcpy(prftFDBptr[i]->FDBid,  FDBnames[i]);
     strcpy(prftFDBptr[i]->FDBdesc,FDBdesc[i]);
     prftFDBptr[i]->FDBdomain[0]=Point[i];
     prftFDBptr[i]->FDBdomain[1]=Point[i+2];
    }
  FzySCurve(prftFDBptr[0],-150,-100,-50,DECLINE,&status);
  FzyDrawSet(prftFDBptr[0],1,&status);
  k=2;
  for(i=1;i<4;i++)
     {
      FzyPiCurve(prftFDBptr[i],Point[k],Point[k+1]-Point[k],&status);
      FzyDrawSet(prftFDBptr[i],1,&status);
      k++;
     }
  FzySCurve(prftFDBptr[4], 50,100,150,GROWTH,&status);
  FzyDrawSet(prftFDBptr[4],1,&status);
  FzyPlotVar("PROFIT",prftFDBptr,FDBcnt,SYSLOGFILE,&status);
//
//
//
  FzyInitFDB(prftFDBptr[0]);
  prftFDBptr[0]->FDBdomain[0]=-150;
  prftFDBptr[0]->FDBdomain[1]= 150;
  FzySCurve(prftFDBptr[0],-150,   0,150,DECLINE,&status);
     strcpy(prftFDBptr[0]->FDBid,  "Unprofitable");
     strcpy(prftFDBptr[0]->FDBdesc,"Loss Money       ");
  FzyInitFDB(prftFDBptr[1]);
  prftFDBptr[1]->FDBdomain[0]=-150;
  prftFDBptr[1]->FDBdomain[1]= 150;
  FzySCurve(prftFDBptr[1],-150,   0,150,GROWTH ,&status);
     strcpy(prftFDBptr[1]->FDBid,  "Profitable");
     strcpy(prftFDBptr[1]->FDBdesc,"Made Money        ");
  FDBcnt=2;
  FzyPlotVar("PROFIT",prftFDBptr,FDBcnt,SYSLOGFILE,&status);
  return;
 }
