/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfznrm.cpp   Earl Cox  04/01/93 Indicates whether or not   |
| a fuzzy region is normal according to the type of normal    |
| tolerance (or rigidity) required by the user.               |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include "FDB.hpp"
#include "mtypes.hpp"
#include "fuzzy.hpp"
bool FzyIsNormalType(FDB *FDBptr,int NormType)
  {
   bool  MinNormal;
   int   i;

//--Calculate Minimal Normal since we will need this state
//--regardless of which normal level the user has selected.
   MinNormal=FALSE;
   for(i=0;i<VECMAX;i++)
      if(FDBptr->FDBvector[i]==1.0) MinNormal=TRUE;
//--Minimal normal means that the height is [1.0]. So we
//--just return the state of the MinNormal variable.
//
   if(NormType==NormMINIMUM)  return(MinNormal);
//
//--Getting here means that the user requested NormMaximum
//--meaning that the fuzzy set must also have a zero membership
//--component. Of course, if the set is not NormMinimum we can
//--say False right away; otherwise we scan for a zero element.
//
   if(!MinNormal)                   return(FALSE);
   for(i=0;i<VECMAX;i++)
      if(FDBptr->FDBvector[i]==0.0) return(TRUE);
   return(FALSE);
  }
