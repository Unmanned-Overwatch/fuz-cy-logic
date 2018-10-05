/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdfdh.cpp  Earl Cox  04/01/93 Find Hedge in the Policy    |
| This function takes a character string containing the name  |
| of a hedge in the policy's  dictionary. On finding the      |
| hedge, we return the HDB address.                           |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <stddef.h>
#include <PDB.hpp>
#include <HDB.hpp>
#include   <mtypes.hpp>
#include <mtsptype.hpp>
HDB *MdlFindHDB(char *Hdgid,PDB *PDBptr,int *statusPtr)
 {
  HDB    *HDBptr,*HDBnull=NULL;
  char   *PgmId="mtmdfdh";
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
     return(HDBnull);
    }
//
//--Look at the HDB doctionary slot. If it's empty, then
//--return a null pointer saying that the fuzzyset doesn't
//--exist. Otherwise look through the remainder of the chain
//--for the hedge name until we come to the chain end.
  *statusPtr=3;
  HDBptr=PDBptr->PDBhedges[slot];
  if(HDBptr==NULL) return(HDBnull);
  for(;;)
    {
     if(strcmp(HDBptr->HDBid,Hdgid)==0)
       {
        *statusPtr=0;
        return(HDBptr);
       }
     if(HDBptr->HDBnext==NULL) return(HDBnull);
     HDBptr=HDBptr->HDBnext;
    }
 }
