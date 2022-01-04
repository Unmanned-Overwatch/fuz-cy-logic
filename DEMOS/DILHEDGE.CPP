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
#include <FuzzysetDescriptor.hpp>
#include "HDB.hpp"
#include   <fuzzy.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
#include "SSYSctl.hpp"
void main(void)
 {
  FuzzysetDescriptor    *piFuzzysetDescriptorptr,*lnFuzzysetDescriptorptr,*tempFuzzysetDescriptorptr,*FuzzysetDescriptorarray[4];
  int     i,j,status,FuzzysetDescriptorcnt,Powmax=5;
  char   *PgmId="inthedge";
  char    wrkBuff[128];
  double  Center,Width;
  double  Power[]={.2,.3,.5,.7,.9};

  FILE     *mdllog;

  status=0;
  MdlConnecttoFMS(&status);               // Connect to modelling system
  mdllog=MtsGetSystemFile(SYSMODFILE);    // Get default model log file
  if(!(piFuzzysetDescriptorptr=new FuzzysetDescriptor))
    {
     status=1;
     MtsSendError(2,PgmId,"outFuzzysetDescriptor");
     return;
    }
  if(!(lnFuzzysetDescriptorptr=new FuzzysetDescriptor))
    {
     status=1;
     MtsSendError(2,PgmId,"outFuzzysetDescriptor");
     return;
    }
  if(!(tempFuzzysetDescriptorptr=new FuzzysetDescriptor))
    {
     status=1;
     MtsSendError(2,PgmId,"outFuzzysetDescriptor");
     return;
    }
  FzyInitFuzzysetDescriptor(tempFuzzysetDescriptorptr);
//--Initialize and then create a PI curve
  FzyInitFuzzysetDescriptor(piFuzzysetDescriptorptr);
  strcpy(piFuzzysetDescriptorptr->FuzzysetDescriptorid,"PI.Curve");
  piFuzzysetDescriptorptr->FuzzysetDescriptordomain[0]=16;
  piFuzzysetDescriptorptr->FuzzysetDescriptordomain[1]=48;
  Center=    32;
  Width=     Center*.25;
  FzyPiCurve(piFuzzysetDescriptorptr,Center,Width,&status);
  FzyDrawSet(piFuzzysetDescriptorptr,SYSMODFILE,&status);
//
//--Initialize and then create a Line Curve
  FzyInitFuzzysetDescriptor(lnFuzzysetDescriptorptr);
  strcpy(lnFuzzysetDescriptorptr->FuzzysetDescriptorid,"LINE.Curve");
  lnFuzzysetDescriptorptr->FuzzysetDescriptordomain[0]=16;
  lnFuzzysetDescriptorptr->FuzzysetDescriptordomain[1]=48;
  FzyLinearCurve(lnFuzzysetDescriptorptr,16,48,INCREASE,&status);
  FzyDrawSet(lnFuzzysetDescriptorptr,SYSMODFILE,&status);
//
  fprintf(mdllog,"%s\n",
    "            I N T E N S I F Y     E F F E C T S    R E P O R T");

  for(i=0;i<Powmax;i++)
    {
     fprintf(mdllog,"%s%10.2f\n","Power: ",Power[i]);
     FzyCopySet(piFuzzysetDescriptorptr,tempFuzzysetDescriptorptr,&status);
     for(j=0;j<VECMAX;j++)
        tempFuzzysetDescriptorptr->FuzzysetDescriptorvector[j]=(float)pow(tempFuzzysetDescriptorptr->FuzzysetDescriptorvector[j],Power[i]);
     FuzzysetDescriptorarray[0]=piFuzzysetDescriptorptr;
     FuzzysetDescriptorarray[1]=tempFuzzysetDescriptorptr;
     FuzzysetDescriptorcnt=2;
     FzyPlotSets(" ",FuzzysetDescriptorarray,FuzzysetDescriptorcnt,SYSMODFILE,&status);
    }
//
  for(i=0;i<Powmax;i++)
    {
     fprintf(mdllog,"%s%10.2f\n","Power: ",Power[i]);
     FzyCopySet(lnFuzzysetDescriptorptr,tempFuzzysetDescriptorptr,&status);
     for(j=0;j<VECMAX;j++)
        tempFuzzysetDescriptorptr->FuzzysetDescriptorvector[j]=pow(tempFuzzysetDescriptorptr->FuzzysetDescriptorvector[j],Power[i]);
     FuzzysetDescriptorarray[0]=lnFuzzysetDescriptorptr;
     FuzzysetDescriptorarray[1]=tempFuzzysetDescriptorptr;
     FuzzysetDescriptorcnt=2;
     FzyPlotSets(" ",FuzzysetDescriptorarray,FuzzysetDescriptorcnt,SYSMODFILE,&status);
    }
  return;
 }
