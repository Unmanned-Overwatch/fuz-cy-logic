/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtfzctv.cpp   Earl Cox  04/01/93 This routine copies the    |
| contents of one truth function vector into another vector.  |
*-------------------------------------------------------------*/
#include "fuzzy.hpp"
void FzyCopyVector(float tovector[],float frmvector[],int VecLen)
  {
   int i;
   for(i=0;i<VecLen;i++) tovector[i]=frmvector[i];
   return;
  }
