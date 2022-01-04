/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtfzdel.cpp   Earl Cox  04/01/93 Delete a Fuzzy Set         |
| This procedure returns the storage associated with a fuzzy  |
| set to the heap.                                            |
*-------------------------------------------------------------*/
#include <FuzzysetDescriptor.hpp>
#include   <fuzzy.hpp>
#include   <SystemTypes.hpp>
bool FzyDeleteSet(FuzzysetDescriptor* FuzzysetDescriptorptr)
  {
   delete FuzzysetDescriptorptr;
   return(SUCCESS);
  }
