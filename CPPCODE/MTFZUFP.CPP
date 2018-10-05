/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzufp.cpp   Earl Cox  04/01/93 Unconditional Fuzzy Prop.  |
| This procedure handles the unconditional fuzzy proposition  |
| or assertion. If the target fuzzy set is empty, then we     |
| just copy over the fuzzy set, otherwise we take the minimum |
| of the two sets across the domain.                          |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include "FDB.hpp"
#include "XFZYctl.hpp"
#include "mtypes.hpp"
#include "mtsptype.hpp"
void FzyUnCondProposition(FDB *inFDBptr,FSV *FSVptr)
 {
   int i;
   FDB *outFDBptr;
   outFDBptr=FSVptr->FzySVfdbptr;
   if(outFDBptr->FDBempty)
     {
      FzyCopyVector(outFDBptr->FDBvector,inFDBptr->FDBvector,VECMAX);
      outFDBptr->FDBempty=FALSE;
     }
    else
     {
      for(i=0;i<VECMAX;i++)
       outFDBptr->FDBvector[i]=
        min(outFDBptr->FDBvector[i],inFDBptr->FDBvector[i]);
     }
   FSVptr->FzySVupdcnt++;
   for(i=0;i<VECMAX;i++)
    if(outFDBptr->FDBvector[i]>0) FSVptr->FzySVcntarray[i]++;
   return;
 }
