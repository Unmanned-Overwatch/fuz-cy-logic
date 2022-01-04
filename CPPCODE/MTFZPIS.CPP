/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzpis.cpp   Earl Cox  04/01/93 Create a PI-shaped Fuzzy   |
| set. This is a bell-shaped curve around a central point. We |
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
void FzyPiCurve(FuzzysetDescriptor* FuzzysetDescriptorptr,double Center,double Width,int *statusPtr)
  {
   int     i;
   char   *PgmId="mtfzpis";
   float   tempVector[VECMAX];
   double  inflexpoint,boundarypoint;

   FzyInitVector(tempVector,VECMAX,ZERO);
   if(Width<0)
     {
      *statusPtr=1;
      MtsSendError(39,PgmId,FuzzysetDescriptorptr->FuzzysetDescriptorid);
      return;
     }
   if((Center<FuzzysetDescriptorptr->FuzzysetDescriptordomain[0])||(Center>FuzzysetDescriptorptr->FuzzysetDescriptordomain[1]))
     {
      *statusPtr=3;
      MtsSendError(40,PgmId,FuzzysetDescriptorptr->FuzzysetDescriptorid);
      printf("%s%10.2f\n","lo domain  = ",FuzzysetDescriptorptr->FuzzysetDescriptordomain[0]);
      printf("%s%10.2f\n","hi domain  = ",FuzzysetDescriptorptr->FuzzysetDescriptordomain[1]);
      return;
     }
   if((Center-fabs(Width)<FuzzysetDescriptorptr->FuzzysetDescriptordomain[0])&&
      (Center+fabs(Width)>FuzzysetDescriptorptr->FuzzysetDescriptordomain[1]))
     {
      *statusPtr=5;
      MtsSendError(41,PgmId,FuzzysetDescriptorptr->FuzzysetDescriptorid);
      printf("%s%10.2f\n","lo domain  = ",FuzzysetDescriptorptr->FuzzysetDescriptordomain[0]);
      printf("%s%10.2f\n","hi domain  = ",FuzzysetDescriptorptr->FuzzysetDescriptordomain[1]);
      return;
     }
   inflexpoint=Center+(Width/2);
   boundarypoint=Center+Width;
   FzySCurve(FuzzysetDescriptorptr,Center,inflexpoint,boundarypoint,GROWTH,statusPtr);
   for(i=0;i<VECMAX;i++) tempVector[i]=(float)1.0-FuzzysetDescriptorptr->FuzzysetDescriptorvector[i];
   inflexpoint=Center-Width;
   boundarypoint=Center-(Width/2);
   FzySCurve(FuzzysetDescriptorptr,inflexpoint,boundarypoint,Center,GROWTH,statusPtr);
   for(i=0;i<VECMAX;i++)
    FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=min(FuzzysetDescriptorptr->FuzzysetDescriptorvector[i],tempVector[i]);
   FuzzysetDescriptorptr->FuzzysetDescriptorgentype=PI;
   FuzzysetDescriptorptr->FuzzysetDescriptorparms[0]=Center;
   FuzzysetDescriptorptr->FuzzysetDescriptorparms[1]=Width;
   return;
  }
