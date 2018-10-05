/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdfdn.cpp  Earl Cox  04/01/93 Find NoiseWord in Policy    |
| This function takes a character string containing the name  |
| of a NoiseWord in the policy's  dictionary. On finding the  |
| NoiseWord we return the NDB address.                        |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <stddef.h>
#include "PDB.hpp"
#include "NDB.hpp"
#include   <mtypes.hpp>
#include <mtsptype.hpp>
NDB *MdlFindNDB(char *Nwrdid,PDB *PDBptr,int *statusPtr)
 {
  NDB    *NDBptr,*NDBnull=NULL;
  char   *PgmId="mtmdfdh";
  long    slot;

  *statusPtr=0;
//
//--Now hash the noise word name to get its slot location in
//--the PDB's dictionary.
  slot=MtsHashString(Nwrdid,NDBmax);
  if(slot<0||slot>NDBmax)
    {
     *statusPtr=1;
     MtsSendError(97,PgmId,Nwrdid);
     return(NDBnull);
    }
//
//--Look at the NDB doctionary slot. If it's empty, then
//--return a null pointer saying that the word doesn't
//--exist. Otherwise look through the remainder of the chain
//--for the name until we come to the chain end.
  *statusPtr=3;
  NDBptr=PDBptr->PDBnoise[slot];
  if(NDBptr==NULL) return(NDBnull);
  for(;;)
    {
     if(strcmp(NDBptr->NDBid,Nwrdid)==0)
       {
        *statusPtr=0;
        return(NDBptr);
       }
     if(NDBptr->NDBnext==NULL) return(NDBnull);
     NDBptr=NDBptr->NDBnext;
    }
 }
