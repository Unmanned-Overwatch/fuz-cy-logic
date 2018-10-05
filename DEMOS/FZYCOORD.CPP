/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| fzycoord.cpp Earl Cox  04/01/93  Generate Coord Fuzzy Sets  |
| Using both the truth membership array and the value/truth   |
| coordinate technique, this stand-alone program generates a  |
| suite of fuzzy sets displaying each method.                 |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fdb.hpp>
#include "SSYSctl.hpp"
#include   <fuzzy.hpp>
#include   <mtypes.hpp>
#include <mtsptype.hpp>
void main(void)
 {
  FDB      *FDBptr;
  int       status,Vcnt,memcnt;
  double    low=16;
  double    high=36;
  double    Values[VECMAX];
  float     Members[VECMAX];

  status=0;
  MdlConnecttoFMS(&status);
  FDBptr=new FDB;
  FzyInitFDB(FDBptr);
  FDBptr->FDBdomain[0]=low;
  FDBptr->FDBdomain[1]=high;
//
//---Fuzzy Set via a Membership Function
//
  strcpy(FDBptr->FDBid,"MemSeries");
  float mem1values[]={0,.1,.1,.1,.3,.5,.5,.5,.5,.6,.8,1};
  memcnt=12;
  FzyMemSeries(FDBptr,mem1values,memcnt,&status);
  FzyDrawSet(FDBptr,1,&status);
//
//--The Triangle
//
  FzyInitFDB(FDBptr);
  FDBptr->FDBdomain[0]=120;
  FDBptr->FDBdomain[1]=360;
  strcpy(FDBptr->FDBid,"Triangle");
  float mem2values[]={0,1,0};
  memcnt=3;
  FzyMemSeries(FDBptr,mem2values,memcnt,&status);
  FzyDrawSet(FDBptr,1,&status);
//
//--The Trapezoid
//
  strcpy(FDBptr->FDBid,"Trapezoid");
  float mem3values[]={0,1,1,1,1,0};
  memcnt=6;
  FzyMemSeries(FDBptr,mem3values,memcnt,&status);
  FzyDrawSet(FDBptr,1,&status);
//
//--create as S-cuurve set and display it
//
  FzyInitFDB(FDBptr);
  FDBptr->FDBdomain[0]=low;
  FDBptr->FDBdomain[1]=high;
  strcpy(FDBptr->FDBid,"CoordSeries");
  fprintf(stdout,"%s\n","A coordinate-curve fuzzyset");
  Values[0]=18; Members[0]=.2;
  Values[1]=19; Members[1]=.2;
  Values[2]=25; Members[2]=.3;
  Values[3]=32; Members[3]=.6;
  Values[4]=35; Members[4]=.7;
  Values[5]=36; Members[5]=1.0;
  Vcnt=6;
  FzyCoordSeries(FDBptr,Values,Members,Vcnt,&status);
  if(status!=0)
    {
     fprintf(stdout,"%s%d\n","COORDS curve error: ",status);
     exit(1);
    }
  FzyDrawSet(FDBptr,1,&status);
//
//
  FzyInitFDB(FDBptr);
  FDBptr->FDBdomain[0]=16;
  FDBptr->FDBdomain[1]=100;
  strcpy(FDBptr->FDBid,"High Risk");
  fprintf(stdout,"%s\n","A coordinate-curve fuzzyset");
  Values[0]=16; Members[0]=1.0;
  Values[1]=21; Members[1]=.6;
  Values[2]=28; Members[2]=.3;
  Values[3]=68; Members[3]=.3;
  Values[4]=76; Members[4]=.5;
  Values[5]=80; Members[5]=.7;
  Values[6]=96; Members[6]=1.0;
  Values[7]=100;Members[7]=1.0;
  Vcnt=8;
  FzyCoordSeries(FDBptr,Values,Members,Vcnt,&status);
  if(status!=0)
    {
     fprintf(stdout,"%s%d\n","COORDS curve error: ",status);
     exit(1);
    }
  FzyDrawSet(FDBptr,1,&status);
 }
