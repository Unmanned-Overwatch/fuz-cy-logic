/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzhdi.cpp   Earl Cox  04/01/93 Initialize a hedge block   |
| This routine takes a pointer to a hedge description block   |
| and sets all the slots to their default values.             |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <HDB.hpp>
#include   <mtypes.hpp>
void FzyInitHDB(HDB *HDBptr)
 {
  memset(HDBptr->HDBid,  '\0',IDENLEN+1);
  memset(HDBptr->HDBdesc,'\0',DESCLEN+1);
  HDBptr->HDBmode     =0;
  HDBptr->HDBop       =0;
  HDBptr->HDBvalue    =0;
  HDBptr->HDBnext     =NULL;
 }
