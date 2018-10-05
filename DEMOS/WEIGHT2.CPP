/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| weight1.cpp   Earl Cox  04/01/93  The Weight Estimator      |
| This is the main driver routine that invokes the stand-alone|
| weight estimating model. This is a counter example of the   |
| monotonic model with multiple rules.                        |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include "SFZYctl.hpp"
#include "SSYSctl.hpp"
#include "mtypes.hpp"
#include "mtsptype.hpp"
double Weight2Model(double,double,float*,int*);
void main(void)
 {
  double   inHeight[]={ 5.0, 5.25, 5.50, 5.75, 6.0,  6.5};
  double   inWaist[] ={  32,   38,   40,   42,  44,   48};
  int      inHcnt=6;
  int      inWcnt=6;
  int      i,j,status;
  float    compidx;
  double   waist,height=0,weight;
//
  MdlConnecttoFMS(&status);              // Connect to modelling system
  for(i=0;i<inHcnt;i++)
    {
     height=inHeight[i];
     for(j=0;j<inWcnt;j++)
       {
        waist =inWaist[j];
        weight=Weight2Model(height,waist,&compidx,&status);
        fprintf(stdout,"\n\n\n%s%8.2f%s%8.3f\n",
         "The Estimated weight is: ",weight," with a CompIdx of ",compidx);
       }
    }
  return;
 }
