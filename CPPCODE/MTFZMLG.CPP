/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzmlg.cpp  Earl Cox  04/01/93 Monotonic Reasoning         |
| In monotonic or proportional fuzzy reasoning the value of   |
| the model state is implicitly determined by the truth values|
| in two related fuzzy regions/                               |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <fdb.hpp>
#include   <mtypes.hpp>
#include <mtsptype.hpp>
double FzyMonotonicLogic(
  FDB *fromFDBptr,FDB *toFDBptr,
    double fromValue,float *PremiseTruth,int *statusPtr)
 {
  int     Idxpos;
  float   PTruth;
  double  Scalar;

  *statusPtr=0;
  PTruth=FzyGetMembership(fromFDBptr,fromValue,&Idxpos,statusPtr);
  Scalar=FzyEquivalentScalar(toFDBptr,PTruth,statusPtr);
  *PremiseTruth=PTruth;
  return(Scalar);
 }
