/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzfhd.cpp   Earl Cox  04/01/93  Free a Hedge              |
| This function takes a pointer to an HDB and releases the    |
| associated storage. Note that it does NOT respect hashing   |
| protocol, so it must never be used to free hedges that are  |
| associated with a Model or a Segment.                       |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <HDB.hpp>
void FzyFreeHDB(HDB **HDBptr,int *statusPtr)
  {
    *statusPtr=0;
    delete *HDBptr;
    *HDBptr=NULL;
    return;
  }
