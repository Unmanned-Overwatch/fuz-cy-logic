/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzlns.cpp   Earl Cox  04/01/93  Create a Linear Fuzzy Set.|
| This routine will create an increasing or decreasing linear |
| fuzzy region from the two end points.                       |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include   <fuzzy.hpp>
#include <FuzzysetDescriptor.hpp>
#include <SystemPrototypes.hpp>
void FzyLinearCurve(
  FuzzysetDescriptor* FuzzysetDescriptorptr,double low,double high,int LineType,int *statusPtr)
  {
    int     i,j;
    double  swidth,
            dwidth,
            memval;
    char   *PgmId="mtfzlns";

    *statusPtr=0;
    if((low==high)||(low>high))
      {
       *statusPtr=1;
       MtsSendError(36,PgmId,FuzzysetDescriptorptr->FuzzysetDescriptorid);
       return;
      }
    swidth=high-low;
    dwidth=FuzzysetDescriptorptr->FuzzysetDescriptordomain[1]-FuzzysetDescriptorptr->FuzzysetDescriptordomain[0];
    for(i=0;i<VECMAX;i++)
       {
        memval=FuzzysetDescriptorptr->FuzzysetDescriptordomain[0]+(float)i/VECMAX*dwidth;
        FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=0.0;
        if(memval>high) FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=1.00;
          else if(memval>low)
                FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=(float)((memval-low)/swidth);
       }
    if(LineType==DECREASE)
       for(j=0;j<VECMAX;j++)
          FuzzysetDescriptorptr->FuzzysetDescriptorvector[j]=1-FuzzysetDescriptorptr->FuzzysetDescriptorvector[j];
    FuzzysetDescriptorptr->FuzzysetDescriptorgentype=LineType;
    FuzzysetDescriptorptr->FuzzysetDescriptorparms[0]=low;
    FuzzysetDescriptorptr->FuzzysetDescriptorparms[1]=high;
    return;
  }
