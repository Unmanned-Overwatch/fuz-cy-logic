/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzfhp.cpp   Earl Cox  04/01/93 Find Set heigh point.      |
| This routine finds the high point in a fuzzy set. We use    |
| this when the point of defuzzification is zero.             |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include "fuzzy.hpp"
#include "FDB.hpp"
int FzyGetHighPoint(FDB* FDBptr,float *height)
  {
   int i,hipoint;
   *height=0;
   float max_memval=FDBptr->FDBvector[0];
   hipoint         =0;
   for(i=0;i<VECMAX;i++)
      if(FDBptr->FDBvector[i]>max_memval)
        {
          max_memval=FDBptr->FDBvector[i];
          hipoint=i;
        }
   *height=hipoint;
   return(hipoint);
  }
