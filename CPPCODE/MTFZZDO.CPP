/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzzdo.cpp   Earl Cox  04/01/93 The Zadeh OR operation     |
| This routine takes the maximum of two truth functions,      |
| thus implementing the Zadeh OR operator                     |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                   |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <math.h>
float max(float,float);
float FzyOR (float truth1,float truth2)
  {
    if(truth1<0||truth1>1) {return(-1);}
    if(truth2<0||truth2>1) {return(-2);}
    return(max(truth1,truth2));
  }
