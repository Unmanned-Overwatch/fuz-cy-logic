/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzxfr.cpp   Earl Cox  04/01/93 Reset the Fuzzy WorkArea   |
| This procedure resets the fuzzy work area by setiing the    |
| membership function in the FSV to zeros.                    |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include <XFZYctl.hpp>
#include <fdb.hpp>
#include <FSV.hpp>
#include   <mtypes.hpp>
#include   <fuzzy.hpp>
#include <mtsptype.hpp>
void FzyResetFZYctl(int *statusPtr)
 {
  FDB  *FDBptr;
  FSV  *FSVptr;
  int   i,j,status;
  char  wrkBuff[80];

  *statusPtr=0;
  sprintf(wrkBuff,"%s %5d",
    "FMSNote(012): under-generation sets:",XFZYctl.XFZYvarcnt);
  MtsWritetoLog(SYSMODFILE,wrkBuff,&status);
//
  for(i=0;i<XFZYctl.XFZYvarcnt+1;i++)
     {
      FSVptr=XFZYctl.XFZYoutvars[i];
      if(FSVptr!=NULL)
        {
         FDBptr=FSVptr->FzySVfdbptr;
         if(FDBptr!=NULL)
           {
            sprintf(wrkBuff,"%s%s%s",
              "....Resetting '",FDBptr->FDBid,"'");
            MtsWritetoLog(SYSMODFILE,wrkBuff,&status);
            for(j=0;j<VECMAX;j++)  FDBptr->FDBvector[j]=0;
            FDBptr->FDBempty=TRUE;
           }
        }
     }
 sprintf(wrkBuff,"%s","FMSNote(009): Fuzzy Work Area Reset.");
 MtsWritetoLog(SYSMODFILE,wrkBuff,&status);
 return;
 }
