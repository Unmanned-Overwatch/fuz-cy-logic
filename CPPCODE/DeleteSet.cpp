/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtfzdel.cpp   Earl Cox  04/01/93 Delete a Fuzzy Set         |
| This procedure returns the storage associated with a fuzzy  |
| set to the heap.                                            |
*-------------------------------------------------------------*/
#include <fdb.hpp>
#include   <fuzzy.hpp>
#include   <mtypes.hpp>
bool FzyDeleteSet(FDB* FDBptr)
  {
   delete FDBptr;
   return(SUCCESS);
  }
