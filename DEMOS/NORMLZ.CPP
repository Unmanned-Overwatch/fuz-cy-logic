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
#include <FuzzysetDescriptor.hpp>
#include "HDB.hpp"
#include   <fuzzy.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
#include "SSYSctl.hpp"
void main(void)
 {
  FuzzysetDescriptor    *FuzzysetDescriptorptr,*piFuzzysetDescriptorptr,*FuzzysetDescriptorarray[4];
  int     i,status,FuzzysetDescriptorcnt;
  char   *PgmId="normlz";
  char    wrkBuff[128];
  double  Center,Width;
  FILE     *mdllog;

  status=0;
  MdlConnecttoFMS(&status);               // Connect to modelling system
  mdllog=MtsGetSystemFile(SYSMODFILE);    // Get default model log file
  if(!(piFuzzysetDescriptorptr=new FuzzysetDescriptor))
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
  strcpy(FuzzysetDescriptorptr->FuzzysetDescriptorid,"Pi.Curve");
  FuzzysetDescriptorptr->FuzzysetDescriptordomain[0]=16;
  FuzzysetDescriptorptr->FuzzysetDescriptordomain[1]=48;
  fprintf(mdllog,"%s\n",
    "          N O R M A L I Z E    E F F E C T S    R E P O R T");
  fprintf(mdllog,"%s\n",
    "                          Bell-shaped fuzzy sets         "  );
//
//--Create a PI shaped fuzzy set centered at the middle of the
//--domain. Display the set and examine the memberhsip function.
  Center=    32;
  Width=     Center*.15;
  FzyPiCurve(FuzzysetDescriptorptr,Center,Width,&status);
  FzyDrawSet(FuzzysetDescriptorptr,SYSMODFILE,&status);
  FzyCopySet(FuzzysetDescriptorptr,piFuzzysetDescriptorptr,&status);
  FuzzysetDescriptorarray[0]=FuzzysetDescriptorptr;
  FuzzysetDescriptorarray[1]=piFuzzysetDescriptorptr;
  FuzzysetDescriptorcnt=2;
  for(i=0;i<VECMAX;i++) FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]*.5;
  FzyPlotSets("S.Curves",FuzzysetDescriptorarray,FuzzysetDescriptorcnt,SYSMODFILE,&status);
  return;
 }
