/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| weight1.cpp   Earl Cox  04/01/93  The Weight Estimator      |
| This is the main driver routine that invokes the stand-alone|
| weight estimating model. This is an example of monotonic    |
| fuzzy reasoning using the low level fuzzy facilities.       |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include "SFZYctl.hpp"
#include "SSYSctl.hpp"
#include   <mtypes.hpp>
#include <mtsptype.hpp>
double Weight1Model(double,float*,int*);
void main(void)
 {
  double   inHeight[]={5.0,5.25,5.50,5.75,6,6.5};
  int      inHcnt=6;
  int      i,status;
  float    compidx;
  double   height=0,weight;
//
  MdlConnecttoFMS(&status);         // Connect to modelling system
  for(i=0;i<inHcnt;i++)
    {
     height=inHeight[i];
     weight=Weight1Model(height,&compidx,&status);
     fprintf(stdout,"\n\n\n%s%8.2f%s%8.3f\n",
      "The Estimated weight is: ",weight," with a CompIdx of ",compidx);
    }
  return;
 }
