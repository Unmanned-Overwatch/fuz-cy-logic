/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfztrs.cpp   Earl Cox  04/01/93 Create a Triangular Fuzzy  |
| set. This is a triangled curve around a central point. We   |
| take the mid-point and the width of the pi flange.          |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <math.h>
#include "FDB.hpp"
#include "fuzzy.hpp"
#include "mtypes.hpp"
#include "mtsptype.hpp"
void FzyTriangleCurve(
   FDB* FDBptr,double Left,double Center,double Right,int *statusPtr)
  {
   int     TrgCnt=3;
   char   *PgmId="mtfztrs";
   double  TrgPoint[5];
   float   TrgGrade[5];

   if((Center<FDBptr->FDBdomain[0])||(Center>FDBptr->FDBdomain[1]))
     {
      *statusPtr=3;
      MtsSendError(56,PgmId,FDBptr->FDBid);
      return;
     }
   if((Left<FDBptr->FDBdomain[0])||(Right>FDBptr->FDBdomain[1]))
     {
      *statusPtr=5;
      MtsSendError(57,PgmId,FDBptr->FDBid);
      return;
     }
   TrgPoint[0]=Left;
   TrgGrade[0]=0.0;

   TrgPoint[1]=Center;
   TrgGrade[1]=1.0;

   TrgPoint[2]=Right;
   TrgGrade[2]=0.0;
   FzyCoordSeries(FDBptr,TrgPoint,TrgGrade,TrgCnt,statusPtr);
   FDBptr->FDBgentype=TRIANGLE;
   FDBptr->FDBparms[0]=Left;
   FDBptr->FDBparms[1]=Center;
   FDBptr->FDBparms[2]=Right;
   return;
  }
