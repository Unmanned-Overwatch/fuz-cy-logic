/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdfdf.cpp  Earl Cox  04/01/93 Find Fuzzyset in Policy     |
| This function takes a character string containing the name  |
| of a fuzzyset in the policy's  dictionary. On finding the   |
| fuzzyset, we return the fdb address.                        |
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
FDB *MdlFindFDB(char *Fzyid,PDB *PDBptr,int *statusPtr)
 {
  FDB    *FDBptr,*FDBnull=NULL;
  char   *PgmId="mtmdfdf";
  long    slot;

  *statusPtr=0;
  if(PDBptr==NULL)
    {
     *statusPtr=1;
     MtsSendError(102,PgmId,Fzyid);
     return(FDBnull);
    }
//
//--Now hash the fuzzy set name to get its slot location in
//--the PDB's fuzzy set dictionary.
  slot=MtsHashString(Fzyid,FDBmax);
  if(slot<0||slot>FDBmax)
    {
     *statusPtr=3;
     MtsSendError(97,PgmId,Fzyid);
     return(FDBnull);
    }
//
//--Look at the fdb doctionary slot. If it's empty, then
//--return a null pointer saying that the fuzzyset doesn't
//--exist. Otherwise look through the remainder of the chain
//--for the fuzzy set name until we come to the chain end.
  *statusPtr=5;
  FDBptr=PDBptr->PDBfuzzysets[slot];
  if(FDBptr==NULL) return(FDBnull);
  for(;;)
    {
     if(strcmp(FDBptr->FDBid,Fzyid)==0)
       {
        *statusPtr=0;
        return(FDBptr);
       }
     if(FDBptr->FDBnext==NULL) return(FDBnull);
     FDBptr=FDBptr->FDBnext;
    }
 }
