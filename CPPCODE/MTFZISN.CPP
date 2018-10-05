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
#include "FDB.hpp"
#include "mtypes.hpp"
#include "fuzzy.hpp"
bool FzyIsNormal(FDB *FDBptr)
  {
   int i;
   for(i=0;i<VECMAX;i++)
      if(FDBptr->FDBvector[i]==1.0) return(TRUE);
   return(FALSE);
  }
