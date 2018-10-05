/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdlkp.cpp  Earl Cox  04/01/93 Link Policy into Model.     |
| This function takes a PDB and links it into the hash        |
| dictionary of the XSYSctl block. Every model can be composed|
| of many different Policies, each with its own internal      |
| organization of variables, rules, fuzzy sets, hedges, etc.  |
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
#include   <mtypes.hpp>
#include <mtsptype.hpp>
void MdlLinkPDB(PDB *PDBptr,int *statusPtr)
 {
  PDB    *PDBwrkptr;
  char   *PgmId="mtmdlkp";
  char    Polid[IDENLEN+1];
  long    slot;

  *statusPtr=0;
//
//--Copy the policy identifier into a working area. We use
//--this with the hashing function to generate an address in
//--the XSYSctl policy dictionary.
  strcpy(Polid,PDBptr->PDBid);
  slot=MtsHashString(Polid,PDBmax);
  if(slot<0||slot>PDBmax)
    {
     *statusPtr=1;
     MtsSendError(97,PgmId,Polid);
     return;
    }
//
//--Look at the PDB dictionary slot. If it's empty, then
//--simply link in the PDB and return. Otherwise, find
//--the last node and link this one into the end of the chain.
  PDBwrkptr=XSYSctl.XSYSpolicies[slot];
  if(PDBwrkptr==NULL)
    {
     XSYSctl.XSYSpolicies[slot]=PDBptr;
     XSYSctl.XSYScurrPDBptr=PDBptr;
     return;
    }
  for(;;)
    {
     if(strcmp(PDBwrkptr->PDBid,PDBptr->PDBid)==0)
       {
        *statusPtr=3;
        MtsSendError(65,PgmId,PDBptr->PDBid);
        return;
       }
     if(PDBwrkptr->PDBnext==NULL)   // Is there a next PDB node?
       {                            // No...
        PDBwrkptr->PDBnext=PDBptr;  // Link this PDB into chain
        XSYSctl.XSYScurrPDBptr=PDBptr;
        return;                     // Return to caller
       }
     PDBwrkptr=PDBwrkptr->PDBnext;  // Move to next PDB node in chain
    }
 }
