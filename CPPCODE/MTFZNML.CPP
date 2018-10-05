/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfznml.cpp   Earl Cox  04/01/93 Normalize a Fuzzy Region.  |
| A fuzzy set is normalized by making its maximum truth value |
| equal to "1".                                               |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <fdb.hpp>
#include   <fuzzy.hpp>
#include   <mtypes.hpp>
void FzyNormalizeSet(FDB* FDBptr)
  {
   int   i;
   float max_memval=FDBptr->FDBvector[0];
//--Find the maximum truth value in the fuzzy set
   for(i=0;i<VECMAX;i++)
      if(FDBptr->FDBvector[i]>max_memval)max_memval=FDBptr->FDBvector[i];
//
//--Scale the fuzzy set into normal form by dividing each truth value
//--by the maximum truth value. This also makes all sub-normal values
//--proportional to the new set height.
   for(i=0;i<VECMAX;i++)
      FDBptr->FDBvector[i]=FDBptr->FDBvector[i]/max_memval;
   return;
  }
