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
#include "FDB.hpp"
#include "SSYSctl.hpp"
#include "mtypes.hpp"
#include "fuzzy.hpp"
#include "mtsptype.hpp"
void main(void)
 {
  FDB      *FDB1ptr;
  int       i,status;
  double    Left,Right,Center,flexpoint,Wfactor;

  MdlConnecttoFMS(&status);
  FDB1ptr=new FDB;
  FzyInitFDB(FDB1ptr);
//
  FDB1ptr->FDBdomain[0]=0;
  FDB1ptr->FDBdomain[1]=1;
//--The MOST proportional set
  Left=.5;
  Center=(Right-Left)/2;
  Right=1.0;
  strcpy(FDB1ptr->FDBid,"Most");
  FzySCurve(FDB1ptr,Left,Center,Right,GROWTH,&status);
  FzyDrawSet(FDB1ptr,1,&status);
//
//--The NEARLY ALL proportional set
  Left=.8;
  Center=(Right-Left)/2;
  Right=1.0;
  strcpy(FDB1ptr->FDBid,"Nearly All");
  FzySCurve(FDB1ptr,Left,Center,Right,GROWTH,&status);
  FzyDrawSet(FDB1ptr,1,&status);
//
//--The Usually proportional set
  Left=0;
  Center=(Right-Left)/2;
  Right=1.0;
  strcpy(FDB1ptr->FDBid,"Usually");
  FzySCurve(FDB1ptr,Left,Center,Right,GROWTH,&status);
  FzyDrawSet(FDB1ptr,1,&status);
//
//--The EVERY proportional set
  Left=.9;
  Center=(Right-Left)/2;
  Right=1.0;
  strcpy(FDB1ptr->FDBid,"Every");
  FzySCurve(FDB1ptr,Left,Center,Right,GROWTH,&status);
  FzyDrawSet(FDB1ptr,1,&status);
  return;
 }
