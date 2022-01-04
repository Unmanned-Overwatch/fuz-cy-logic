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
#include <FuzzysetDescriptor.hpp>
#include <XFZYctl.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
void FzyUnCondProposition(FuzzysetDescriptor *inFuzzysetDescriptorptr,FSV *FSVptr)
 {
   int i;
   FuzzysetDescriptor *outFuzzysetDescriptorptr;
   outFuzzysetDescriptorptr=FSVptr->FzySVFuzzysetDescriptorptr;
   if(outFuzzysetDescriptorptr->FuzzysetDescriptorempty)
     {
      FzyCopyVector(outFuzzysetDescriptorptr->FuzzysetDescriptorvector,inFuzzysetDescriptorptr->FuzzysetDescriptorvector,VECMAX);
      outFuzzysetDescriptorptr->FuzzysetDescriptorempty=FALSE;
     }
    else
     {
      for(i=0;i<VECMAX;i++)
       outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=
        min(outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i],inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]);
     }
   FSVptr->FzySVupdcnt++;
   for(i=0;i<VECMAX;i++)
    if(outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]>0) FSVptr->FzySVcntarray[i]++;
   return;
 }
