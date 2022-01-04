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
#include <FuzzysetDescriptor.hpp>
#include   <fuzzy.hpp>
#include <SystemPrototypes.hpp>
void FzySCurve(
       FuzzysetDescriptor* FuzzysetDescriptorptr,
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
          MtsSendError(42,PgmId,FuzzysetDescriptorptr->FuzzysetDescriptorid);
          return;
         }
      swidth=right-left;
      dwidth=FuzzysetDescriptorptr->FuzzysetDescriptordomain[1]-FuzzysetDescriptorptr->FuzzysetDescriptordomain[0];
      for(i=0;i<VECMAX;i++)
         {
          memval=FuzzysetDescriptorptr->FuzzysetDescriptordomain[0]+(float)i/(VECMAX-1)*dwidth;
          if(memval>=right)
              FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=1.00;
            else
          if(memval>flexpoint)
             {
              temp1=(memval-right)/swidth;
              FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=(float)(1-(2*(pow(temp1,2))));
             }
            else
          if(memval>left)
             {
              temp1=(memval-left)/swidth;
              FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=(float)(2*(pow(temp1,2)));
             }
            else
             FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=0.0;
         }
      if(CurveType==DECLINE)
         for(i=0;i<VECMAX;i++)
            FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=1-FuzzysetDescriptorptr->FuzzysetDescriptorvector[i];
      FuzzysetDescriptorptr->FuzzysetDescriptorgentype=CurveType;
      FuzzysetDescriptorptr->FuzzysetDescriptorparms[0]=left;
      FuzzysetDescriptorptr->FuzzysetDescriptorparms[1]=flexpoint;
      FuzzysetDescriptorptr->FuzzysetDescriptorparms[2]=right;
      return;
    }
