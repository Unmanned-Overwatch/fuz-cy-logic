/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdpcr.cpp  Earl Cox  04/01/93 Create a Policy             |
| This procedure allocates and initializes a Policy Descriptor|
| Block (PDB) and returns its address.                        |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stddef.h>
#include <string.h>
#include "PDB.hpp"
#include "mtypes.hpp"
#include "mtsptype.hpp"
void Complete_Policy(const PDB*);
PDB *MdlCreatePolicy(char *Polid,int StoreAction,int *statusPtr)
 {
  PDB*    PDBptr;
  char   *PgmId="mtmdpcr";

  *statusPtr=0;
  PDBptr=NULL;
//--Create a new policy and initialize it to the default state
  if(!(PDBptr=new PDB))
    {
     *statusPtr=1;
     MtsSendError(2,PgmId,Polid);
     return(PDBptr);
    }
   MdlInitPDB(PDBptr);
//
//--Now copy in the parameters to complete the general properties
//--of the Policy
    strcpy(PDBptr->PDBid,Polid);
    if(StoreAction==MODELADD)   MdlLinkPDB(PDBptr,statusPtr);
    Complete_Policy(PDBptr);
    return(PDBptr);
  }
void Complete_Policy(const PDB* PDBptr)
 {
  int     status;
  char    wrkBuff[180];

  sprintf(wrkBuff,"%s%s%s","Policy '",PDBptr->PDBid,"' created.");
  MtsWritetoLog(SYSMODFILE,wrkBuff,&status);
  return;
 }
