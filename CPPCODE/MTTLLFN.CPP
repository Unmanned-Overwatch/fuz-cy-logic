/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttllfn.cpp   Earl Cox  04/01/93 Get System File Name       |
| This routine returns the name of the log file associated    |
| with the symbolic constant. We use this to improve the      |
| diagnostic display for the user.                            |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include "mtypes.hpp"
char *MtsLogFileName(int FileType)
 {
  switch(FileType)
   {
    case SYSLOGFILE:   return("system log");
    case SYSMODFILE:   return("model log");
    case SYSERRFILE:   return("error log");
    default:           return("unknown");
   }
 }
