/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlswm.cpp  Earl Cox  04/01/93 Send a Warning Message      |
| Warning messages, unlike standard diagnostics, usually do   |
| not indicate a fatal operating condition. You can take the  |
| standard recovery action and processing continues.          |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
void MtsSendWarning(
   char *MsgId,char Severity,char *WrngText,int *statusPtr)
  {
    char  MsgBuff[256];

    *statusPtr=0;
    sprintf(MsgBuff,"%s%s%c%s%s\n",
      MsgId,"---[",Severity,"] ",WrngText);
    fputs(MsgBuff,stderr);
  //
  //--Now we reformat this message to write it out to the log
    sprintf(MsgBuff,"%s.[%c]%s",MsgId,Severity,WrngText);
    MtsWritetoLog(SYSLOGFILE,MsgBuff,statusPtr);
    return;
  }
