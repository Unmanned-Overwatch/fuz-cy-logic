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
#include <FuzzysetDescriptor.hpp>
#include <SystemPrototypes.hpp>
#include   <SystemTypes.hpp>
void FzyTrueSet(FuzzysetDescriptor* FuzzysetDescriptorptr)
  {
    int     i;

    FzyInitFuzzysetDescriptor(FuzzysetDescriptorptr);
    strcpy(FuzzysetDescriptorptr->FuzzysetDescriptorid,"TRUE");
    strcpy(FuzzysetDescriptorptr->FuzzysetDescriptordesc,"The Orthogonal Truth Fuzzyset");
    FuzzysetDescriptorptr->FuzzysetDescriptordomain[0]=0;
    FuzzysetDescriptorptr->FuzzysetDescriptordomain[1]=1;
    for(i=0;i<VECMAX;i++)
       FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=((float)i)/(VECMAX-1);
    return;
   }
