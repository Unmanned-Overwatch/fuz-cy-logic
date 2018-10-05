/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzscx.cpp   Earl Cox  04/01/93 Statistical Compatibility  |
| Index. This procedure accumulates model execution frame     |
| data and dynamically calculates the statistical compidx     |
| metrix. We also return an indicator of whether or not the   |
| cumulative truth is within the compatibility range.         |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include "FDB.hpp"
#include "fuzzy.hpp"
#include "mtypes.hpp"
#include "CIX.hpp"
bool FzyStatCompIndex(FDB *FDBptr,float ExpValTruth,CIX *CIXptr)
  {
   const bool InCompatible=0;
   const bool   Compatible=1;
   int i;
   float max_tv,
         min_tv;
   max_tv=0.00;
   min_tv=1.00;
   for(i=0;i<VECMAX;i++)
    {
     if(FDBptr->FDBvector[i]>max_tv) max_tv=FDBptr->FDBvector[i];
     if(FDBptr->FDBvector[i]<min_tv) min_tv=FDBptr->FDBvector[i];
    }
   CIXptr->CIXruncount++;
   CIXptr->CIXCummaxTruth+=max_tv;
   CIXptr->CIXCumminTruth+=min_tv;
   CIXptr->CIXCumdeltaTruth+=(max_tv-min_tv);
   CIXptr->CIXCumexpvTruth+=ExpValTruth;
   CIXptr->CIXAvgmaxTruth=   (float)(CIXptr->CIXCummaxTruth/CIXptr->CIXruncount);
   CIXptr->CIXAvgminTruth=   (float)(CIXptr->CIXCumminTruth/CIXptr->CIXruncount);
   CIXptr->CIXAvgdeltaTruth= (float)(CIXptr->CIXCumdeltaTruth/CIXptr->CIXruncount);
   CIXptr->CIXAvgexpvTruth=(float)(CIXptr->CIXCumexpvTruth/CIXptr->CIXruncount);
  if(CIXptr->CIXAvgmaxTruth>CIXptr->CIXMaxTruth) return(InCompatible);
  if(CIXptr->CIXAvgmaxTruth<CIXptr->CIXMinTruth) return(InCompatible);
  return(Compatible);
  }
