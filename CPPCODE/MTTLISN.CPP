/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlisn.cpp   Earl Cox  04/01/93 Is this Item Numeric       |
| This routine examines a character string to see if it is    |
| a valid integer or floating number in conventional format.  |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <ctype.h>
#include   <mtypes.hpp>
bool MtsIsNumeric(char *Item,int *NumType)
 {
   int i;
   bool PeriodFound=FALSE;
   *NumType=STRING;
   for(i=0;Item[i];i++)
    {
     if(!isdigit(Item[i])&&!(Item[i]=='.')) return(FALSE);
     if(Item[i]=='.')
       {
         if(PeriodFound) return(FALSE);
         PeriodFound=TRUE;
       }
    }
   if(PeriodFound)   *NumType=REAL;
      else           *NumType=INTEGER;
   return(TRUE);
 }
