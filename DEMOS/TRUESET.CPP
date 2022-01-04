/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| trueset.cpp  Earl Cox  04/01/93 The [0,1] interval TRUE set |
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
  FuzzysetDescriptor      *FuzzysetDescriptor1ptr;
  int       i,status;
  double    Left,Right;

  MdlConnecttoFMS(&status);              // Connect to modelling system
  FuzzysetDescriptor1ptr=new FuzzysetDescriptor;
  FzyInitFuzzysetDescriptor(FuzzysetDescriptor1ptr);

  FzyTrueSet(FuzzysetDescriptor1ptr);
  FzyDrawSet(FuzzysetDescriptor1ptr,1,&status);

  FuzzysetDescriptor1ptr->FuzzysetDescriptordomain[0]=0.0;
  FuzzysetDescriptor1ptr->FuzzysetDescriptordomain[1]=1.0;

  Left  =0;
  Right =1;
  strcpy(FuzzysetDescriptor1ptr->FuzzysetDescriptorid,"Proportional Up");
  FzyLinearCurve(FuzzysetDescriptor1ptr,Left,Right,INCREASE,&status);
  FzyDrawSet(FuzzysetDescriptor1ptr,1,&status);
  FzyExamineSet(FuzzysetDescriptor1ptr,&status);
  return;
 }
