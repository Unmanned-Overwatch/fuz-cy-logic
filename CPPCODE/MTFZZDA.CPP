/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzzda.cpp   Earl Cox  04/01/93 The Zadeh AND operation    |
| This routine takes the minimum of two truth functions,      |
| thus implementing the Zadeh AND operator                    |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <math.h>
float min(float,float);
float FzyAND(float truth1,float truth2)
  {
    if(truth1<0||truth1>1) {return(-1);}
    if(truth2<0||truth2>1) {return(-2);}
    return(min(truth1,truth2));
  }
