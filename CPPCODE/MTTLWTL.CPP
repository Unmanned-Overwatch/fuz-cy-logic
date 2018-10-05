/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlwtl.cpp  Earl Cox  04/01/93 Write to a Log File         |
| This procedure writes a line of text to one of the system   |
| log files. If you specify SYSOUT, then the display is made  |
| at the communications terminal.                             |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include "XSYSctl.hpp"
#include "mtypes.hpp"
#include "mtsptype.hpp"
static char *PgmId="mttlwtl";
void MtsWritetoLog(int LogType,char *LogText,int *statusPtr)
 {
  FILE   *logfile;
  char   *fileid;
  char   *theDate,*theTime,*fmtDate,*fmtTime;
  char    wrkBuff[16];
  int     dhow=5,thow=3;

  *statusPtr=0;
  switch(LogType)
   {
    case SYSLOGFILE:
      logfile=XSYSctl.XSYSfpSyslog;
      break;
    case SYSMODFILE:
      logfile=XSYSctl.XSYSfpModellog;
      break;
    case SYSOUT:
      logfile=stdout;
      break;
    case SYSERRFILE:
      *statusPtr=1;
      fileid=MtsLogFileName(LogType);
      MtsSendError(103,PgmId,fileid);
      return;
    default:
      *statusPtr=2;
      fileid=MtsLogFileName(LogType);
      MtsSendError(104,PgmId,fileid);
      return;
   }
//--Get and format the current data and time.
  theDate=MtsGetDate(wrkBuff,statusPtr);
  theTime=MtsGetTime(statusPtr);
  fmtDate=MtsFormatDate(theDate,dhow,statusPtr);
  fmtTime=MtsFormatTime(theTime,thow,statusPtr);
//
//fprintf(stdout, "%s%c%s%s%s\n",fmtDate,' ',fmtTime,"---",LogText);
  fprintf(logfile,"%s%c%s%s%s\n",fmtDate,' ',fmtTime,"---",LogText);
  fflush(logfile);
  return;
 }
