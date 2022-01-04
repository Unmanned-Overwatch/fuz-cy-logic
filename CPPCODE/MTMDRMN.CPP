/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdrmn.cpp  Earl Cox  04/01/93 Remove Noiseword in Policy  |
| This function takes a character string containing the name  |
| of a NoiseWord in the policy's  dictionary. On finding the  |
| NoiseWord we delete it and fix up the links.                |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <stddef.h>
#include <PDB.hpp>
#include <NDB.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
void MdlRemoveNDB(char *Nwrdid,PDB *PDBptr,int *statusPtr)
 {
  NDB    *NDBptr,*NDBprevptr=NULL;
  char   *PgmId="mtmdrmn";
  long    slot;

  *statusPtr=0;
//
//--Now hash the noise word name to get its slot location in
//--the PDB's noise word dictionary.
  slot=MtsHashString(Nwrdid,NDBmax);
  if(slot<0||slot>NDBmax)
    {
     *statusPtr=1;
     MtsSendError(97,PgmId,Nwrdid);
     return;
    }
//
//--Look at the NDB doctionary slot. If it's empty, then
//--return a null pointer saying that the fuzzyset doesn't
//--exist. Otherwise look through the remainder of the chain
//--for the noise word name until we come to the chain end.
  *statusPtr=3;
  NDBptr=PDBptr->PDBnoise[slot];
  if(NDBptr==NULL) return;
  for(;;)
    {
     if(strcmp(NDBptr->NDBid,Nwrdid)==0)
       {
        *statusPtr=0;
        if(NDBprevptr==NULL)
          {
           PDBptr->PDBnoise[slot]=NDBptr->NDBnext;
           delete NDBptr;
           return;
          }
        NDBprevptr->NDBnext=NDBptr->NDBnext;
        delete NDBptr;
        return;
       }
     NDBprevptr=NDBptr;
     if(NDBptr->NDBnext==NULL) return;
     NDBptr=NDBptr->NDBnext;
    }
 }
