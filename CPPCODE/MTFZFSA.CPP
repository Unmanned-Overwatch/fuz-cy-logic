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
#include "FDB.hpp"
#include "mtypes.hpp"
#include "mtsptype.hpp"
FDB *FzyApplyAND(
   FDB *FDBptr1,FDB *FDBptr2,int ANDClass,double ANDCoeff,int *statusPtr)
 {
   FDB  *FDBoutptr,*FDBnull=NULL;
   char *PgmId="mtfzfsa";
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
         FzyCompAND(
          ANDClass,ANDCoeff,
            FDBptr1->FDBvector[i],FDBptr2->FDBvector[i],statusPtr);
       if(*statusPtr!=0) return(FDBnull);
      }
   return(FDBoutptr);
 }
