/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzucx.cpp   Earl Cox  04/01/93 Unit Compatibility Index   |
| This procedure examines a fuzzy set's truth membership to   |
| see if its height is within the limits imposed by the       |
| compatability brackets. The routine also returns the mean   |
| (average) truth of the membership function.                 |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <FuzzysetDescriptor.hpp>
#include   <fuzzy.hpp>
#include   <SystemTypes.hpp>
bool FzyUnitCompIndex(
   FuzzysetDescriptor* FuzzysetDescriptorptr,float mintv,float maxtv,float* avgtv,float* deltatv)
  {
   const bool InCompatible=0;
   const bool   Compatible=1;
   int i;
   int tvcount = 0;
   float max_tv,
         min_tv,
         sum_tv;
   max_tv=0.00;
   min_tv=1.00;
   sum_tv=0.00;
//
//--examine the truth membership vector. Find the minimum and maximum
//--truth memberships and also the sum of the membership values.
   for(i=0;i<VECMAX;i++)
    {
     if(FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]>max_tv) max_tv=FuzzysetDescriptorptr->FuzzysetDescriptorvector[i];
     if(FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]<min_tv) min_tv=FuzzysetDescriptorptr->FuzzysetDescriptorvector[i];
     ++tvcount;
     sum_tv=sum_tv+FuzzysetDescriptorptr->FuzzysetDescriptorvector[i];
    }
//
//--calculate the unit run compatibility information.
  *avgtv=(sum_tv/tvcount);
  *deltatv=max_tv-min_tv;
  if(max_tv<mintv) return(InCompatible);
  if(max_tv>maxtv) return(InCompatible);
  return(Compatible);
  }
