/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfztru.cpp   Earl Cox  04/01/93  Create the True Fuzzyset. |
| Each segment has a TRUE fuzzyset and is an important set    |
| in approximate reasoning and database operations.           |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <fdb.hpp>
#include <mtsptype.hpp>
#include   <mtypes.hpp>
void FzyTrueSet(FDB* FDBptr)
  {
    int     i;

    FzyInitFDB(FDBptr);
    strcpy(FDBptr->FDBid,"TRUE");
    strcpy(FDBptr->FDBdesc,"The Orthogonal Truth Fuzzyset");
    FDBptr->FDBdomain[0]=0;
    FDBptr->FDBdomain[1]=1;
    for(i=0;i<VECMAX;i++)
       FDBptr->FDBvector[i]=((float)i)/(VECMAX-1);
    return;
   }
