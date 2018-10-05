/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlgtf.cpp   Earl Cox  04/01/93 Get System File stream     |
| The standard system files are stored in the XSYSctl area    |
| but there identifiers are generally unweildy for use in     |
| most programs. This procedure returns the stream pointer    |
| so it can be assigned to a user variable in the program.    |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include "XSYSctl.hpp"
#include "mtypes.hpp"
FILE *MtsGetSystemFile(int FileType)
 {
  switch(FileType)
   {
    case SYSLOGFILE:    return(XSYSctl.XSYSfpSyslog);
    case SYSMODFILE:    return(XSYSctl.XSYSfpModellog);
    case SYSERRFILE:    return(XSYSctl.XSYSfpErrors);
    case SYSOUT:        return(stdout);
    default:            return(NULL);
   }
 }
