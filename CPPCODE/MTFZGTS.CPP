/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzgts.cpp   Earl Cox  04/01/93 Get the Scalar Value from  |
| at fuzzy set. Given the domain of a fuzzy set and a specific|
| cell in the vector, this routine returns the scalar value   |
| corresponding to that vector cell.                          |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include "FDB.hpp"
#include "mtypes.hpp"
#include "mtsptype.hpp"
double FzyGetScalar(const FDB* FDBptr,const int CellNo,int* statusPtr)
 {
   char *PgmId="mtfzgts";
   *statusPtr=1;
   if(CellNo<0||CellNo>VECMAX)
     {
      *statusPtr=1;
      MtsSendError(48,PgmId,MtsFormatInt(CellNo));
     }
   *statusPtr=0;
   double Range=FDBptr->FDBdomain[1]-FDBptr->FDBdomain[0];
   double Scalar=FDBptr->FDBdomain[0]+(CellNo*Range)/(VECMAX-1);
   return(Scalar);
 }
