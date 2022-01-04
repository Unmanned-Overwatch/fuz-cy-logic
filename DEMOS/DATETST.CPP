/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| datetst.cpp  Earl Cox  04/01/93 Test the Date/Time formatter|
| This routine will request a date and time format option.    |
| The system data and time is then retreived and formatted    |
| using this specification.                                   |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include "stdio.h"
#include <SystemPrototypes.hpp>
void main(void)
 {
   char   *thedate,
          *thetime,
          *fmtdate,
          *fmttime;
   char    dow[12];
   int     dhow,thow,status;
//
   fflush(stdin);
   puts("Enter the DATE format:");
   scanf("%d",&dhow);
   puts("Enter the TIME format:");
   scanf("%d",&thow);
//
   thedate=MtsGetDate(dow,&status);
   thetime=MtsGetTime(&status);
   fmtdate=MtsFormatDate(thedate,dhow,&status);
   fmttime=MtsFormatTime(thetime,thow,&status);
   fprintf(stdout,"%s%s\n","Date = ",thedate);
   fprintf(stdout,"%s%s\n","Date = ",fmtdate);
   fprintf(stdout,"%s%s\n","Time = ",thetime);
   fprintf(stdout,"%s%s\n","Time = ",fmttime);
   fprintf(stdout,"%s%s\n","Dow  = ",dow    );
   return;
 }
