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
#include <FuzzysetDescriptor.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
double FzyMonotonicLogic(
  FuzzysetDescriptor *fromFuzzysetDescriptorptr,FuzzysetDescriptor *toFuzzysetDescriptorptr,
    double fromValue,float *PremiseTruth,int *statusPtr)
 {
  int     Idxpos;
  float   PTruth;
  double  Scalar;

  *statusPtr=0;
  PTruth=FzyGetMembership(fromFuzzysetDescriptorptr,fromValue,&Idxpos,statusPtr);
  Scalar=FzyEquivalentScalar(toFuzzysetDescriptorptr,PTruth,statusPtr);
  *PremiseTruth=PTruth;
  return(Scalar);
 }
