/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdlkh.cpp  Earl Cox  04/01/93 Link Hedge into Policy      |
| This function takes an HDB and links it into the hash       |
| dictionary of a policy. Every policy has its own            |
| dictionary of hedges (forming the basic surface transformers|
| for the model inside this segment.)                         |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <stddef.h>
#include <PDB.hpp>
#include <HDB.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
void MdlLinkHDB(HDB *HDBptr,PDB *PDBptr,int *statusPtr)
 {
  HDB    *HDBwrkptr;
  char   *PgmId="mtmdlkh";
  char    Hdgid[IDENLEN+1];
  long    slot;

  *statusPtr=0;
//
//--Copy the hedge identifier into a working area. We use
//--this with the hashing function to generate an address in
//--the PDB hedge dictionary.
  strcpy(Hdgid,HDBptr->HDBid);
  slot=MtsHashString(Hdgid,HDBmax);
  if(slot<0||slot>HDBmax)
    {
     *statusPtr=1;
     MtsSendError(97,PgmId,Hdgid);
     return;
    }
//
//--Look at the HDB doctionary slot. If it's empty, then
//--simply link in the hedge and return. Otherwise, find
//--the last node and link this one into the end of the chain.
  HDBwrkptr=PDBptr->PDBhedges[slot];
  if(HDBwrkptr==NULL)
    {
     PDBptr->PDBhedges[slot]=HDBptr;
     return;
    }
  for(;;)
    {
     if(strcmp(HDBwrkptr->HDBid,HDBptr->HDBid)==0)
       {
        *statusPtr=3;
        MtsSendError(66,PgmId,HDBptr->HDBid);
        return;
       }
     if(HDBwrkptr->HDBnext==NULL)   // Is there a next HDB node?
       {                            // No...
        HDBwrkptr->HDBnext=HDBptr;  // Link this HDB into chain
        return;                     // Return to caller
       }
     HDBwrkptr=HDBwrkptr->HDBnext;  // Move to next HDB node in chain
    }
 }
