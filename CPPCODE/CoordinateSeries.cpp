/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtfzcds.cpp   Earl Cox  04/01/93 Coodinate data series      |
| This procedure creates a fuzzy set from a series of domain  |
| values and associated truth memberships. The procedure      |
| follows the same line as the membership series creator by   |
| finding the scalar (Values[i]) in the membership array and  |
| setting that cell to the truth. All other cells are set to  |
| minus one (-1). We then simply call the series expander.    |
*-------------------------------------------------------------*/
#include <FuzzysetDescriptor.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
void FzyCoordSeries(
  FuzzysetDescriptor* FuzzysetDescriptorptr,
   double Scalars[],float Grades[],const int ValCnt,int *statusPtr)
  {
   int     i,Cellpos;
   double  Hi,Lo,Range;
   float   tempVector[VECMAX+1];
   bool    Normalset;

   *statusPtr=0;
   Hi=FuzzysetDescriptorptr->FuzzysetDescriptordomain[1];
   Lo=FuzzysetDescriptorptr->FuzzysetDescriptordomain[0];
   Range=Hi-Lo;
   Normalset=FALSE;
   FzyInitVector(tempVector,VECMAX,MINUSONE);
   for(i=0;i<ValCnt;i++)
    {
//   Cellpos=((Scalars[i]-Lo)*(VECMAX-1))/Range;
     Cellpos=(int)(((Scalars[i]-Lo)/Range)*VECMAX);
     tempVector[Cellpos]=Grades[i];
     if(Grades[i]==1.0) Normalset=TRUE;
    }
   if(tempVector[0]==-1) tempVector[0]=0.0;
   FzyInterpVec(tempVector,statusPtr);
// if(*statusPtr!=0) return;
   FzyCopyVector(FuzzysetDescriptorptr->FuzzysetDescriptorvector,tempVector,VECMAX);
   if(Normalset==FALSE) FzyNormalizeSet(FuzzysetDescriptorptr);
   return;
  }
