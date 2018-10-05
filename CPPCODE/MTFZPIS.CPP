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
#include "FDB.hpp"
#include "fuzzy.hpp"
#include "mtypes.hpp"
#include "mtsptype.hpp"
void FzyPiCurve(FDB* FDBptr,double Center,double Width,int *statusPtr)
  {
   int     i;
   char   *PgmId="mtfzpis";
   float   tempVector[VECMAX];
   double  inflexpoint,boundarypoint;

   FzyInitVector(tempVector,VECMAX,ZERO);
   if(Width<0)
     {
      *statusPtr=1;
      MtsSendError(39,PgmId,FDBptr->FDBid);
      return;
     }
   if((Center<FDBptr->FDBdomain[0])||(Center>FDBptr->FDBdomain[1]))
     {
      *statusPtr=3;
      MtsSendError(40,PgmId,FDBptr->FDBid);
      printf("%s%10.2f\n","lo domain  = ",FDBptr->FDBdomain[0]);
      printf("%s%10.2f\n","hi domain  = ",FDBptr->FDBdomain[1]);
      return;
     }
   if((Center-fabs(Width)<FDBptr->FDBdomain[0])&&
      (Center+fabs(Width)>FDBptr->FDBdomain[1]))
     {
      *statusPtr=5;
      MtsSendError(41,PgmId,FDBptr->FDBid);
      printf("%s%10.2f\n","lo domain  = ",FDBptr->FDBdomain[0]);
      printf("%s%10.2f\n","hi domain  = ",FDBptr->FDBdomain[1]);
      return;
     }
   inflexpoint=Center+(Width/2);
   boundarypoint=Center+Width;
   FzySCurve(FDBptr,Center,inflexpoint,boundarypoint,GROWTH,statusPtr);
   for(i=0;i<VECMAX;i++) tempVector[i]=(float)1.0-FDBptr->FDBvector[i];
   inflexpoint=Center-Width;
   boundarypoint=Center-(Width/2);
   FzySCurve(FDBptr,inflexpoint,boundarypoint,Center,GROWTH,statusPtr);
   for(i=0;i<VECMAX;i++)
    FDBptr->FDBvector[i]=min(FDBptr->FDBvector[i],tempVector[i]);
   FDBptr->FDBgentype=PI;
   FDBptr->FDBparms[0]=Center;
   FDBptr->FDBparms[1]=Width;
   return;
  }
