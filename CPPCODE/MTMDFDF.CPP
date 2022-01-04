/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdfdf.cpp  Earl Cox  04/01/93 Find Fuzzyset in Policy     |
| This function takes a character string containing the name  |
| of a fuzzyset in the policy's  dictionary. On finding the   |
| fuzzyset, we return the FuzzysetDescriptor address.                        |
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
FuzzysetDescriptor *MdlFindFuzzysetDescriptor(char *Fzyid,PDB *PDBptr,int *statusPtr)
 {
  FuzzysetDescriptor    *FuzzysetDescriptorptr,*FuzzysetDescriptornull=NULL;
  char   *PgmId="mtmdfdf";
  long    slot;

  *statusPtr=0;
  if(PDBptr==NULL)
    {
     *statusPtr=1;
     MtsSendError(102,PgmId,Fzyid);
     return(FuzzysetDescriptornull);
    }
//
//--Now hash the fuzzy set name to get its slot location in
//--the PDB's fuzzy set dictionary.
  slot=MtsHashString(Fzyid,FuzzysetDescriptormax);
  if(slot<0||slot>FuzzysetDescriptormax)
    {
     *statusPtr=3;
     MtsSendError(97,PgmId,Fzyid);
     return(FuzzysetDescriptornull);
    }
//
//--Look at the FuzzysetDescriptor doctionary slot. If it's empty, then
//--return a null pointer saying that the fuzzyset doesn't
//--exist. Otherwise look through the remainder of the chain
//--for the fuzzy set name until we come to the chain end.
  *statusPtr=5;
  FuzzysetDescriptorptr=PDBptr->PDBfuzzysets[slot];
  if(FuzzysetDescriptorptr==NULL) return(FuzzysetDescriptornull);
  for(;;)
    {
     if(strcmp(FuzzysetDescriptorptr->FuzzysetDescriptorid,Fzyid)==0)
       {
        *statusPtr=0;
        return(FuzzysetDescriptorptr);
       }
     if(FuzzysetDescriptorptr->FuzzysetDescriptornext==NULL) return(FuzzysetDescriptornull);
     FuzzysetDescriptorptr=FuzzysetDescriptorptr->FuzzysetDescriptornext;
    }
 }
