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
#include <FuzzysetDescriptor.hpp>
#include   <fuzzy.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
void FzyShoulderedCurve(
   FuzzysetDescriptor* FuzzysetDescriptorptr,int CurveType,double Edge,double Floor,int *statusPtr)
  {
   int     TrgCnt=3;
   char   *PgmId="mtfzsfs";
   double  TrgPoint[5];
   float   TrgGrade[5];

   if((Edge<FuzzysetDescriptorptr->FuzzysetDescriptordomain[0])||(Edge>FuzzysetDescriptorptr->FuzzysetDescriptordomain[1]))
     {
      *statusPtr=3;
      MtsSendError(56,PgmId,FuzzysetDescriptorptr->FuzzysetDescriptorid);
      return;
     }
   if((Floor<FuzzysetDescriptorptr->FuzzysetDescriptordomain[0])||(Floor>FuzzysetDescriptorptr->FuzzysetDescriptordomain[1]))
     {
      *statusPtr=3;
      MtsSendError(56,PgmId,FuzzysetDescriptorptr->FuzzysetDescriptorid);
      return;
     }
   if(CurveType==LEFTSHOULDER)
     {
      TrgPoint[0]=FuzzysetDescriptorptr->FuzzysetDescriptordomain[0];
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

      TrgPoint[2]=FuzzysetDescriptorptr->FuzzysetDescriptordomain[1];
      TrgGrade[2]=1.0;
     }
   FzyCoordSeries(FuzzysetDescriptorptr,TrgPoint,TrgGrade,TrgCnt,statusPtr);
   FuzzysetDescriptorptr->FuzzysetDescriptorgentype=CurveType;
   FuzzysetDescriptorptr->FuzzysetDescriptorparms[0]=Edge;
   FuzzysetDescriptorptr->FuzzysetDescriptorparms[1]=Floor;
   return;
  }
