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
#include <FuzzysetDescriptor.hpp>
#include "SSYSctl.hpp"
#include   <SystemTypes.hpp>
#include   <fuzzy.hpp>
#include <SystemPrototypes.hpp>
void main(void)
 {
  FuzzysetDescriptor      *FuzzysetDescriptor1ptr,
           *FuzzysetDescriptor2ptr,
           *FuzzysetDescriptor3ptr,
           *FuzzysetDescriptor4ptr,
           *FuzzysetDescriptorarray[5];
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
  FuzzysetDescriptor1ptr=new FuzzysetDescriptor;
  FzyInitFuzzysetDescriptor(FuzzysetDescriptor1ptr);
  FuzzysetDescriptor1ptr->FuzzysetDescriptordomain[0]=16;
  FuzzysetDescriptor1ptr->FuzzysetDescriptordomain[1]=42;
//
//--------------   Line curves -----------------------------------------
//
  Left  =18;
  Right =36;
  strcpy(FuzzysetDescriptor1ptr->FuzzysetDescriptorid,"Linear Up");
  FzyLinearCurve(FuzzysetDescriptor1ptr,Left,Right,INCREASE,&status);
  FzyDrawSet(FuzzysetDescriptor1ptr,SYSMODFILE,&status);
  FzyExamineSet(FuzzysetDescriptor1ptr,&status);
//
  Left  =18;
  Right =36;
  strcpy(FuzzysetDescriptor1ptr->FuzzysetDescriptorid,"Linear Down");
  FzyLinearCurve(FuzzysetDescriptor1ptr,Left,Right,DECREASE,&status);
  FzyDrawSet(FuzzysetDescriptor1ptr,SYSMODFILE,&status);
  FzyExamineSet(FuzzysetDescriptor1ptr,&status);
//
//--------------   S  curves   -----------------------------------------
//
  Left=18;
  Center=29;
  Right=40;
  FuzzysetDescriptor4ptr=new FuzzysetDescriptor;
  FzyInitFuzzysetDescriptor(FuzzysetDescriptor4ptr);
  FuzzysetDescriptor4ptr->FuzzysetDescriptordomain[0]=16;
  FuzzysetDescriptor4ptr->FuzzysetDescriptordomain[1]=42;
  strcpy(FuzzysetDescriptor4ptr->FuzzysetDescriptorid,"SCgrw[18,29,40]");
  FzySCurve(FuzzysetDescriptor4ptr,Left,Center,Right,GROWTH,&status);
  FzyDrawSet(FuzzysetDescriptor4ptr,SYSMODFILE,&status);
  FzyExamineSet(FuzzysetDescriptor4ptr,&status);
//
  strcpy(FuzzysetDescriptor4ptr->FuzzysetDescriptorid,"SCdcl[18,29,40]");
  FzySCurve(FuzzysetDescriptor4ptr,Left,Center,Right,DECLINE,&status);
  FzyDrawSet(FuzzysetDescriptor4ptr,SYSMODFILE,&status);
  FzyExamineSet(FuzzysetDescriptor4ptr,&status);
//
//--------------   PI  curves   ----------------------------------------
//
  Center=29;
  maxSets=5;
  for(i=0;i<maxSets;i++)
    {
     flexpoint=Center*Percents[i];
     sprintf(FuzzysetDescriptor1ptr->FuzzysetDescriptorid,"%s%5.0f%s","PI Set[",Percents[i]*100,"%]");
     FzyPiCurve(FuzzysetDescriptor1ptr,Center,flexpoint,&status);
     FzyDrawSet(FuzzysetDescriptor1ptr,SYSMODFILE,&status);
    }
//
//--------------   Beta curves  ----------------------------------------
//
  Center=29;
  maxSets=5;
  for(i=0;i<maxSets;i++)
    {
     flexpoint=Center*Percents[i];
     sprintf(FuzzysetDescriptor1ptr->FuzzysetDescriptorid,"%s%5.0f%s","Beta Set[",Percents[i]*100,"%]");
     FzyBetaCurve(FuzzysetDescriptor1ptr,Center,flexpoint,&status);
     FzyDrawSet(FuzzysetDescriptor1ptr,SYSMODFILE,&status);
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
     strcpy(FuzzysetDescriptor4ptr->FuzzysetDescriptorid,wrkBuff);
     FzyWgtdBetaCurve(FuzzysetDescriptor4ptr,Center,flexpoint,Wfactor,&status);
     FzyDrawSet(FuzzysetDescriptor4ptr,SYSMODFILE,&status);
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
     strcpy(FuzzysetDescriptor4ptr->FuzzysetDescriptorid,wrkBuff);
     FzyGaussianCurve(FuzzysetDescriptor4ptr,Center,Wfactor,&status);
     FzyDrawSet(FuzzysetDescriptor4ptr,SYSMODFILE,&status);
     FzyExamineSet(FuzzysetDescriptor4ptr,&status);
    }
  return;
 }
