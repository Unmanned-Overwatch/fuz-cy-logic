/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdlkv.cpp  Earl Cox  04/01/93 Link Variable to Policy     |
| This function takes a VariableDescriptor and links it into the hash        |
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
#include <PDB.hpp>
#include "VariableDescriptor.hpp"
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
void MdlLinkVariableDescriptor(VariableDescriptor *VariableDescriptorptr,PDB *PDBptr,int *statusPtr)
 {
  VariableDescriptor    *VariableDescriptorwrkptr;
  char   *PgmId="mtmdlkv";
  char    Varid[IDENLEN+1];
  long    slot;

  *statusPtr=0;
//
//--Copy the variable identifier into a working area. We use
//--this with the hashing function to generate an address in
//--the PDB variable dictionary.
  strcpy(Varid,VariableDescriptorptr->VariableDescriptorid);
  slot=MtsHashString(Varid,VariableDescriptormax);
  if(slot<0||slot>VariableDescriptormax)
    {
     *statusPtr=1;
     MtsSendError(97,PgmId,Varid);
     return;
    }
//
//--Look at the VariableDescriptor doctionary slot. If it's empty, then
//--simply link in the variable and return. Otherwise, find
//--the last node and link this one into the end of the chain.
  VariableDescriptorwrkptr=PDBptr->PDBvariables[slot];
  if(VariableDescriptorwrkptr==NULL)
    {
     PDBptr->PDBvariables[slot]=VariableDescriptorptr;
     return;
    }
  for(;;)
    {
     if(strcmp(VariableDescriptorwrkptr->VariableDescriptorid,VariableDescriptorptr->VariableDescriptorid)==0)
       {
        *statusPtr=3;
        MtsSendError(67,PgmId,VariableDescriptorptr->VariableDescriptorid);
        return;
       }
     if(VariableDescriptorwrkptr->VariableDescriptornext==NULL)   // Is there a next VariableDescriptor node?
       {                            // No...
        VariableDescriptorwrkptr->VariableDescriptornext=VariableDescriptorptr;  // Link this VariableDescriptor into chain
        return;                     // Return to caller
       }
     VariableDescriptorwrkptr=VariableDescriptorwrkptr->VariableDescriptornext;  // Move to next VariableDescriptor node in chain
    }
 }
