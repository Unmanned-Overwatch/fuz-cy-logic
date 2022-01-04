/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdfdp.cpp  Earl Cox  04/01/93 Find Policy in the Model    |
| This function takes a character string containing the name  |
| of a policy and finds it in the model. On finding it, we    |
| return the address of the PDB.                              |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <stddef.h>
#include <PDB.hpp>
#include <XSYSctl.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
PDB *MdlFindPDB(char *Polid,int *statusPtr)
 {
  PDB    *PDBptr,*PDBnull=NULL;
  char   *PgmId="mtmdfdp";
  long    slot;

  *statusPtr=0;
  if(PDBptr==NULL)
    {
     *statusPtr=1;
     MtsSendError(102,PgmId,Polid);
     return(PDBnull);
    }
//
//--Now hash the policy name to get its slot location in
//--the XSYSctl's policy dictionary.
  slot=MtsHashString(Polid,PDBmax);
  if(slot<0||slot>PDBmax)
    {
     *statusPtr=3;
     MtsSendError(97,PgmId,Polid);
     return(PDBnull);
    }
//
//--Look at the PDB doctionary slot. If it's empty, then
//--return a null pointer saying that the policy doesn't
//--exist. Otherwise look through the remainder of the chain
//--for the policy name until we come to the chain end.
  *statusPtr=5;
  PDBptr=XSYSctl.XSYSpolicies[slot];
  if(PDBptr==NULL) return(PDBnull);
  for(;;)
    {
     if(strcmp(PDBptr->PDBid,Polid)==0)
       {
        *statusPtr=0;
        return(PDBptr);
       }
     if(PDBptr->PDBnext==NULL) return(PDBnull);
     PDBptr=PDBptr->PDBnext;
    }
 }
