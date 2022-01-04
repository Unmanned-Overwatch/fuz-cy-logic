/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlast.cpp  Earl Cox  04/01/93 The Diagnostic ASSERT       |
| This routine is used with the debug ASSERT macro to handle  |
| asseertion failures in the code.                            |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
void _MtsAssert(char * strNote,char *strFile,unsigned uLine)
 {
   FILE *syslog=MtsGetSystemFile(SYSLOGFILE);
   fflush(stdout);
//
//--Output the assertion failure to the stardard error file, usually
//--the terminal. We do this messaging so that the user sees that
//--some kind of assertion failed.
   fprintf(stderr,
       "\n\n--ASSERTION failed: '%s', in %s, at line %u\n",
             strNote,strFile,uLine);
//
//--Output the assertion failure once more to the FMS system log
//--so that we will have (if we're lucky) a permenant record.
   fprintf(syslog,
       "\n\n--ASSERTION failed: '%s', in %s, at line %u\n",
             strNote,strFile,uLine);
   fflush(stderr);
   fflush(syslog);
//--We might normally abort here. If you want to abort on
//--an assertion failure, uncomment this next line and recompile.
// abort();
   return;
 }
