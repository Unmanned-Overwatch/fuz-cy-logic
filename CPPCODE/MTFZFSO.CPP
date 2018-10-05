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
#include <fdb.hpp>
#include   <mtypes.hpp>
#include <mtsptype.hpp>
FDB *FzyApplyOR(
   FDB *FDBptr1,FDB *FDBptr2,int ORClass,double ORCoeff,int *statusPtr)
 {
   FDB  *FDBoutptr,*FDBnull=NULL;
   char *PgmId="mtfzfso";
   int   i;

   *statusPtr=0;
   if(!(FDBoutptr=new FDB))
     {
      *statusPtr=1;
      MtsSendError(2,PgmId,"");
      return(FDBnull);
     }
   FzyInitFDB(FDBoutptr);
   FzyCopySet(FDBptr1,FDBoutptr,statusPtr);
   for(i=0;i<VECMAX;i++)
      {
       FDBoutptr->FDBvector[i]=
         FzyCompOR(
          ORClass,ORCoeff,
            FDBptr1->FDBvector[i],FDBptr2->FDBvector[i],statusPtr);
       if(*statusPtr!=0) return(FDBnull);
      }
   return(FDBoutptr);
 }
