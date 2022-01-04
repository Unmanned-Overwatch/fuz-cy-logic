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
#include <PDB.hpp>
#include <FuzzysetDescriptor.hpp>
#include <HDB.hpp>
#include "VariableDescriptor.hpp"
#include <NDB.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
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
   VariableDescriptor  *VariableDescriptorptr,*nextVariableDescriptorptr;
   int   i;
   int   varbytes=sizeof(VariableDescriptor);
   long  memAmt=0;

   for(i=0;i<VariableDescriptormax;i++)
     if(PDBptr->PDBvariables[i]!=NULL)
       {
        VariableDescriptorptr=PDBptr->PDBvariables[i];
        while(1)
         {
          nextVariableDescriptorptr=VariableDescriptorptr->VariableDescriptornext;
          delete VariableDescriptorptr;
          memAmt+=varbytes;
          if(nextVariableDescriptorptr==NULL) break;
          VariableDescriptorptr=nextVariableDescriptorptr;
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
   FuzzysetDescriptor  *FuzzysetDescriptorptr,*nextFuzzysetDescriptorptr;
   int   i;
   int   fzybytes=sizeof(FuzzysetDescriptor);
   long  memAmt=0;

   for(i=0;i<FuzzysetDescriptormax;i++)
     if(PDBptr->PDBfuzzysets[i]!=NULL)
       {
        FuzzysetDescriptorptr=PDBptr->PDBfuzzysets[i];
        while(1)
         {
          nextFuzzysetDescriptorptr=FuzzysetDescriptorptr->FuzzysetDescriptornext;
          delete FuzzysetDescriptorptr;
          memAmt+=fzybytes;
          if(nextFuzzysetDescriptorptr==NULL) break;
          FuzzysetDescriptorptr=nextFuzzysetDescriptorptr;
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
