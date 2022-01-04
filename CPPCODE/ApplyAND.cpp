/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzfsa.cpp  Earl Cox  04/01/93 AND two fuzzy sets          |
| This is the high level driver for the fuzzy set zadeh and   |
| compensatory AND facilities.                                |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stddef.h>
#include <FuzzysetDescriptor.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
FuzzysetDescriptor *FzyApplyAND(
   FuzzysetDescriptor *FuzzysetDescriptorptr1,FuzzysetDescriptor *FuzzysetDescriptorptr2,int ANDClass,double ANDCoeff,int *statusPtr)
 {
   FuzzysetDescriptor  *FuzzysetDescriptoroutptr,*FuzzysetDescriptornull=NULL;
   char *PgmId="mtfzfsa";
   int   i;

   *statusPtr=0;
   if(!(FuzzysetDescriptoroutptr=new FuzzysetDescriptor))
     {
      *statusPtr=1;
      MtsSendError(2,PgmId,"");
      return(FuzzysetDescriptornull);
     }
   FzyInitFuzzysetDescriptor(FuzzysetDescriptoroutptr);
   FzyCopySet(FuzzysetDescriptorptr1,FuzzysetDescriptoroutptr,statusPtr);
   for(i=0;i<VECMAX;i++)
      {
       FuzzysetDescriptoroutptr->FuzzysetDescriptorvector[i]=
         FzyCompAND(
          ANDClass,ANDCoeff,
            FuzzysetDescriptorptr1->FuzzysetDescriptorvector[i],FuzzysetDescriptorptr2->FuzzysetDescriptorvector[i],statusPtr);
       if(*statusPtr!=0) return(FuzzysetDescriptornull);
      }
   return(FuzzysetDescriptoroutptr);
 }
