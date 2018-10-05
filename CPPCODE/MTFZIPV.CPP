/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzipv.cpp   Earl Cox  04/01/93 Interpolate across a truth |
| vector. This routines creates a fuzzy surface by linear     |
| interpolation between vector segments. An empty segment is  |
| indicated by a series of "-1" values.                       |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include   <fuzzy.hpp>
#include   <mtypes.hpp>
#include <mtsptype.hpp>
void FzyInterpVec(float TempVector[],int *statusPtr)
   {
    int    i,j,k,Pnt1,Pnt2;
    float  y,Seg1,Seg2;
    char  *PgmId="mtfzipv";

    i=0;
    j=0;
//--This loop moves across the vector until it find a slot that
//--does not contain a -1. We then linearly interpolate between
//--the previous bounary and this cell.
    interpolate:
     j++;
     if(j>VECMAX)
       {
        *statusPtr=1;
        MtsSendError(48,PgmId,MtsFormatInt(j));
        return;
       }
     if(TempVector[j]==-1) goto interpolate;
//--OKay, lets interpolate. The idea here is very simple,
//--we calculate "y" as the proportion of the distance
//--from the anchor point to the current point (k). We then
//--multiply this with the linear distance between the two
//--points.
       Pnt1=i+1;
       Pnt2=j;
       for(k=Pnt1;k<Pnt2+1;k++)
         {
          Seg1=k-i;
          Seg2=j-i;
          y=Seg1/Seg2;
          if(k>VECMAX) {*statusPtr=77;return;}
          TempVector[k]=
             TempVector[i]+y*(TempVector[j]-TempVector[i]);
         }
       i=j;
       if(i>=VECMAX) return;
     goto interpolate;
   }
