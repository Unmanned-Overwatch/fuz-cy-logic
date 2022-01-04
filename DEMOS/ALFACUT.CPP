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
#include <FuzzysetDescriptor.hpp>
#include "HDB.hpp"
#include   <fuzzy.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
#include "SSYSctl.hpp"
void main(void)
 {
  FuzzysetDescriptor    *FuzzysetDescriptorptr,*scFuzzysetDescriptorptr,*FuzzysetDescriptorarray[4];
  int     i,status,FuzzysetDescriptorcnt;
  char   *PgmId="alfacut";
  char    wrkBuff[128];
  float   alfas[]={0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
  int     alfacnt=9;
  double  Left,Flexpt,Right;
  FILE     *mdllog;

  status=0;
  MdlConnecttoFMS(&status);               // Connect to modelling system
  mdllog=MtsGetSystemFile(SYSMODFILE);    // Get default model log file
  if(!(scFuzzysetDescriptorptr=new FuzzysetDescriptor))
    {
     status=1;
     MtsSendError(2,PgmId,"FuzzysetDescriptor");
     return;
    }
  if(!(FuzzysetDescriptorptr=new FuzzysetDescriptor))
    {
     status=1;
     MtsSendError(2,PgmId,"FuzzysetDescriptor");
     return;
    }
  FzyInitFuzzysetDescriptor(FuzzysetDescriptorptr);
  strcpy(FuzzysetDescriptorptr->FuzzysetDescriptorid,"S.Curve");
  FuzzysetDescriptorptr->FuzzysetDescriptordomain[0]=16;
  FuzzysetDescriptorptr->FuzzysetDescriptordomain[1]=48;
  fprintf(mdllog,"%s\n",
    "          A L F A C U T     E F F E C T S    R E P O R T");
  fprintf(mdllog,"%s\n",
    "                          Bell-shaped fuzzy sets         "  );
//
//--Create a PI shaped fuzzy set centered at the middle of the
//--domain. Display the set and examine the memberhsip function.
  Left =FuzzysetDescriptorptr->FuzzysetDescriptordomain[0];
  Right=FuzzysetDescriptorptr->FuzzysetDescriptordomain[1];
  Flexpt=Left+((Right-Left)/2);
  FzySCurve(FuzzysetDescriptorptr,Left,Flexpt,Right,GROWTH,&status);
  FzyDrawSet(FuzzysetDescriptorptr,SYSMODFILE,&status);
  FzyCopySet(FuzzysetDescriptorptr,scFuzzysetDescriptorptr,&status);
  FuzzysetDescriptorarray[0]=FuzzysetDescriptorptr;
  FuzzysetDescriptorarray[1]=scFuzzysetDescriptorptr;
  FuzzysetDescriptorcnt=2;
//
//--Loop through each of the hedges and apply each hedge to the
//--PI curve. We then print out the overlapping hedge and its
//--hedged version.
  for(i=0;i<alfacnt;i++)
   {
    sprintf(wrkBuff,"%s%7.3f\n","Alfa-cut: ",alfas[i]);
    strcpy(FuzzysetDescriptorptr->FuzzysetDescriptordesc,wrkBuff);
    FzySCurve(FuzzysetDescriptorptr,Left,Flexpt,Right,GROWTH,&status);
    FzyApplyAlfa(FuzzysetDescriptorptr,alfas[i],STRONG);
    FzyDrawSet(FuzzysetDescriptorptr,SYSMODFILE,&status);
//  FzyPlotSets("S.Curves",FuzzysetDescriptorarray,FuzzysetDescriptorcnt,SYSMODFILE,&status);
   }
  return;
 }
