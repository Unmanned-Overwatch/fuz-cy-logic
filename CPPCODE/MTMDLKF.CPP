/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdlkf.cpp  Earl Cox  04/01/93 Link Fuzzyset to Policy     |
| This function takes a fdb and links it into the hash        |
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
#include "PDB.hpp"
#include <fdb.hpp>
#include   <mtypes.hpp>
#include <mtsptype.hpp>
void MdlLinkFDB(FDB *FDBptr,PDB *PDBptr,int *statusPtr)
 {
  FDB    *FDBwrkptr;
  char   *PgmId="mtmdlkf";
  char    Fsetid[IDENLEN+1];
  long    slot;

  *statusPtr=0;
//
//--Copy the fuzzy set identifier into a working area. We use
//--this with the hashing function to generate an address in
//--the PDB fuzzy set dictionary.
  strcpy(Fsetid,FDBptr->FDBid);
  slot=MtsHashString(Fsetid,FDBmax);
  if(slot<0||slot>FDBmax)
    {
     *statusPtr=1;
     MtsSendError(97,PgmId,Fsetid);
     return;
    }
//
//--Look at the fdb doctionary slot. If it's empty, then
//--simply link in the fuzzy set and return. Otherwise, find
//--the last node and link this one into the end of the chain.
  FDBwrkptr=PDBptr->PDBfuzzysets[slot];
  if(FDBwrkptr==NULL)
    {
     PDBptr->PDBfuzzysets[slot]=FDBptr;
     return;
    }
  for(;;)
    {
     if(strcmp(FDBwrkptr->FDBid,FDBptr->FDBid)==0)
       {
        *statusPtr=3;
        MtsSendError(65,PgmId,FDBptr->FDBid);
        return;
       }
     if(FDBwrkptr->FDBnext==NULL)   // Is there a next fdb node?
       {                            // No...
        FDBwrkptr->FDBnext=FDBptr;  // Link this fdb into chain
        return;                     // Return to caller
       }
     FDBwrkptr=FDBwrkptr->FDBnext;  // Move to next fdb node in chain
    }
 }
