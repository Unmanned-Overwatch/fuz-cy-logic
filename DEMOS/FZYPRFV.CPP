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
#include <FuzzysetDescriptor.hpp>
#include "SSYSctl.hpp"
#include   <fuzzy.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
char *FuzzysetDescriptornames[]=
  {
   "LN",
   "SN",
   "ZR",
   "SP",
   "LP"
  };
char *FuzzysetDescriptordesc[]=
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
  FuzzysetDescriptor   *prftFuzzysetDescriptorptr[FzyTermMax];
  int    i,k,status,FuzzysetDescriptorcnt=5;

  status=0;
  MdlConnecttoFMS(&status);

  for(i=0;i<FzyTermMax;i++)
    {
     prftFuzzysetDescriptorptr[i]=new FuzzysetDescriptor;
     FzyInitFuzzysetDescriptor(prftFuzzysetDescriptorptr[i]);
     strcpy(prftFuzzysetDescriptorptr[i]->FuzzysetDescriptorid,  FuzzysetDescriptornames[i]);
     strcpy(prftFuzzysetDescriptorptr[i]->FuzzysetDescriptordesc,FuzzysetDescriptordesc[i]);
     prftFuzzysetDescriptorptr[i]->FuzzysetDescriptordomain[0]=Point[i];
     prftFuzzysetDescriptorptr[i]->FuzzysetDescriptordomain[1]=Point[i+2];
    }
  FzySCurve(prftFuzzysetDescriptorptr[0],-150,-100,-50,DECLINE,&status);
  FzyDrawSet(prftFuzzysetDescriptorptr[0],1,&status);
  k=2;
  for(i=1;i<4;i++)
     {
      FzyPiCurve(prftFuzzysetDescriptorptr[i],Point[k],Point[k+1]-Point[k],&status);
      FzyDrawSet(prftFuzzysetDescriptorptr[i],1,&status);
      k++;
     }
  FzySCurve(prftFuzzysetDescriptorptr[4], 50,100,150,GROWTH,&status);
  FzyDrawSet(prftFuzzysetDescriptorptr[4],1,&status);
  FzyPlotVar("PROFIT",prftFuzzysetDescriptorptr,FuzzysetDescriptorcnt,SYSLOGFILE,&status);
//
//
//
  FzyInitFuzzysetDescriptor(prftFuzzysetDescriptorptr[0]);
  prftFuzzysetDescriptorptr[0]->FuzzysetDescriptordomain[0]=-150;
  prftFuzzysetDescriptorptr[0]->FuzzysetDescriptordomain[1]= 150;
  FzySCurve(prftFuzzysetDescriptorptr[0],-150,   0,150,DECLINE,&status);
     strcpy(prftFuzzysetDescriptorptr[0]->FuzzysetDescriptorid,  "Unprofitable");
     strcpy(prftFuzzysetDescriptorptr[0]->FuzzysetDescriptordesc,"Loss Money       ");
  FzyInitFuzzysetDescriptor(prftFuzzysetDescriptorptr[1]);
  prftFuzzysetDescriptorptr[1]->FuzzysetDescriptordomain[0]=-150;
  prftFuzzysetDescriptorptr[1]->FuzzysetDescriptordomain[1]= 150;
  FzySCurve(prftFuzzysetDescriptorptr[1],-150,   0,150,GROWTH ,&status);
     strcpy(prftFuzzysetDescriptorptr[1]->FuzzysetDescriptorid,  "Profitable");
     strcpy(prftFuzzysetDescriptorptr[1]->FuzzysetDescriptordesc,"Made Money        ");
  FuzzysetDescriptorcnt=2;
  FzyPlotVar("PROFIT",prftFuzzysetDescriptorptr,FuzzysetDescriptorcnt,SYSLOGFILE,&status);
  return;
 }
