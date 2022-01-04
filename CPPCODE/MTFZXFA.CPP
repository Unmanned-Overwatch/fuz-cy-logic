/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzxfa.cpp   Earl Cox  04/01/93 Add to the Fuzzy WorkArea  |
| This procedure adds a variable to the fuzzy work area. It   |
| also creates a new output fuzzy set and makes it available  |
| to the processor.                                           |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include <XFZYctl.hpp>
#include "VariableDescriptor.hpp"
#include <FuzzysetDescriptor.hpp>
#include   <SystemTypes.hpp>
#include   <fuzzy.hpp>
#include <SystemPrototypes.hpp>
#define Maxoutvars  32
bool FzyAddFZYctl(VariableDescriptor *VariableDescriptorptr,FuzzysetDescriptor **FuzzysetDescriptorptr,FSV **FSVptr,int *statusPtr)
 {
  FSV    *tempFSVptr;
  FuzzysetDescriptor    *tempFuzzysetDescriptorptr;
  int     j;
  char   *Pgmid="mtfzafs";
  char    wrkBuff[128];
  double  Parms[6];

  *statusPtr=0;
//
//--Increment to the next available work slot for this variable
//
  XFZYctl.XFZYvarcnt++;
  if(XFZYctl.XFZYvarcnt>Maxoutvars)
    {
     *statusPtr=1;
     MtsSendError(194,Pgmid,VariableDescriptorptr->VariableDescriptorid);
     return(FAILED);
    }
  VariableDescriptorptr->VariableDescriptorfsvslot= XFZYctl.XFZYvarcnt;
  XFZYctl.XFZYthisvar=XFZYctl.XFZYvarcnt;
//
//--Allocate a new FSV block and link it itno the work slot
//
  if(!(tempFSVptr=new FSV))
    {
     *statusPtr=3;
     MtsSendError(195,Pgmid,VariableDescriptorptr->VariableDescriptorid);
     return(FAILED);
    }
  XFZYctl.XFZYoutvars[XFZYctl.XFZYvarcnt]=tempFSVptr;
//
//--Now fill out this slot with information from the VariableDescriptor
//
  strcpy(tempFSVptr->FzySVvarid,VariableDescriptorptr->VariableDescriptorid);
  tempFSVptr->FzySVvarptr       =VariableDescriptorptr;
  tempFSVptr->FzySVupdcnt       =0;
  tempFSVptr->FzySVdefuzzMethod =VariableDescriptorptr->VariableDescriptordefuzzmethod;
  tempFSVptr->FzySVgeometry     =VariableDescriptorptr->VariableDescriptorfzygeometry;
  tempFSVptr->FzySVcorrMethod   =VariableDescriptorptr->VariableDescriptorfzycorrmethod;
  tempFSVptr->FzySVimplMethod   =VariableDescriptorptr->VariableDescriptorfzyimplmethod;
  tempFSVptr->FzySValfacut      =VariableDescriptorptr->VariableDescriptoralfacut;
//
//--Every output variable is represented by a fuzzy set. We now
//--create a new fuzzy set, initialize it to an empty region and
//--link it into the output slot.
//
  tempFuzzysetDescriptorptr=FzyCreateSet(
    VariableDescriptorptr->VariableDescriptorid,EMPTYSET,VariableDescriptorptr->VariableDescriptordomain,Parms,0,statusPtr);
  if(tempFuzzysetDescriptorptr==NULL)
    {
     *statusPtr=5;
     MtsSendError(196,Pgmid,VariableDescriptorptr->VariableDescriptorid);
     return(FAILED);
    }
  tempFSVptr->FzySVFuzzysetDescriptorptr=tempFuzzysetDescriptorptr;
  for(j=0;j<VECMAX;j++) tempFSVptr->FzySVcntarray[j]=0;
//
//--Now update the actual pointers to the FSV and the FuzzysetDescriptors
//
  *FSVptr=tempFSVptr;
  *FuzzysetDescriptorptr=tempFuzzysetDescriptorptr;
//
//--All done. Send a message to the log.
//
 sprintf(wrkBuff,"%s%s%s",
   "FMSNote(005): Output Variable '",VariableDescriptorptr->VariableDescriptorid,
   "' added to Fuzzy Model.");
 MtsWritetoLog(SYSMODFILE,wrkBuff,statusPtr);
 return(SUCCESS);
 }
