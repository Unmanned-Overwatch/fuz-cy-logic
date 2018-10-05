/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlerd.cpp   Earl Cox  04/01/93 Error Diagnostic Handler   |
| This routine retreives, formats, and transmits an error     |
| diagnostic message from the main "fmssys.edf" repository.   |
| The message is sent to the log and optionally to the        |
| terminal.                                                   |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <XSYSctl.hpp>
#include   <mtypes.hpp>
#include <mtsptype.hpp>
#define RECSIZE    80
static char ErrorRecord[RECSIZE];
void MtsSendError(int ErrMsgNo,const char *Pgmid,const char *AnyToken)
  {
    int  i,k,status;
    long RecPos;
    char MesgBuffer[RECSIZE*2];
    char ErrClass[6];
    char ErrText[81];
    FILE *fpErrMsgs=XSYSctl.XSYSfpErrors;

    if(fpErrMsgs==NULL)
      {
       fputs("Error Diagnostic file is not open\n",stderr);
       abort();
      }
    //--Fetch error record from the file.
     RecPos=(ErrMsgNo-1)*RECSIZE;
     fseek(fpErrMsgs,RecPos,SEEK_SET);
     fread(ErrorRecord,RECSIZE,1,fpErrMsgs);
    //--Get the class and the diagnostic text from the record
     memset(ErrClass,'\0',6);
     for(i=5,k=0;i<10;i++,k++)            ErrClass[k]=ErrorRecord[i];
     memset(ErrText,'\0',81);
     for(i=11,k=0;ErrorRecord[i];i++,k++) ErrText[k]=ErrorRecord[i];
     sprintf(MesgBuffer,
       "ERROR> (%s.%s) %s",Pgmid,ErrClass,ErrText);
     if(AnyToken!=NULL)
       {
        strcat(MesgBuffer,": ");
        strcat(MesgBuffer,AnyToken);
        strcat(MesgBuffer," \n");
       }
     else
        strcat(MesgBuffer, "\n");
//
//--Now, if the error message switch is active we print the message
//--at the console. In any case, we put the error diagnostic in
//--the system log file.
     if(XSYSctl.XSYSerrmsgs)  fprintf(stdout,"%s\n",MesgBuffer);
     MtsWritetoLog(SYSLOGFILE,MesgBuffer,&status);
     return;
  }
