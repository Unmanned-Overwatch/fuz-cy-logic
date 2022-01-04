/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdmvp.cpp  Earl Cox  04/01/93  Make a Virtual Policy.     |
| A "virtual" policy is one that is created 'out of thin air' |
| that is, it doesn't exist in the repository. This type of   |
| service is need for embedded programming.                   |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "MDB.hpp"
#include <PDB.hpp>
#include <XSYSctl.hpp>
#include   <mtypes.hpp>
#include <mtsptype.hpp>
PDB *MdlMakeVirtualModel(char *Policyid,char *Policydesc,int *statusPtr)
 {
  PDB     *PDBptr,*nullPDB=NULL;
  ModelDescription     *MDBptr;
  char    *PgmId="mtmdmvp";
  char    wrkbuff[120];

  *statusPtr=0;
  if(XSYSctl.XSYScurrMDBptr==NULL)
    {
     *statusPtr=1;
     MtsSendError(101,PgmId,Policyid);
     return(nullPDB);
    }
  MDBptr=XSYSctl.XSYScurrMDBptr;
  if(!(PDBptr=new PDB))
    {
     *statusPtr=1;
     MtsSendError(2,PgmId,Policyid);
     return(nullPDB);
    }
  MdlInitPDB(PDBptr);
  strcpy(PDBptr->PDBid,Policyid);
  strcpy(PDBptr->PDBdesc,Policydesc);
  MdlLinkPDB(PDBptr,statusPtr);
  sprintf(wrkbuff,"%s%s%s%s","FMSNote(35): Virtual Policy '",Policyid,
   "' inserted into Model: ",MDBptr->MDBid);
  MtsWritetoLog(SYSLOGFILE,wrkbuff,statusPtr);
  return(PDBptr);
 }
