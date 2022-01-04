/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzfso.cpp  Earl Cox  04/01/93 OR two fuzzy sets           |
| This is the high level driver for the fuzzy set zadeh and   |
| compensatory OR facilities.                                 |
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
FuzzysetDescriptor *FzyApplyOR(
   FuzzysetDescriptor *FuzzysetDescriptorptr1,FuzzysetDescriptor *FuzzysetDescriptorptr2,int ORClass,double ORCoeff,int *statusPtr)
 {
   FuzzysetDescriptor  *FuzzysetDescriptoroutptr,*FuzzysetDescriptornull=NULL;
   char *PgmId="mtfzfso";
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
         FzyCompOR(
          ORClass,ORCoeff,
            FuzzysetDescriptorptr1->FuzzysetDescriptorvector[i],FuzzysetDescriptorptr2->FuzzysetDescriptorvector[i],statusPtr);
       if(*statusPtr!=0) return(FuzzysetDescriptornull);
      }
   return(FuzzysetDescriptoroutptr);
 }
