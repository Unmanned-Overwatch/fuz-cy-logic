/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdlkf.cpp  Earl Cox  04/01/93 Link Fuzzyset to Policy     |
| This function takes a FuzzysetDescriptor and links it into the hash        |
| dictionary of a policy. Every policy has its own            |
| dictionary of fuzzy sets (forming the basic vocabulary of   |
| the model in the policy.)                                   |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <PDB.hpp>
#include <FuzzysetDescriptor.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
void MdlLinkFuzzysetDescriptor(FuzzysetDescriptor *FuzzysetDescriptorptr,PDB *PDBptr,int *statusPtr)
 {
  FuzzysetDescriptor    *FuzzysetDescriptorwrkptr;
  char   *PgmId="mtmdlkf";
  char    Fsetid[IDENLEN+1];
  long    slot;

  *statusPtr=0;
//
//--Copy the fuzzy set identifier into a working area. We use
//--this with the hashing function to generate an address in
//--the PDB fuzzy set dictionary.
  strcpy(Fsetid,FuzzysetDescriptorptr->FuzzysetDescriptorid);
  slot=MtsHashString(Fsetid,FuzzysetDescriptormax);
  if(slot<0||slot>FuzzysetDescriptormax)
    {
     *statusPtr=1;
     MtsSendError(97,PgmId,Fsetid);
     return;
    }
//
//--Look at the FuzzysetDescriptor doctionary slot. If it's empty, then
//--simply link in the fuzzy set and return. Otherwise, find
//--the last node and link this one into the end of the chain.
  FuzzysetDescriptorwrkptr=PDBptr->PDBfuzzysets[slot];
  if(FuzzysetDescriptorwrkptr==NULL)
    {
     PDBptr->PDBfuzzysets[slot]=FuzzysetDescriptorptr;
     return;
    }
  for(;;)
    {
     if(strcmp(FuzzysetDescriptorwrkptr->FuzzysetDescriptorid,FuzzysetDescriptorptr->FuzzysetDescriptorid)==0)
       {
        *statusPtr=3;
        MtsSendError(65,PgmId,FuzzysetDescriptorptr->FuzzysetDescriptorid);
        return;
       }
     if(FuzzysetDescriptorwrkptr->FuzzysetDescriptornext==NULL)   // Is there a next FuzzysetDescriptor node?
       {                            // No...
        FuzzysetDescriptorwrkptr->FuzzysetDescriptornext=FuzzysetDescriptorptr;  // Link this FuzzysetDescriptor into chain
        return;                     // Return to caller
       }
     FuzzysetDescriptorwrkptr=FuzzysetDescriptorwrkptr->FuzzysetDescriptornext;  // Move to next FuzzysetDescriptor node in chain
    }
 }
