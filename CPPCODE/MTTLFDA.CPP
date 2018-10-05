/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlfda.cpp  Earl Cox  04/01/93 Format a Date               |
| This procedure takes a format type parameter that determines|
| how a date should be formatted for output into a character  |
| string. We expect the date in long integer format.          |
|                                                             |
|    0     YYYYMMDD       19991016                            |
|    1     ddMMMyy        16OCT99                             |
|    2     dd-MMM-yy      16-OCT-99                           |
|    3     MO dd, yyyy    OCTOBER 16, 1999                    |
|    4     Mo dd, yyyy    October 16, 1999                    |
|    5     mm/dd/yy       10/16/99                            |
|    6     dd/mm/yy       16/10/99                            |
|                                                             |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "mtypes.hpp"
#include "mtsptype.hpp"
char *MtsFormatDate(char *theDate,int FormatType,int *statusPtr)
 {
//
//--We add an extra initial slot to the months array so that
//--the i-th entry is equal to the month with that number.
   char *Months[]=
    {
     "       ",
     "January",
     "February",
     "March",
     "April",
     "May",
     "June",
     "July",
     "August",
     "September",
     "November",
     "December"
    };
   int   i,Mnthidx,maxbuff=32;
   char  month[16];
   char *wrkBuff;
   char *theFullYear  =MtsGetsubstr(theDate,2,2);
   char *theYear      =MtsGetsubstr(theDate,0,4);
   char *theMonth     =MtsGetsubstr(theDate,4,2);
   char *theDay       =MtsGetsubstr(theDate,6,2);

   *statusPtr=0;
   wrkBuff=new char[maxbuff+1];
   switch(FormatType)
    {
     case  0:
       return(theDate);
     case  1:
     case  2:
       Mnthidx=atoi(theMonth);
       strcpy(month,Months[Mnthidx]);
       for(i=0;i<(signed)strlen(month);i++) month[i]=toupper(month[i]);
       if(FormatType==1)
          sprintf(wrkBuff,"%s%.3s%s",theDay,month,theYear);
         else
          sprintf(wrkBuff,"%s%c%.3s%c%s",theDay,'-',month,'-',theYear);
       return(wrkBuff);
     case  3:
     case  4:
       Mnthidx=atoi(theMonth);
       strcpy(month,Months[Mnthidx]);
       if(FormatType==3)
          for(i=0;i<(signed)strlen(month);i++) month[i]=toupper(month[i]);
       sprintf(wrkBuff,"%s %s%c%s",month,theDay,',',theFullYear);
       return(wrkBuff);
     case  5:
       sprintf(wrkBuff,"%s%c%s%c%s",theMonth,'//',theDay,'//',theYear);
       return(wrkBuff);
     case  6:
       sprintf(wrkBuff,"%s%c%s%c%s",theDay,'//',theMonth,'//',theYear);
       return(wrkBuff);
     default:
       *statusPtr=1;
       sprintf(wrkBuff,"%s%c%s%c%s",theMonth,'//',theDay,'//',theYear);
       return(wrkBuff);
    }
 }
