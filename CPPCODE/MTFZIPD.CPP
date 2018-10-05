/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzipd.cpp  Earl Cox  04/01/93 Isolate Possibility density |
| Region. This function is used with the preponderance of     |
| evidence routine to house the user's own code for limiting  |
| the underlying fuzzy region for centroid defuzzification.   |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include "FDB.hpp"
#include "mtypes.hpp"
void FzyIsolatePDR(FDB *FDBptr)
 {
  //--limit the non-zero region of the fuzzy truth membership array
  //--to those cells that exceed the minimum possibility density for
  //--this kind of policy.
  //
  //--this is an exit for user code
  return;
 }
