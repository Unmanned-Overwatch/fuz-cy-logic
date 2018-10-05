/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzscs.cpp   Earl Cox  04/01/93  Create an S-Curve Fuzzy   |
| set. The left or right facing S-curve has three paramters:  |
| the left and right edges of the set, and the "inflextion"   |
| point (the place were the value is 50% true).               |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include "FDB.hpp"
#include "fuzzy.hpp"
#include "mtsptype.hpp"
void FzySCurve(
       FDB* FDBptr,
       double left,
       double flexpoint,
       double right,
       int CurveType,
       int *statusPtr)
    {
      int i;
      char *PgmId="mtfzscs";
      double  swidth,dwidth,memval,temp1;

      *statusPtr=0;
      if((left>right)||(right<flexpoint))
         {
          *statusPtr=1;
          MtsSendError(42,PgmId,FDBptr->FDBid);
          return;
         }
      swidth=right-left;
      dwidth=FDBptr->FDBdomain[1]-FDBptr->FDBdomain[0];
      for(i=0;i<VECMAX;i++)
         {
          memval=FDBptr->FDBdomain[0]+(float)i/(VECMAX-1)*dwidth;
          if(memval>=right)
              FDBptr->FDBvector[i]=1.00;
            else
          if(memval>flexpoint)
             {
              temp1=(memval-right)/swidth;
              FDBptr->FDBvector[i]=(float)(1-(2*(pow(temp1,2))));
             }
            else
          if(memval>left)
             {
              temp1=(memval-left)/swidth;
              FDBptr->FDBvector[i]=(float)(2*(pow(temp1,2)));
             }
            else
             FDBptr->FDBvector[i]=0.0;
         }
      if(CurveType==DECLINE)
         for(i=0;i<VECMAX;i++)
            FDBptr->FDBvector[i]=1-FDBptr->FDBvector[i];
      FDBptr->FDBgentype=CurveType;
      FDBptr->FDBparms[0]=left;
      FDBptr->FDBparms[1]=flexpoint;
      FDBptr->FDBparms[2]=right;
      return;
    }
