/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| invmod1.cpp   Earl Cox  04/01/93  The Inventory Model       |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include "SFZYctl.hpp"
#include "SSYSctl.hpp"
#include <mtsptype.hpp>
//
//
double InvModel1(double,float*,int*);
void main(void)
 {
  int    i,status;
  float  compidx;
  double inOrders[]={60,80,100,130,150,190,200};
  double BOAmt[7];
  float  BOAmtCIX[7];
  int    inOrdcnt =7;
  double orders=0,backorderAmt=0;
//
  MdlConnecttoFMS(&status);
//
  fprintf(stdout,"%s\n%s\n",
   "Orders      BackOrder      CIX",
   "------      ---------      ---------");
  for(i=0;i<inOrdcnt;i++)
    {
     orders=inOrders[i];
     backorderAmt=InvModel1(orders,&compidx,&status);
     BOAmt[i]=backorderAmt;
     BOAmtCIX[i]=compidx;
     fprintf(stdout,"%6.0f      %9.2f      %9.4f\n",
      orders,backorderAmt,compidx);
    }
  return;
 }
