/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtfzapa.cpp    Earl Cox   4/01/93  Applying an Alfa Cut to  |
| a fuzzy region. This routine set any value below the current|
| cut to zero.                                                |
*-------------------------------------------------------------*/
#include <FuzzysetDescriptor.hpp>
#include   <fuzzy.hpp>
#include <SystemPrototypes.hpp>
void FzyApplyAlfa(FuzzysetDescriptor* FuzzysetDescriptorptr,const float Alfa,const int AlfaType)
   {
     int i;
     for(i=0;i<VECMAX;i++)
       if(!FzyAboveAlfa(FuzzysetDescriptorptr->FuzzysetDescriptorvector[i],Alfa,AlfaType))
             FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=0;
   }
