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
#include "VariableDescriptor.hpp"
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
void MdlRemoveVariableDescriptor(char *Varid,PDB *PDBptr,int *statusPtr)
 {
  VariableDescriptor    *VariableDescriptorptr,*VariableDescriptorprevptr=NULL;
  char   *PgmId="mtmdrmf";
  long    slot;

  *statusPtr=0;
//
//--Now hash the variable name to get its slot location in
//--the PDB's variable dictionary.
  slot=MtsHashString(Varid,VariableDescriptormax);
  if(slot<0||slot>VariableDescriptormax)
    {
     *statusPtr=1;
     MtsSendError(97,PgmId,Varid);
     return;
    }
//
//--Look at the VariableDescriptor doctionary slot. If it's empty, then
//--return a null pointer saying that the fuzzyset doesn't
//--exist. Otherwise look through the remainder of the chain
//--for the variable name until we come to the chain end.
  *statusPtr=3;
  VariableDescriptorptr=PDBptr->PDBvariables[slot];
  if(VariableDescriptorptr==NULL) return;
  for(;;)
    {
     if(strcmp(VariableDescriptorptr->VariableDescriptorid,Varid)==0)
       {
        *statusPtr=0;
        if(VariableDescriptorprevptr==NULL)
          {
           PDBptr->PDBvariables[slot]=VariableDescriptorptr->VariableDescriptornext;
           delete VariableDescriptorptr;
           return;
          }
        VariableDescriptorprevptr->VariableDescriptornext=VariableDescriptorptr->VariableDescriptornext;
        delete VariableDescriptorptr;
        return;
       }
     VariableDescriptorprevptr=VariableDescriptorptr;
     if(VariableDescriptorptr->VariableDescriptornext==NULL) return;
     VariableDescriptorptr=VariableDescriptorptr->VariableDescriptornext;
    }
 }
