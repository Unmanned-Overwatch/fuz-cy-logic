/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzxfi.cpp   Earl Cox  04/01/93 Initialize Fuzzy WorkArea  |
| This procedure initializes the work area use to handle the  |
| "under generation" variables created by the fuzzy modelling |
| facilities.                                                 |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include <XFZYctl.hpp>
#include   <mtypes.hpp>
#include   <fuzzy.hpp>
#include <mtsptype.hpp>
#define Maxoutvars  32
void FzyInitFZYctl(int *statusPtr)
 {
  int   i,status;
  char  wrkBuff[80];

  *statusPtr=0;
  XFZYctl.XFZYvarcnt=0;
  XFZYctl.XFZYthisvar=-1;
  for(i=0;i<Maxoutvars;i++) XFZYctl.XFZYoutvars[i]=NULL;
 sprintf(wrkBuff,"%s","FMSNote(003): Fuzzy Work Area Initialized");
 MtsWritetoLog(SYSMODFILE,wrkBuff,&status);
 }
