/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdinw.cpp  Earl Cox  04/01/93 Insert Noise Words          |
| This procedure inserts the default noise words into the     |
| designated policy.  We need this to parse fuzzy rules.      |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <PDB.hpp>
#include <NDB.hpp>
#include <eqpack.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
void MdlInsertNWords(PDB *PDBptr,int *NDBcnt,int *statusPtr)
 {
  NDB    *NDBptr,*NDBwrkptr;
  char   *PgmId="mtmdinw";
  char    Nword[DESCLEN+1];
  char    wrkBuff[80];
  int     i;
  long    slot;

  *statusPtr=0;
  *NDBcnt=0;
  for(i=0;i<EQNWRDmax;i++)
   {
     strcpy(Nword,EQNoiseWords[i]);
     if(!(NDBptr=new NDB))
       {
        *statusPtr=1;
        MtsSendError(2,PgmId,Nword);
        return;
       }
     (*NDBcnt)++;
     strcpy(NDBptr->NDBid,Nword);
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
        if(NDBwrkptr->NDBnext==NULL)     // Is there a next block
          {                              // No...
           NDBwrkptr->NDBnext=NDBptr;    // Link into the chain
           return;                       // return to caller
          }
        NDBwrkptr=NDBwrkptr->NDBnext;    // move to next chain node
       }
   }
   sprintf(wrkBuff,"%s%s%s",
    "Default Noise Words installed in Policy '",PDBptr->PDBid,"'");
   MtsWritetoLog(SYSMODFILE,wrkBuff,statusPtr);
   return;
 }
