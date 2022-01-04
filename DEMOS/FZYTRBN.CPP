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
#include <FuzzysetDescriptor.hpp>
#include "SSYSctl.hpp"
#include   <fuzzy.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
char *FuzzysetDescriptornames[]=
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
  FuzzysetDescriptor   *tempFuzzysetDescriptorptr[FzyTermMax];
  int    i,status,FuzzysetDescriptorcnt=5;

  status=0;
  MdlConnecttoFMS(&status);

  for(i=0;i<FzyTermMax;i++)
    {
     tempFuzzysetDescriptorptr[i]=new FuzzysetDescriptor;
     FzyInitFuzzysetDescriptor(tempFuzzysetDescriptorptr[i]);
     strcpy(tempFuzzysetDescriptorptr[i]->FuzzysetDescriptorid,FuzzysetDescriptornames[i]);
     tempFuzzysetDescriptorptr[i]->FuzzysetDescriptordomain[0]=Point[i];
     tempFuzzysetDescriptorptr[i]->FuzzysetDescriptordomain[1]=Point[i+2];
    }
  FzyShoulderedCurve(tempFuzzysetDescriptorptr[0],LEFTSHOULDER,120,180,&status);
  FzyDrawSet(tempFuzzysetDescriptorptr[0],1,&status);
  for(i=1;i<4;i++)
     {
      FzyTriangleCurve(tempFuzzysetDescriptorptr[i],Point[i],Point[i+1],Point[i+2],&status);
      FzyDrawSet(tempFuzzysetDescriptorptr[i],1,&status);
     }
  FzyShoulderedCurve(tempFuzzysetDescriptorptr[4],RITESHOULDER,360,300,&status);
  FzyDrawSet(tempFuzzysetDescriptorptr[4],1,&status);
  FzyPlotVar("TEMPERATURE",tempFuzzysetDescriptorptr,FuzzysetDescriptorcnt,SYSLOGFILE,&status);
  return;
 }
