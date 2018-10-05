/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtvrafd.cpp  Earl Cox  04/01/93 Attach FDB to VDB           |
| This function inserts a fuzzy set description into the      |
| specified variable descriptor.                              |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include "FDB.hpp"
#include "VDB.hpp"
#define  FzysetMax  16
void VarAttachFDB(FDB *FDBptr,VDB *VDBptr,int *statusPtr)
 {
  *statusPtr=0;
  int fcnt=VDBptr->VDBfsetcnt;
  if(fcnt==FzysetMax)
    {
     *statusPtr=1;
     return;
    }
   fcnt++;
   VDBptr->VDBfuzzysets[fcnt]=FDBptr;
   VDBptr->VDBfsetcnt=fcnt;
   return;
 }
