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
#include <fdb.hpp>
#include   <mtypes.hpp>
#include <mtsptype.hpp>
void MdlRemoveFDB(char *Fzyid,PDB *PDBptr,int *statusPtr)
 {
  FDB    *FDBptr,*FDBprevptr=NULL;
  char   *PgmId="mtmdrmf";
  long    slot;

  *statusPtr=0;
//
//--Now hash the fuzzy set name to get its slot location in
//--the PDB's fuzzy set dictionary.
  slot=MtsHashString(Fzyid,FDBmax);
  if(slot<0||slot>FDBmax)
    {
     *statusPtr=1;
     MtsSendError(97,PgmId,Fzyid);
     return;
    }
//
//--Look at the fdb doctionary slot. If it's empty, then
//--return a null pointer saying that the fuzzyset doesn't
//--exist. Otherwise look through the remainder of the chain
//--for the fuzzy set name until we come to the chain end.
  *statusPtr=3;
  FDBptr=PDBptr->PDBfuzzysets[slot];
  if(FDBptr==NULL) return;
  for(;;)
    {
     if(strcmp(FDBptr->FDBid,Fzyid)==0)
       {
        *statusPtr=0;
        if(FDBprevptr==NULL)
          {
           PDBptr->PDBfuzzysets[slot]=FDBptr->FDBnext;
           delete FDBptr;
           return;
          }
        FDBprevptr->FDBnext=FDBptr->FDBnext;
        delete FDBptr;
        return;
       }
     FDBprevptr=FDBptr;
     if(FDBptr->FDBnext==NULL) return;
     FDBptr=FDBptr->FDBnext;
    }
 }
