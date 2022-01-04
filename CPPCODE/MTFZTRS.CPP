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
#include <FuzzysetDescriptor.hpp>
#include   <fuzzy.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
void FzyTriangleCurve(
   FuzzysetDescriptor* FuzzysetDescriptorptr,double Left,double Center,double Right,int *statusPtr)
  {
   int     TrgCnt=3;
   char   *PgmId="mtfztrs";
   double  TrgPoint[5];
   float   TrgGrade[5];

   if((Center<FuzzysetDescriptorptr->FuzzysetDescriptordomain[0])||(Center>FuzzysetDescriptorptr->FuzzysetDescriptordomain[1]))
     {
      *statusPtr=3;
      MtsSendError(56,PgmId,FuzzysetDescriptorptr->FuzzysetDescriptorid);
      return;
     }
   if((Left<FuzzysetDescriptorptr->FuzzysetDescriptordomain[0])||(Right>FuzzysetDescriptorptr->FuzzysetDescriptordomain[1]))
     {
      *statusPtr=5;
      MtsSendError(57,PgmId,FuzzysetDescriptorptr->FuzzysetDescriptorid);
      return;
     }
   TrgPoint[0]=Left;
   TrgGrade[0]=0.0;

   TrgPoint[1]=Center;
   TrgGrade[1]=1.0;

   TrgPoint[2]=Right;
   TrgGrade[2]=0.0;
   FzyCoordSeries(FuzzysetDescriptorptr,TrgPoint,TrgGrade,TrgCnt,statusPtr);
   FuzzysetDescriptorptr->FuzzysetDescriptorgentype=TRIANGLE;
   FuzzysetDescriptorptr->FuzzysetDescriptorparms[0]=Left;
   FuzzysetDescriptorptr->FuzzysetDescriptorparms[1]=Center;
   FuzzysetDescriptorptr->FuzzysetDescriptorparms[2]=Right;
   return;
  }
