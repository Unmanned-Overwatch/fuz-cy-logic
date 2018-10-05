/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzeqs.cpp  Earl Cox  04/01/93 Scalar Equivalent to Truth  |
| Given a truth membership gradient, this routine returns a   |
| scalar that best represents a point in the fuzzy set at this|
| truth membership level.                                     |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <fdb.hpp>
#include <mtypes.hpp>
#include <mtsptype.hpp>
double FzyEquivalentScalar(FDB *FDBptr,float Grade,int *statusPtr)
 {
  int    i;
  double scalar=0;

  *statusPtr=0;
  for(i=0;i<VECMAX;i++)
    {
     if(Grade>=FDBptr->FDBvector[i])
       {
        scalar=FzyGetScalar(FDBptr,i,statusPtr);
        return(scalar);
       }
    }
  *statusPtr=1;
  return(scalar);
 }
