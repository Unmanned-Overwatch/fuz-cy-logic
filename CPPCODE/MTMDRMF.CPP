/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdrmf.cpp  Earl Cox  04/01/93 Remove Fuzzysets in Policy  |
| This function takes a character string containing the name  |
| of a Fuzzyset  in the policy's dictionary. On finding the   |
| Fuzzyset  we delete it and fix up the links.                |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <stddef.h>
#include <PDB.hpp>
#include <FuzzysetDescriptor.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
void MdlRemoveFuzzysetDescriptor(char *Fzyid,PDB *PDBptr,int *statusPtr)
 {
  FuzzysetDescriptor    *FuzzysetDescriptorptr,*FuzzysetDescriptorprevptr=NULL;
  char   *PgmId="mtmdrmf";
  long    slot;

  *statusPtr=0;
//
//--Now hash the fuzzy set name to get its slot location in
//--the PDB's fuzzy set dictionary.
  slot=MtsHashString(Fzyid,FuzzysetDescriptormax);
  if(slot<0||slot>FuzzysetDescriptormax)
    {
     *statusPtr=1;
     MtsSendError(97,PgmId,Fzyid);
     return;
    }
//
//--Look at the FuzzysetDescriptor doctionary slot. If it's empty, then
//--return a null pointer saying that the fuzzyset doesn't
//--exist. Otherwise look through the remainder of the chain
//--for the fuzzy set name until we come to the chain end.
  *statusPtr=3;
  FuzzysetDescriptorptr=PDBptr->PDBfuzzysets[slot];
  if(FuzzysetDescriptorptr==NULL) return;
  for(;;)
    {
     if(strcmp(FuzzysetDescriptorptr->FuzzysetDescriptorid,Fzyid)==0)
       {
        *statusPtr=0;
        if(FuzzysetDescriptorprevptr==NULL)
          {
           PDBptr->PDBfuzzysets[slot]=FuzzysetDescriptorptr->FuzzysetDescriptornext;
           delete FuzzysetDescriptorptr;
           return;
          }
        FuzzysetDescriptorprevptr->FuzzysetDescriptornext=FuzzysetDescriptorptr->FuzzysetDescriptornext;
        delete FuzzysetDescriptorptr;
        return;
       }
     FuzzysetDescriptorprevptr=FuzzysetDescriptorptr;
     if(FuzzysetDescriptorptr->FuzzysetDescriptornext==NULL) return;
     FuzzysetDescriptorptr=FuzzysetDescriptorptr->FuzzysetDescriptornext;
    }
 }
