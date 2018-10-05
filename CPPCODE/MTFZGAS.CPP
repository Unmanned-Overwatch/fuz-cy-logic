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
#include <fdb.hpp>
#include   <mtypes.hpp>
void FzyGaussianCurve(
  FDB *FDBptr,double Center,double WFactor,int *statusPtr)
 {
  int    i;
  double dwidth=FDBptr->FDBdomain[1]-FDBptr->FDBdomain[0];
  double thisScalar,GaussPt;

  *statusPtr=0;
  for(i=0;i<VECMAX;i++)
    {
     thisScalar=FDBptr->FDBdomain[0]+(float)i/(VECMAX-1)*dwidth;
     GaussPt=-WFactor*pow((Center-thisScalar),2);
     FDBptr->FDBvector[i]=(float)pow(E,GaussPt);
    }
  return;
 }
