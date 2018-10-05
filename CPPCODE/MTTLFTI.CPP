/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlfti.cpp  Earl Cox  04/01/93 Format a Time               |
| This procedure takes a format type parameter that determines|
| how a time should be formatted for output into a character  |
| string. We expect the time in character string format.      |
|                                                             |
|    0     hhmmss         114638                              |
|    1     hh:mm:ss       11:46:38                            |
|    2     hh.mm.ss       11.46.38                            |
|    3     hh.mmxx        11.46am                             |
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
//
static const int maxbuff=24;
char *MtsFormatTime(char *theTime,int FormatType,int *statusPtr)
 {
   int   ModuloHour;
   char *wrkBuff,suffix[2];
   char *theHour      =MtsGetsubstr(theTime,0,2);
   char *theMinutes   =MtsGetsubstr(theTime,2,2);
   char *theSeconds   =MtsGetsubstr(theTime,4,2);

   *statusPtr=0;
   wrkBuff=new char[maxbuff+1];
   switch(FormatType)
    {
     case  0:
       return(theTime);
     case  1:
       sprintf(wrkBuff,"%s%c%s%c%s",
           theHour,':',theMinutes,':',theSeconds);
       return(wrkBuff);
     case  2:
       sprintf(wrkBuff,"%s%c%s%c%s",
           theHour,'.',theMinutes,'.',theSeconds);
       return(wrkBuff);
     case  3:
       ModuloHour=atoi(theHour);
       strcpy(suffix,"am");
       //--If the time is after noon then we subtract 12 to get
       //--the actual wall lock time. If the hour is now zero,
       //--this means that we are actually at noon, so we reset
       //--the time to 12.
       if(ModuloHour>=12)
         {
          ModuloHour=ModuloHour-12;
          if(ModuloHour==0) ModuloHour=12;
          strcpy(suffix,"pm");
         }
       sprintf(wrkBuff,"%2d%c%s%s",ModuloHour,'.',theMinutes,suffix);
       return(wrkBuff);
     default:
       *statusPtr=1;
       sprintf(wrkBuff,"%s%c%s%c%s",
           theHour,':',theMinutes,':',theSeconds);
       return(wrkBuff);
    }
 }
