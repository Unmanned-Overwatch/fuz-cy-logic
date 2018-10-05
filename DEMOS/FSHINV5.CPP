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
#include "mtsptype.hpp"
//
//
double InvModel5(double,float*,int*);
void main(void)
 {
  int    i,status;
  float  compidx;
  double inOrders[]={60,80,92,95,97,100,130,150,190,200,240,280,300};
  double BOAmt[7];
  float  BOAmtCIX[7];
  int    inOrdcnt =13;
  double orders=0,backorderAmt=0,AdjBOAmt;
//
  MdlConnecttoFMS(&status);
//
  fprintf(stdout,"%s\n%s\n",
   "Orders      BackOrder      CIX            CIX*BOAmt",
   "------      ---------      ---------      ---------");
  for(i=0;i<inOrdcnt;i++)
    {
     orders=inOrders[i];
     backorderAmt=InvModel5(orders,&compidx,&status);
     BOAmt[i]=backorderAmt;
     BOAmtCIX[i]=compidx;
     AdjBOAmt=backorderAmt*compidx;
     fprintf(stdout,"%6.0f      %9.2f      %9.4f      %9.2f\n",
      orders,backorderAmt,compidx,AdjBOAmt);
    }
  return;
 }
