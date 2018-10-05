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
#include "VDB.hpp"
#include <fdb.hpp>
#include   <mtypes.hpp>
#include   <fuzzy.hpp>
#include <mtsptype.hpp>
#define Maxoutvars  32
bool FzyAddFZYctl(VDB *VDBptr,FDB **FDBptr,FSV **FSVptr,int *statusPtr)
 {
  FSV    *tempFSVptr;
  FDB    *tempFDBptr;
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
     MtsSendError(194,Pgmid,VDBptr->VDBid);
     return(FAILED);
    }
  VDBptr->VDBfsvslot= XFZYctl.XFZYvarcnt;
  XFZYctl.XFZYthisvar=XFZYctl.XFZYvarcnt;
//
//--Allocate a new FSV block and link it itno the work slot
//
  if(!(tempFSVptr=new FSV))
    {
     *statusPtr=3;
     MtsSendError(195,Pgmid,VDBptr->VDBid);
     return(FAILED);
    }
  XFZYctl.XFZYoutvars[XFZYctl.XFZYvarcnt]=tempFSVptr;
//
//--Now fill out this slot with information from the VDB
//
  strcpy(tempFSVptr->FzySVvarid,VDBptr->VDBid);
  tempFSVptr->FzySVvarptr       =VDBptr;
  tempFSVptr->FzySVupdcnt       =0;
  tempFSVptr->FzySVdefuzzMethod =VDBptr->VDBdefuzzmethod;
  tempFSVptr->FzySVgeometry     =VDBptr->VDBfzygeometry;
  tempFSVptr->FzySVcorrMethod   =VDBptr->VDBfzycorrmethod;
  tempFSVptr->FzySVimplMethod   =VDBptr->VDBfzyimplmethod;
  tempFSVptr->FzySValfacut      =VDBptr->VDBalfacut;
//
//--Every output variable is represented by a fuzzy set. We now
//--create a new fuzzy set, initialize it to an empty region and
//--link it into the output slot.
//
  tempFDBptr=FzyCreateSet(
    VDBptr->VDBid,EMPTYSET,VDBptr->VDBdomain,Parms,0,statusPtr);
  if(tempFDBptr==NULL)
    {
     *statusPtr=5;
     MtsSendError(196,Pgmid,VDBptr->VDBid);
     return(FAILED);
    }
  tempFSVptr->FzySVfdbptr=tempFDBptr;
  for(j=0;j<VECMAX;j++) tempFSVptr->FzySVcntarray[j]=0;
//
//--Now update the actual pointers to the FSV and the FDBs
//
  *FSVptr=tempFSVptr;
  *FDBptr=tempFDBptr;
//
//--All done. Send a message to the log.
//
 sprintf(wrkBuff,"%s%s%s",
   "FMSNote(005): Output Variable '",VDBptr->VDBid,
   "' added to Fuzzy Model.");
 MtsWritetoLog(SYSMODFILE,wrkBuff,statusPtr);
 return(SUCCESS);
 }
