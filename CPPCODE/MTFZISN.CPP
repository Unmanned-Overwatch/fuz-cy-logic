/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzisn.cpp   Earl Cox  04/01/93 Indicates whether or not   |
| a fuzzy region is normal. A fuzzy region is normal if its   |
| maximum truth value is "1.0"                                |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <FuzzysetDescriptor.hpp>
#include   <SystemTypes.hpp>
#include   <fuzzy.hpp>
bool FzyIsNormal(FuzzysetDescriptor *FuzzysetDescriptorptr)
  {
   int i;
   for(i=0;i<VECMAX;i++)
      if(FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]==1.0) return(TRUE);
   return(FALSE);
  }
