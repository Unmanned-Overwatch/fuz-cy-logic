/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzspt.cpp   Earl Cox  04/01/93 The Support Set            |
| The support set of a fuzzy region is the start of the       |
| nonzero domain as measured from the fuzzy set edges.        |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include "FDB.hpp"
#include "mtsptype.hpp"
void FzySupportSet(
       FDB* FDBptr,double Scalars[],int Truth[],int* statusPtr)
  {
   *statusPtr=0;
   int i,j;
   for(i=0;i<VECMAX;i++)
    {
      if(FDBptr->FDBvector[i]>0)
        {
         for(j=VECMAX-1;j>=0;j--)
          {
           if(FDBptr->FDBvector[j]>0)
             {
              Truth[0]  =i;
              Scalars[0]=FzyGetScalar(FDBptr,i,statusPtr);
              Truth[1]  =j;
              Scalars[1]=FzyGetScalar(FDBptr,j,statusPtr);
              return;
             }
          }
        }
    }
  }
