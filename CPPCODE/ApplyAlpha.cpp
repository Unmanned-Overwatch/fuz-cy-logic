/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtfzapa.cpp    Earl Cox   4/01/93  Applying an Alfa Cut to  |
| a fuzzy region. This routine set any value below the current|
| cut to zero.                                                |
*-------------------------------------------------------------*/
#include <fdb.hpp>
#include   <fuzzy.hpp>
#include <mtsptype.hpp>
void FzyApplyAlfa(FDB* FDBptr,const float Alfa,const int AlfaType)
   {
     int i;
     for(i=0;i<VECMAX;i++)
       if(!FzyAboveAlfa(FDBptr->FDBvector[i],Alfa,AlfaType))
             FDBptr->FDBvector[i]=0;
   }
