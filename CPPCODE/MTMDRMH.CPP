/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdrmh.cpp  Earl Cox  04/01/93 Remove Hedge in a Policy    |
| This function takes a character string containing the name  |
| of a Hedge in the policy's  dictionary. On finding the      |
| Hedge we delete it and fix up the links.                    |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <stddef.h>
#include "PDB.hpp"
#include <fdb.hpp>
#include   <mtypes.hpp>
#include <mtsptype.hpp>
void MdlRemoveHDB(char *Hdgid,PDB *PDBptr,int *statusPtr)
 {
  HDB    *HDBptr,*HDBprevptr=NULL;
  char   *PgmId="mtmdrmh";
  long    slot;

  *statusPtr=0;
//
//--Now hash the hedge name to get its slot location in
//--the PDB's hedge dictionary.
  slot=MtsHashString(Hdgid,HDBmax);
  if(slot<0||slot>HDBmax)
    {
     *statusPtr=1;
     MtsSendError(97,PgmId,Hdgid);
     return;
    }
//
//--Look at the HDB doctionary slot. If it's empty, then
//--return a null pointer saying that the fuzzyset doesn't
//--exist. Otherwise look through the remainder of the chain
//--for the hedge name until we come to the chain end.
  *statusPtr=3;
  HDBptr=PDBptr->PDBhedges[slot];
  if(HDBptr==NULL) return;
  for(;;)
    {
     if(strcmp(HDBptr->HDBid,Hdgid)==0)
       {
        *statusPtr=0;
        if(HDBprevptr==NULL)
          {
           PDBptr->PDBhedges[slot]=HDBptr->HDBnext;
           delete HDBptr;
           return;
          }
        HDBprevptr->HDBnext=HDBptr->HDBnext;
        delete HDBptr;
        return;
       }
     HDBprevptr=HDBptr;
     if(HDBptr->HDBnext==NULL) return;
     HDBptr=HDBptr->HDBnext;
    }
 }
