/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlart.cpp   Earl Cox  04/01/93 Error Text Append Handler  |
| This routine transmits additinal textual information with   |
| a system error message. We use this since (1) messaging may |
| be turned off and (2) we need the actual name of the system |
| log file.                                                   |
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
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
#define RECSIZE    80
static char ErrorRecord[RECSIZE];
void MtsAppendErrorText(int ErrMsgNo,const char *AppText)
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
     sprintf(MesgBuffer,
       "ERROR> (%s.%s) %s","[more...]",ErrClass,AppText);
//
//--Now, if the error message switch is active we print the message
//--at the console. In any case, we put the error diagnostic in
//--the system log file.
     if(XSYSctl.XSYSerrmsgs)  fprintf(stdout,"%s\n",MesgBuffer);
     MtsWritetoLog(SYSLOGFILE,MesgBuffer,&status);
     return;
  }
