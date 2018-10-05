/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdlkm.cpp  Earl Cox  04/01/93 Link in Active Model        |
| This function takes a MDB and links it into the XSYSctl     |
| external block as the active model. We give this action a   |
| symmetrical name so that if we decide to allow multiple,    |
| active models nothing changes for the user.                 |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <stddef.h>
#include "MDB.hpp"
#include <XSYSctl.hpp>
#include   <mtypes.hpp>
#include <mtsptype.hpp>
void MdlLinkMDB(MDB *MDBptr,bool ReqdLink,int *statusPtr)
 {
  MDB    *wrkMDBptr;
  char    wrkBuff[128];

  *statusPtr=0;
  if(XSYSctl.XSYScurrMDBptr!=NULL)
    {
     *statusPtr=9;
     wrkMDBptr=XSYSctl.XSYScurrMDBptr;
     sprintf(wrkBuff,"%s%s%s",
       "WARNING. Model '",wrkMDBptr->MDBid,"' is already active!");
      MtsWritetoLog(SYSMODFILE,wrkBuff,statusPtr);
      if(!ReqdLink) return;
    }
  *statusPtr=0;
  XSYSctl.XSYScurrMDBptr=MDBptr;
  return;
 }
