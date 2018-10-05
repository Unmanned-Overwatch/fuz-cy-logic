/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzmss.cpp   Earl Cox  04/01/93 Create a Fuzzy Set from a  |
| series of membership truth values. Given a minimum of three |
| truth function points in the interval [0,1], we spread them |
| equi-distantly across the vector, fill in the empty cells   |
| with "-1" and call the interpolator.                        |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <fdb.hpp>
#include   <fuzzy.hpp>
#include   <mtypes.hpp>
#include <mtsptype.hpp>
void FzyMemSeries(
      FDB* FDBptr,float TruthSeries[],const int Scnt,int *statusPtr)
   {
    bool   Normal;
    int    i,
           j,
           Serlen,
           remaining;
    float  TempVector[VECMAX];

    *statusPtr=0;
    Normal=FALSE;
    for(i=0;i<Scnt;i++)
      if(TruthSeries[i]==1.0) Normal=TRUE;
    if(!Normal) {*statusPtr=1;return;}
    FzyInitVector(TempVector,VECMAX,MINUSONE);
    TempVector[0]=TruthSeries[0];
    Serlen=Scnt-1;
    for(remaining=1;remaining<Serlen+1;remaining++)
       {
        j=(int)(BUMP+((float)remaining/(float)Serlen)*(VECMAX-1));
        if(j>VECMAX) {*statusPtr=66; return;}
        TempVector[j]=TruthSeries[remaining];
       }
    FzyInterpVec(TempVector,statusPtr);
    if(*statusPtr!=0) {*statusPtr=88;return;}
    FzyCopyVector(FDBptr->FDBvector,TempVector,VECMAX);
    return;
   }
