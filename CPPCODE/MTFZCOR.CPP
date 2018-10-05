/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtfzcor.cpp   Earl Cox  04/01/93   The correlation methods. |
| Correlation Maximum (the classical Zadeh impl method) will  |
| take a fuzzy region and clip it at the maximum of a truth   |
| value (the 'plateau'.) Normally this plateau value comes    |
| from the truth of the predicate fuzzy expression. The       |
| correlation product simply multiples the truth function by  |
| the predicate truth, thus this acts like a scaling factor.  |
*-------------------------------------------------------------*/
#include <stdlib.h>
#include "fuzzy.hpp"
#include "FDB.hpp"
#include "mtypes.hpp"
#include "mtsptype.hpp"
void FzyCorrMinimum(float vector[],const float PredTruth,int *statusPtr)
   {
    int i;
    char *PgmId="mtfzcor";
    *statusPtr=0;
    if(PredTruth<0||PredTruth>1)
      {
       *statusPtr=1;
       MtsSendError(26,PgmId,MtsFormatFlt(PredTruth,4));
       return;
      }
    for(i=0;i<VECMAX;i++) vector[i]=min(vector[i],PredTruth);
    return;
   }
//
//
void FzyCorrProduct(float vector[],const truthval PredTruth,int *statusPtr)
   {
    int i;
    char *PgmId="mtfzcor";
    *statusPtr=0;
    if(PredTruth<0||PredTruth>1)
      {
       *statusPtr=1;
       MtsSendError(26,PgmId,MtsFormatFlt(PredTruth,4));
       return;
      }
    for(i=0;i<VECMAX;i++) vector[i]=vector[i]*PredTruth;
    return;
   }
//
//
void FzyCorrAverage(float vector[],const truthval PredTruth,int *statusPtr)
   {
    int i;
    char *PgmId="mtfzcor";
    *statusPtr=0;
    if(PredTruth<0||PredTruth>1)
      {
       *statusPtr=1;
       MtsSendError(26,PgmId,MtsFormatFlt(PredTruth,4));
       return;
      }
    for(i=0;i<VECMAX;i++) vector[i]=min(1,(vector[i]+PredTruth)/2);
    return;
   }
