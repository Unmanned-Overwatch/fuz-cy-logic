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
#include <FuzzysetDescriptor.hpp>
float FzyGetHeight(FuzzysetDescriptor* FuzzysetDescriptorptr)
  {
   int i;
   float max_memval=FuzzysetDescriptorptr->FuzzysetDescriptorvector[0];
   for(i=0;i<VECMAX;i++)
      if(FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]>max_memval)max_memval=FuzzysetDescriptorptr->FuzzysetDescriptorvector[i];
   return(max_memval);
  }
