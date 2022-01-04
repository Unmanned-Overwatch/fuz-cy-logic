/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzffs.cpp   Earl Cox  04/01/93  Free a Fuzzy Set          |
| This function takes a pointer to an FuzzysetDescriptor and releases the    |
| associated storage. Note that it does NOT respect hashing   |
| protocol, so it must never be used to free fuzzy sets       |
| associated with a Model or a Segment.                       |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <FuzzysetDescriptor.hpp>
void FzyFreeFuzzysetDescriptor(FuzzysetDescriptor **FuzzysetDescriptorptr,int *statusPtr)
  {
    *statusPtr=0;
    delete *FuzzysetDescriptorptr;
    *FuzzysetDescriptorptr=NULL;
    return;
  }
