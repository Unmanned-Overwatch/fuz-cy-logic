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
#include   <fuzzy.hpp>
#include <FuzzysetDescriptor.hpp>
int FzyGetHighPoint(FuzzysetDescriptor* FuzzysetDescriptorptr,float *height)
  {
   int i,hipoint;
   *height=0;
   float max_memval=FuzzysetDescriptorptr->FuzzysetDescriptorvector[0];
   hipoint         =0;
   for(i=0;i<VECMAX;i++)
      if(FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]>max_memval)
        {
          max_memval=FuzzysetDescriptorptr->FuzzysetDescriptorvector[i];
          hipoint=i;
        }
   *height=hipoint;
   return(hipoint);
  }
