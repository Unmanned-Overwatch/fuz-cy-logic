/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtvrafd.cpp  Earl Cox  04/01/93 Attach FuzzysetDescriptor to VariableDescriptor           |
| This function inserts a fuzzy set description into the      |
| specified variable descriptor.                              |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <FuzzysetDescriptor.hpp>
#include "VariableDescriptor.hpp"
#define  FzysetMax  16
void VarAttachFuzzysetDescriptor(FuzzysetDescriptor *FuzzysetDescriptorptr,VariableDescriptor *VariableDescriptorptr,int *statusPtr)
 {
  *statusPtr=0;
  int fcnt=VariableDescriptorptr->VariableDescriptorfsetcnt;
  if(fcnt==FzysetMax)
    {
     *statusPtr=1;
     return;
    }
   fcnt++;
   VariableDescriptorptr->VariableDescriptorfuzzysets[fcnt]=FuzzysetDescriptorptr;
   VariableDescriptorptr->VariableDescriptorfsetcnt=fcnt;
   return;
 }
