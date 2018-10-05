/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdcen.cpp  Earl Cox  04/01/93 Get Modelling Environment.  |
| This routine looks at the current XSYSctl block and returns |
| the identifiers of the currently active model and policy.   |
| If a complete model, policy ennvironment is not active an   |
| error condition is returned.                                |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdlib.h>
#include "MDB.hpp"
#include "PDB.hpp"
#include <XSYSctl.hpp>
#include   <mtypes.hpp>
#include <mtsptype.hpp>
void MdlGetcurrentEnvironment(MDB **MDBptr,PDB **PDBptr,int *statusPtr)
 {
  char  *PgmId="mtmdcen";

  *statusPtr=0;
  if((*MDBptr=XSYSctl.XSYScurrMDBptr)==NULL)
    {
     *statusPtr=1;
     MtsSendError(101,PgmId,"");
     return;
    }
  if((*PDBptr=XSYSctl.XSYScurrPDBptr)==NULL)
    {
     *statusPtr=3;
     MtsSendError(102,PgmId,"");
     return;
    }
  return;
 }
void MdlSetcurrentEnvironment(MDB *MDBptr,PDB *PDBptr,int *statusPtr)
 {
  char  *PgmId="mtmdcen";

  *statusPtr=0;
  if(XSYSctl.XSYScurrMDBptr!=NULL) XSYSctl.XSYScurrMDBptr=MDBptr;
  if(XSYSctl.XSYScurrPDBptr==NULL) XSYSctl.XSYScurrPDBptr=PDBptr;
  return;
 }
