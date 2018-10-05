/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzhgt.cpp   Earl Cox  04/01/93 The Fuzzy Set Height.      |
| This routine finds the height of the fuzzy set, that is,    |
| point of maximum truth in the fuzzy set membership function.|
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include   <fuzzy.hpp>
#include <fdb.hpp>
float FzyGetHeight(FDB* FDBptr)
  {
   int i;
   float max_memval=FDBptr->FDBvector[0];
   for(i=0;i<VECMAX;i++)
      if(FDBptr->FDBvector[i]>max_memval)max_memval=FDBptr->FDBvector[i];
   return(max_memval);
  }
