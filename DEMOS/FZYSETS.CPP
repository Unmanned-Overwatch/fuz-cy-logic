/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| fzysets.cpp  Earl Cox  04/01/93  Fuzzy set type display     |
| This stand-alone prrogram display a number of different     |
| fuzzy set shapes. Tests out the generators and shows how    |
| changes in parameters give different topologies.            |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <fdb.hpp>
#include "SSYSctl.hpp"
#include   <mtypes.hpp>
#include   <fuzzy.hpp>
#include <mtsptype.hpp>
void main(void)
 {
  FDB      *FDB1ptr,
           *FDB2ptr,
           *FDB3ptr,
           *FDB4ptr,
           *FDBarray[5];
  char      wrkBuff[16];
  int       i,status,SetCnt;
  int       maxSets;
  double    Left,
            Right,
            Center,
            flexpoint,
            Wfactor;
  double    GaussWgt[]={.9,.7,.5,.1,1,5,7,9};
  double    Percents[]={.40,.25,.15,.10,.05};

  MdlConnecttoFMS(&status);              // Connect to modelling system
  FDB1ptr=new FDB;
  FzyInitFDB(FDB1ptr);
  FDB1ptr->FDBdomain[0]=16;
  FDB1ptr->FDBdomain[1]=42;
//
//--------------   Line curves -----------------------------------------
//
  Left  =18;
  Right =36;
  strcpy(FDB1ptr->FDBid,"Linear Up");
  FzyLinearCurve(FDB1ptr,Left,Right,INCREASE,&status);
  FzyDrawSet(FDB1ptr,SYSMODFILE,&status);
  FzyExamineSet(FDB1ptr,&status);
//
  Left  =18;
  Right =36;
  strcpy(FDB1ptr->FDBid,"Linear Down");
  FzyLinearCurve(FDB1ptr,Left,Right,DECREASE,&status);
  FzyDrawSet(FDB1ptr,SYSMODFILE,&status);
  FzyExamineSet(FDB1ptr,&status);
//
//--------------   S  curves   -----------------------------------------
//
  Left=18;
  Center=29;
  Right=40;
  FDB4ptr=new FDB;
  FzyInitFDB(FDB4ptr);
  FDB4ptr->FDBdomain[0]=16;
  FDB4ptr->FDBdomain[1]=42;
  strcpy(FDB4ptr->FDBid,"SCgrw[18,29,40]");
  FzySCurve(FDB4ptr,Left,Center,Right,GROWTH,&status);
  FzyDrawSet(FDB4ptr,SYSMODFILE,&status);
  FzyExamineSet(FDB4ptr,&status);
//
  strcpy(FDB4ptr->FDBid,"SCdcl[18,29,40]");
  FzySCurve(FDB4ptr,Left,Center,Right,DECLINE,&status);
  FzyDrawSet(FDB4ptr,SYSMODFILE,&status);
  FzyExamineSet(FDB4ptr,&status);
//
//--------------   PI  curves   ----------------------------------------
//
  Center=29;
  maxSets=5;
  for(i=0;i<maxSets;i++)
    {
     flexpoint=Center*Percents[i];
     sprintf(FDB1ptr->FDBid,"%s%5.0f%s","PI Set[",Percents[i]*100,"%]");
     FzyPiCurve(FDB1ptr,Center,flexpoint,&status);
     FzyDrawSet(FDB1ptr,SYSMODFILE,&status);
    }
//
//--------------   Beta curves  ----------------------------------------
//
  Center=29;
  maxSets=5;
  for(i=0;i<maxSets;i++)
    {
     flexpoint=Center*Percents[i];
     sprintf(FDB1ptr->FDBid,"%s%5.0f%s","Beta Set[",Percents[i]*100,"%]");
     FzyBetaCurve(FDB1ptr,Center,flexpoint,&status);
     FzyDrawSet(FDB1ptr,SYSMODFILE,&status);
    }
//
//--------------   Weighted Beta Curves  -------------------------------
//
  Center=29;
  flexpoint=Center*.25;
  for(i=0;i<maxSets;i++)
    {
     Wfactor=GaussWgt[i];
     sprintf(wrkBuff,"%s%7.2f","WBeta-",Wfactor);
     strcpy(FDB4ptr->FDBid,wrkBuff);
     FzyWgtdBetaCurve(FDB4ptr,Center,flexpoint,Wfactor,&status);
     FzyDrawSet(FDB4ptr,SYSMODFILE,&status);
    }
//
//--------------   Gaussian curves  ------------------------------------
//
  maxSets=8;
  Center=29;
  for(i=0;i<maxSets;i++)
    {
     Wfactor=GaussWgt[i];
     sprintf(wrkBuff,"%s%7.2f","Gauss-",Wfactor);
     strcpy(FDB4ptr->FDBid,wrkBuff);
     FzyGaussianCurve(FDB4ptr,Center,Wfactor,&status);
     FzyDrawSet(FDB4ptr,SYSMODFILE,&status);
     FzyExamineSet(FDB4ptr,&status);
    }
  return;
 }
