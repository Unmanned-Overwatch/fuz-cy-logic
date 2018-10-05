/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdrmv.cpp  Earl Cox  04/01/93 Remove variable in Policy   |
| This function takes a character string containing the name  |
| of a variable  in the policy's  dictionary. On finding the  |
| variable  we delete it and fix up the links.                |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <stddef.h>
#include <PDB.hpp>
#include "VDB.hpp"
#include   <mtypes.hpp>
#include <mtsptype.hpp>
void MdlRemoveVDB(char *Varid,PDB *PDBptr,int *statusPtr)
 {
  VDB    *VDBptr,*VDBprevptr=NULL;
  char   *PgmId="mtmdrmf";
  long    slot;

  *statusPtr=0;
//
//--Now hash the variable name to get its slot location in
//--the PDB's variable dictionary.
  slot=MtsHashString(Varid,VDBmax);
  if(slot<0||slot>VDBmax)
    {
     *statusPtr=1;
     MtsSendError(97,PgmId,Varid);
     return;
    }
//
//--Look at the VDB doctionary slot. If it's empty, then
//--return a null pointer saying that the fuzzyset doesn't
//--exist. Otherwise look through the remainder of the chain
//--for the variable name until we come to the chain end.
  *statusPtr=3;
  VDBptr=PDBptr->PDBvariables[slot];
  if(VDBptr==NULL) return;
  for(;;)
    {
     if(strcmp(VDBptr->VDBid,Varid)==0)
       {
        *statusPtr=0;
        if(VDBprevptr==NULL)
          {
           PDBptr->PDBvariables[slot]=VDBptr->VDBnext;
           delete VDBptr;
           return;
          }
        VDBprevptr->VDBnext=VDBptr->VDBnext;
        delete VDBptr;
        return;
       }
     VDBprevptr=VDBptr;
     if(VDBptr->VDBnext==NULL) return;
     VDBptr=VDBptr->VDBnext;
    }
 }
