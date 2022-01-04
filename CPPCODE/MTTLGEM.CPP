/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlgem.cpp  Earl Cox  04/01/93 Get Error Message.          |
| This procedure fetches the error message associated with a  |
| diagnostic number and returns it to the caller. We use this |
| to retreive a message without calling the error handler.    |
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
#include <SystemPrototypes.hpp>
#define RECSIZE    80
static char ErrorRecord[RECSIZE];
static char *PgmId="mttlgem";
char *MtsGetErrorMsg(int ErrMsgNo)
  {
    int  i,k;
    long RecPos;
    char *ErrText,*errnum,*nullstr=NULL;
    FILE *fpErrMsgs=XSYSctl.XSYSfpErrors;

    if(fpErrMsgs==NULL)
      {
       fputs("Error Diagnostic file is not open\n",stderr);
       return(nullstr);
      }
    //--Fetch error record from the file.
     RecPos=(ErrMsgNo-1)*RECSIZE;
     fseek(fpErrMsgs,RecPos,SEEK_SET);
     fread(ErrorRecord,RECSIZE,1,fpErrMsgs);
    //--Get the diagnostic text from the record
     if(!(ErrText=new char[RECSIZE+1]))
       {
        errnum=MtsFormatInt(ErrMsgNo);
        MtsSendError(2,PgmId,errnum);
        return(nullstr);
       }
     memset(ErrText,'\0',81);
     for(i=11,k=0;ErrorRecord[i];i++,k++) ErrText[k]=ErrorRecord[i];
     return(ErrText);
  }
