/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzsfs.cpp   Earl Cox  04/01/93 Create a Shouldered Fuzzy  |
| set. This is a trapazoidal curve that is shouldered at the  |
| edge of the fuzzy set.                                      |
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
void FzyShoulderedCurve(
   FDB* FDBptr,int CurveType,double Edge,double Floor,int *statusPtr)
  {
   int     TrgCnt=3;
   char   *PgmId="mtfzsfs";
   double  TrgPoint[5];
   float   TrgGrade[5];

   if((Edge<FDBptr->FDBdomain[0])||(Edge>FDBptr->FDBdomain[1]))
     {
      *statusPtr=3;
      MtsSendError(56,PgmId,FDBptr->FDBid);
      return;
     }
   if((Floor<FDBptr->FDBdomain[0])||(Floor>FDBptr->FDBdomain[1]))
     {
      *statusPtr=3;
      MtsSendError(56,PgmId,FDBptr->FDBid);
      return;
     }
   if(CurveType==LEFTSHOULDER)
     {
      TrgPoint[0]=FDBptr->FDBdomain[0];
      TrgGrade[0]=1.0;

      TrgPoint[1]=Edge;
      TrgGrade[1]=1.0;

      TrgPoint[2]=Floor;
      TrgGrade[2]=0.0;
     }
   if(CurveType==RITESHOULDER)
     {
      TrgPoint[0]=Floor;
      TrgGrade[0]=0.0;

      TrgPoint[1]=Edge;
      TrgGrade[1]=1.0;

      TrgPoint[2]=FDBptr->FDBdomain[1];
      TrgGrade[2]=1.0;
     }
   FzyCoordSeries(FDBptr,TrgPoint,TrgGrade,TrgCnt,statusPtr);
   FDBptr->FDBgentype=CurveType;
   FDBptr->FDBparms[0]=Edge;
   FDBptr->FDBparms[1]=Floor;
   return;
  }
