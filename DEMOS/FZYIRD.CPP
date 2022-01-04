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
  int    i,k,status,FuzzysetDescriptorcnt=5;

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
  FzySCurve(tempFuzzysetDescriptorptr[0],100,140,180,DECLINE,&status);
  FzyDrawSet(tempFuzzysetDescriptorptr[0],1,&status);
  k=2;
  for(i=1;i<4;i++)
     {
      FzyPiCurve(tempFuzzysetDescriptorptr[i],Point[k],Point[k+1]-Point[k],&status);
      FzyDrawSet(tempFuzzysetDescriptorptr[i],1,&status);
      k++;
     }
  FzySCurve(tempFuzzysetDescriptorptr[4],300,340,380,GROWTH,&status);
  FzyDrawSet(tempFuzzysetDescriptorptr[4],1,&status);
  FzyPlotVar("TEMPERATURE",tempFuzzysetDescriptorptr,FuzzysetDescriptorcnt,SYSLOGFILE,&status);
  return;
 }
