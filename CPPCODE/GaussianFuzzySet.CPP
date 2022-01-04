/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzgas.cpp  Earl Cox  04/01/93 Gaussian fuzzy set surface  |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <math.h>
#include <FuzzysetDescriptor.hpp>
#include   <SystemTypes.hpp>
void FzyGaussianCurve(
  FuzzysetDescriptor *FuzzysetDescriptorptr,double Center,double WFactor,int *statusPtr)
 {
  int    i;
  double dwidth=FuzzysetDescriptorptr->FuzzysetDescriptordomain[1]-FuzzysetDescriptorptr->FuzzysetDescriptordomain[0];
  double thisScalar,GaussPt;

  *statusPtr=0;
  for(i=0;i<VECMAX;i++)
    {
     thisScalar=FuzzysetDescriptorptr->FuzzysetDescriptordomain[0]+(float)i/(VECMAX-1)*dwidth;
     GaussPt=-WFactor*pow((Center-thisScalar),2);
     FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=(float)pow(E,GaussPt);
    }
  return;
 }
