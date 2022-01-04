/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdfdv.cpp  Earl Cox  04/01/93 Find Variable in Policy     |
| This function takes a character string containing the name  |
| of a variable in the policy's  dictionary. On finding the   |
| variable, we return the VariableDescriptor address.                        |
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
VariableDescriptor *MdlFindVariableDescriptor(char *Varid,PDB *PDBptr,int *statusPtr)
 {
  VariableDescriptor    *VariableDescriptorptr,*VariableDescriptornull=NULL;
  char   *PgmId="mtmdfdv";
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
     return(VariableDescriptornull);
    }
//
//--Look at the VariableDescriptor doctionary slot. If it's empty, then
//--return a null pointer saying that the variable doesn't
//--exist. Otherwise look through the remainder of the chain
//--for the variable name until we come to the chain end.
  *statusPtr=3;
  VariableDescriptorptr=PDBptr->PDBvariables[slot];
  if(VariableDescriptorptr==NULL) return(VariableDescriptornull);
  for(;;)
    {
     if(strcmp(VariableDescriptorptr->VariableDescriptorid,Varid)==0)
       {
        *statusPtr=0;
        return(VariableDescriptorptr);
       }
     if(VariableDescriptorptr->VariableDescriptornext==NULL) return(VariableDescriptornull);
     VariableDescriptorptr=VariableDescriptorptr->VariableDescriptornext;
    }
 }
