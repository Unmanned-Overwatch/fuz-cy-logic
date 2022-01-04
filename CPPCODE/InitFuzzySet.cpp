/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzfdi.cpp   Earl Cox  04/01/93  This procedure initializes|
| a fuzzy set. It is called when ever we create a new set     |
| structure.                                                  |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <FuzzysetDescriptor.hpp>
#include <XSYSctl.hpp>
#include   <SystemTypes.hpp>
#include   <fuzzy.hpp>
void FzyInitFuzzysetDescriptor(FuzzysetDescriptor* FuzzysetDescriptorptr)
  {
   int i;
   memset(FuzzysetDescriptorptr->FuzzysetDescriptorid,  '\0',IDENLEN);
   memset(FuzzysetDescriptorptr->FuzzysetDescriptordesc,'\0',DESCLEN);
   FuzzysetDescriptorptr->FuzzysetDescriptorgentype     = 0;
   FuzzysetDescriptorptr->FuzzysetDescriptorempty       = TRUE;
   FuzzysetDescriptorptr->FuzzysetDescriptororder       = 1;
   FuzzysetDescriptorptr->FuzzysetDescriptordomain[0]   = 0;
   FuzzysetDescriptorptr->FuzzysetDescriptordomain[1]   = 0;
   FuzzysetDescriptorptr->FuzzysetDescriptoralfacut     = XSYSctl.XSYSalfacut;
   for(i=0;i<PARMMAX;i++) FuzzysetDescriptorptr->FuzzysetDescriptorparms[i] =0.0;
   for(i=0;i<VECMAX; i++) FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=0.0;
   FuzzysetDescriptorptr->FuzzysetDescriptornext=NULL;
   return;
  }

