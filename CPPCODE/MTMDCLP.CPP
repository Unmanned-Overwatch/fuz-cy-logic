/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdclp.cpp  Earl Cox  04/01/93 Close a Policy              |
| This procedure shuts down a policy by releasing all its     |
| dictionary memory allocations. It does NOT free the memory  |
| held by the PDB itself since this is held in a hash chain.  |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include "PDB.hpp"
#include "FDB.hpp"
#include "HDB.hpp"
#include "VDB.hpp"
#include "NDB.hpp"
#include "mtypes.hpp"
#include "mtsptype.hpp"
//--We could probably use a template for these or a void* pointer
//--with a paramter to indicate casting since they are all exactly
//--the same except for the pointer type.
void MdlReleaseVariables(PDB*,long*);
void MdlReleaseFuzzysets(PDB*,long*);
void MdlReleaseHedges(PDB*,long*);
void MdlReleaseNoise(PDB*,long*);
void MdlClosePolicy(PDB *PDBptr,long *memory,int *statusPtr)
 {
  char    wrkBuff[128];
  long    varMemory,
          fzyMemory,
          hdgMemory,
          nswMemory,
          totMemory;
  totMemory=0;
  MdlReleaseVariables(PDBptr,&varMemory);
  MdlReleaseFuzzysets(PDBptr,&fzyMemory);
  MdlReleaseHedges   (PDBptr,&hdgMemory);
  MdlReleaseNoise    (PDBptr,&nswMemory);
  totMemory=(varMemory+fzyMemory+hdgMemory+nswMemory);
  sprintf(wrkBuff,"%s%s%s%5ld%s",
    "FMSNote(014): Policy '",
      PDBptr->PDBid,"' closed. ",totMemory/1024,"K bytes released.");
  MtsWritetoLog(SYSMODFILE,wrkBuff,statusPtr);
  *memory=totMemory;
  return;
 }
//
//-----------Dictionary memory management routines-----------------
//
void MdlReleaseVariables(PDB *PDBptr,long *Memory)
/*------------------------------------------------------------*
| Release memory for all the formal variables in this policy. |
*-------------------------------------------------------------*/
  {
   VDB  *VDBptr,*nextVDBptr;
   int   i;
   int   varbytes=sizeof(VDB);
   long  memAmt=0;

   for(i=0;i<VDBmax;i++)
     if(PDBptr->PDBvariables[i]!=NULL)
       {
        VDBptr=PDBptr->PDBvariables[i];
        while(1)
         {
          nextVDBptr=VDBptr->VDBnext;
          delete VDBptr;
          memAmt+=varbytes;
          if(nextVDBptr==NULL) break;
          VDBptr=nextVDBptr;
         }
        PDBptr->PDBvariables[i]=NULL;
       }
   *Memory=memAmt;
  }
//
void MdlReleaseFuzzysets(PDB *PDBptr,long *Memory)
/*------------------------------------------------------------*
| Release memory for all the fuzzy sets in this policy        |
*-------------------------------------------------------------*/
  {
   FDB  *FDBptr,*nextFDBptr;
   int   i;
   int   fzybytes=sizeof(FDB);
   long  memAmt=0;

   for(i=0;i<FDBmax;i++)
     if(PDBptr->PDBfuzzysets[i]!=NULL)
       {
        FDBptr=PDBptr->PDBfuzzysets[i];
        while(1)
         {
          nextFDBptr=FDBptr->FDBnext;
          delete FDBptr;
          memAmt+=fzybytes;
          if(nextFDBptr==NULL) break;
          FDBptr=nextFDBptr;
         }
        PDBptr->PDBfuzzysets[i]=NULL;
       }
   *Memory=memAmt;
  }
//
void MdlReleaseHedges(PDB *PDBptr,long *Memory)
/*------------------------------------------------------------*
| Release memory for all the hedge operators in this policy.  |
*-------------------------------------------------------------*/
  {
   HDB  *HDBptr,*nextHDBptr;
   int   i;
   int   hdgbytes=sizeof(HDB);
   long  memAmt=0;

   for(i=0;i<HDBmax;i++)
     if(PDBptr->PDBhedges[i]!=NULL)
       {
        HDBptr=PDBptr->PDBhedges[i];
        while(1)
         {
          nextHDBptr=HDBptr->HDBnext;
          delete HDBptr;
          memAmt+=hdgbytes;
          if(nextHDBptr==NULL) break;
          HDBptr=nextHDBptr;
         }
        PDBptr->PDBhedges[i]=NULL;
       }
   *Memory=memAmt;
  }
//
void MdlReleaseNoise(PDB *PDBptr,long *Memory)
/*------------------------------------------------------------*
| Release memory for all the noise words in this policy       |
*-------------------------------------------------------------*/
  {
   NDB  *NDBptr,*nextNDBptr;
   int   i;
   int   nwdbytes=sizeof(NDB);
   long  memAmt=0;

   for(i=0;i<NDBmax;i++)
     if(PDBptr->PDBnoise[i]!=NULL)
       {
        NDBptr=PDBptr->PDBnoise[i];
        while(1)
         {
          nextNDBptr=NDBptr->NDBnext;
          delete NDBptr;
          memAmt+=nwdbytes;
          if(nextNDBptr==NULL) break;
          NDBptr=nextNDBptr;
         }
        PDBptr->PDBnoise[i]=NULL;
       }
   *Memory=memAmt;
  }
