/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| propfst.cpp  Earl Cox  04/01/93 Proportional fuzzy sets     |
| Here are how some of the proportional linguistic variable   |
| components appear.                                          |
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
  double    Left,Right,Center,flexpoint,Wfactor;

  MdlConnecttoFMS(&status);
  FuzzysetDescriptor1ptr=new FuzzysetDescriptor;
  FzyInitFuzzysetDescriptor(FuzzysetDescriptor1ptr);
//
  FuzzysetDescriptor1ptr->FuzzysetDescriptordomain[0]=0;
  FuzzysetDescriptor1ptr->FuzzysetDescriptordomain[1]=1;
//--The MOST proportional set
  Left=.5;
  Center=(Right-Left)/2;
  Right=1.0;
  strcpy(FuzzysetDescriptor1ptr->FuzzysetDescriptorid,"Most");
  FzySCurve(FuzzysetDescriptor1ptr,Left,Center,Right,GROWTH,&status);
  FzyDrawSet(FuzzysetDescriptor1ptr,1,&status);
//
//--The NEARLY ALL proportional set
  Left=.8;
  Center=(Right-Left)/2;
  Right=1.0;
  strcpy(FuzzysetDescriptor1ptr->FuzzysetDescriptorid,"Nearly All");
  FzySCurve(FuzzysetDescriptor1ptr,Left,Center,Right,GROWTH,&status);
  FzyDrawSet(FuzzysetDescriptor1ptr,1,&status);
//
//--The Usually proportional set
  Left=0;
  Center=(Right-Left)/2;
  Right=1.0;
  strcpy(FuzzysetDescriptor1ptr->FuzzysetDescriptorid,"Usually");
  FzySCurve(FuzzysetDescriptor1ptr,Left,Center,Right,GROWTH,&status);
  FzyDrawSet(FuzzysetDescriptor1ptr,1,&status);
//
//--The EVERY proportional set
  Left=.9;
  Center=(Right-Left)/2;
  Right=1.0;
  strcpy(FuzzysetDescriptor1ptr->FuzzysetDescriptorid,"Every");
  FzySCurve(FuzzysetDescriptor1ptr,Left,Center,Right,GROWTH,&status);
  FzyDrawSet(FuzzysetDescriptor1ptr,1,&status);
  return;
 }
