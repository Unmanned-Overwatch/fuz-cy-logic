/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfziss.cpp  Earl Cox  04/01/93 Is "x" a member of set "Y"  |
| This routine determines whether or not a scalar value 'x' is|
| a member of a particular fuzzy set 'Y', and, if so, returns |
| a boolean result along with its membership grade.           |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <fdb.hpp>
#include   <fuzzy.hpp>
#include   <mtypes.hpp>
#include <XSYSctl.hpp>
#include <mtsptype.hpp>
bool FzyIsMemberof(FDB *FDBptr,double Scalar,float *grade,int *statusPtr)
 {
  int  i;
  *statusPtr=0;
//--a scalar is not a member of the fuzzy set if its actual or its
//--extended membership value is zero. An extended or implied membership
//--is a value that falls along the projected zero membership axis.
  *grade=FzyGetMembership(FDBptr,Scalar,&i,statusPtr);
  if(*grade==0) return(FALSE);
  if(*grade<XSYSctl.XSYSalfacut) return(FALSE);
  return(TRUE);
 }
