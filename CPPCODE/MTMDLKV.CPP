/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdlkv.cpp  Earl Cox  04/01/93 Link Variable to Policy     |
| This function takes a VDB and links it into the hash        |
| dictionary of a policy. Even though this is a variable      |
| function we keep it under the general modelling functions   |
| for uniformity and control.                                 |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <stddef.h>
#include "PDB.hpp"
#include "VDB.hpp"
#include "mtypes.hpp"
#include "mtsptype.hpp"
void MdlLinkVDB(VDB *VDBptr,PDB *PDBptr,int *statusPtr)
 {
  VDB    *VDBwrkptr;
  char   *PgmId="mtmdlkv";
  char    Varid[IDENLEN+1];
  long    slot;

  *statusPtr=0;
//
//--Copy the variable identifier into a working area. We use
//--this with the hashing function to generate an address in
//--the PDB variable dictionary.
  strcpy(Varid,VDBptr->VDBid);
  slot=MtsHashString(Varid,VDBmax);
  if(slot<0||slot>VDBmax)
    {
     *statusPtr=1;
     MtsSendError(97,PgmId,Varid);
     return;
    }
//
//--Look at the VDB doctionary slot. If it's empty, then
//--simply link in the variable and return. Otherwise, find
//--the last node and link this one into the end of the chain.
  VDBwrkptr=PDBptr->PDBvariables[slot];
  if(VDBwrkptr==NULL)
    {
     PDBptr->PDBvariables[slot]=VDBptr;
     return;
    }
  for(;;)
    {
     if(strcmp(VDBwrkptr->VDBid,VDBptr->VDBid)==0)
       {
        *statusPtr=3;
        MtsSendError(67,PgmId,VDBptr->VDBid);
        return;
       }
     if(VDBwrkptr->VDBnext==NULL)   // Is there a next VDB node?
       {                            // No...
        VDBwrkptr->VDBnext=VDBptr;  // Link this VDB into chain
        return;                     // Return to caller
       }
     VDBwrkptr=VDBwrkptr->VDBnext;  // Move to next VDB node in chain
    }
 }
