/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlgtd.cpp  Earl Cox  04/01/93 Get Date Information        |
| This function accesses the DOS date structure and returns   |
| the current date as YYYYMMDD. The day of the week is also   |
| passed back as a calling parameter.                         |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stddef.h>
#include <string.h>
#include <dos.h>
#include "mtypes.hpp"
#include "mtsptype.hpp"
char *MtsGetDate(char *DayofWeek,int *statusPtr)
 {
  dosdate_t   thisDate;
  char       *ToDayptr,*nullChar=NULL;
  const int   Datelen=8;
  char *WeekDays[]=
   {
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday"
   };
  _dos_getdate(&thisDate);
  if(!(ToDayptr=new char[Datelen+1]))
    {
     *statusPtr=1;
     return(nullChar);
    }
  sprintf(ToDayptr,"%4d%02d%02d",
    thisDate.year,thisDate.month,thisDate.day);
  strcpy(DayofWeek,WeekDays[thisDate.dayofweek]);
  return(ToDayptr);
 }
