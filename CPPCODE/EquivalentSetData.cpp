/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzesd.cpp  Earl Cox  04/01/93 Extract fuzzy set data      |
| This function is used to create two vectors of domain and   |
| truth membership values from a fuzzy set. You can also      |
| specify a compression factor.                               |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <FuzzysetDescriptor.hpp>
#include   <fuzzy.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
void FzyExtractSetdata(
  FDB   *FDBptr,       // target fuzzy set
  int    CompFactor,   // compression factor
  double Domain[],     // table of domain values
  float  TFvalue[],    // table of membership values
  int   *Extcnt,       // count of table entries
  int   *statusPtr)    // function status code
 {
  int i,j=0;

  *statusPtr=0;
  for(i=0;i<VECMAX;i+=CompFactor)
    {
     Domain[j] =FzyGetScalar(FDBptr,i,statusPtr);
     TFvalue[j]=FDBptr->FDBvector[i];
     j++;
    }
  *Extcnt=j;
  return;
 }
