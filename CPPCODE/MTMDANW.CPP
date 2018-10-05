/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdanw.cpp  Earl Cox  04/01/93 Add a Noise Word to Policy  |
| This procedure inserts a noise word into the designated     |
| policy  envelope.                                           |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include "PDB.hpp"
#include "NDB.hpp"
#include "eqpack.hpp"
#include "mtypes.hpp"
#include "mtsptype.hpp"
void MdlAddNoiseWord(char *NoiseWord,PDB *PDBptr,int *statusPtr)
 {
  NDB    *NDBptr,*NDBwrkptr;
  char   *PgmId="mtmdinw";
  char    Nword[DESCLEN+1];
  long    slot;

  *statusPtr=0;
  if(!(NDBptr=new NDB))
    {
     *statusPtr=1;
     MtsSendError(2,PgmId,NoiseWord);
     return;
    }
  strcpy(NDBptr->NDBid,NoiseWord);
  NDBptr->NDBnext=NULL;
  slot=MtsHashString(Nword,NDBmax);
  NDBwrkptr=PDBptr->PDBnoise[slot];
  if(NDBwrkptr==NULL)
    {
     PDBptr->PDBnoise[slot]=NDBptr;
     return;
    }
  for(;;)
    {
     if(strcmp(NDBwrkptr->NDBid,NoiseWord)==0)
       {
        *statusPtr=3;
        delete NDBptr;
        return;
       }
     if(NDBwrkptr->NDBnext==NULL)     // Is there a next block
       {                              // No...
        NDBwrkptr->NDBnext=NDBptr;    // Link into the chain
        return;                       // return to caller
       }
     NDBwrkptr=NDBwrkptr->NDBnext;    // move to next chain node
    }
 }
