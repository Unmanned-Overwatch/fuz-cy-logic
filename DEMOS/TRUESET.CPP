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
#include <fdb.hpp>
#include "SSYSctl.hpp"
#include   <mtypes.hpp>
#include   <fuzzy.hpp>
#include <mtsptype.hpp>
void main(void)
 {
  FDB      *FDB1ptr;
  int       i,status;
  double    Left,Right;

  MdlConnecttoFMS(&status);              // Connect to modelling system
  FDB1ptr=new FDB;
  FzyInitFDB(FDB1ptr);

  FzyTrueSet(FDB1ptr);
  FzyDrawSet(FDB1ptr,1,&status);

  FDB1ptr->FDBdomain[0]=0.0;
  FDB1ptr->FDBdomain[1]=1.0;

  Left  =0;
  Right =1;
  strcpy(FDB1ptr->FDBid,"Proportional Up");
  FzyLinearCurve(FDB1ptr,Left,Right,INCREASE,&status);
  FzyDrawSet(FDB1ptr,1,&status);
  FzyExamineSet(FDB1ptr,&status);
  return;
 }
