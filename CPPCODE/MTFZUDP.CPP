/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzudp.cpp  Earl Cox  04/01/93 Detect an undecidable set   |
| A result fuzzy set is undecidable if it is empty (height=0) |
| or the truth membership function is all ones. This function |
| examines the set for these conditions.                      |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include "FDB.hpp"
#include "mtypes.hpp"
#include "fuzzy.hpp"
#include "mtsptype.hpp"
bool FzyIsUndecidable(FDB *FDBptr)
 {
  int i;
  if(FzyGetHeight(FDBptr)==0)     return(TRUE);
  for(i=0;i<VECMAX;i++)
   if(FDBptr->FDBvector[i]!=1.0) return(FALSE);
  return(TRUE);
 }
