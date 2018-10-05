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
#include <fdb.hpp>
#include <mtsptype.hpp>
void FzyLinearCurve(
  FDB* FDBptr,double low,double high,int LineType,int *statusPtr)
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
       MtsSendError(36,PgmId,FDBptr->FDBid);
       return;
      }
    swidth=high-low;
    dwidth=FDBptr->FDBdomain[1]-FDBptr->FDBdomain[0];
    for(i=0;i<VECMAX;i++)
       {
        memval=FDBptr->FDBdomain[0]+(float)i/VECMAX*dwidth;
        FDBptr->FDBvector[i]=0.0;
        if(memval>high) FDBptr->FDBvector[i]=1.00;
          else if(memval>low)
                FDBptr->FDBvector[i]=(float)((memval-low)/swidth);
       }
    if(LineType==DECREASE)
       for(j=0;j<VECMAX;j++)
          FDBptr->FDBvector[j]=1-FDBptr->FDBvector[j];
    FDBptr->FDBgentype=LineType;
    FDBptr->FDBparms[0]=low;
    FDBptr->FDBparms[1]=high;
    return;
  }
