/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzinv.cpp   Earl Cox  04/01/93 Initialize a truth vector. |
| This procedure propogates a vale through a floating point   |
| array.                                                      |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include "fuzzy.hpp"
void FzyInitVector(float vector[],int VecLen,float InitVal)
  {
   int i;
   for(i=0;i<VecLen;i++) vector[i]=InitVal;
  }
