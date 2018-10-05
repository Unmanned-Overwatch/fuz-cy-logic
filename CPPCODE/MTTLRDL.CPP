/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlrdl.cpp   Earl Cox  04/01/93 Reduce Line                |
| The ReduceLine procedure scrubs a system text line by       |
| removing multiple blanks, removing comments, and replacing  |
| newlines and tabs with blanks.                              |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <stddef.h>
#include   <fuzzy.hpp>
#include   <mtypes.hpp>
#include <mtsptype.hpp>
void MtsReduceLine(char *Text,int *TextLen)
   {
    char  WrkArea[LINEmax];
    char *PgmId="mttlrdl";
    char  thisChar,
          tempChar,
          QuoteType;
    int   i,
          wrkcnt=0;
    bool  inQuote=FALSE;

    for(i=0;i<*TextLen;i++)
     {
      if(wrkcnt>=LINEmax)
        {
         MtsSendError(6,PgmId,Text);
         return;
        }
      thisChar=Text[i];
      switch(thisChar)
       {
        case NEWLINE:
        case TAB:
        case BLANK:
         if((wrkcnt==0||WrkArea[wrkcnt]==BLANK)&&(!inQuote)) break;
         WrkArea[wrkcnt++]=thisChar;
         break;
        case SINGLEQUOTE:
        case DOUBLEQUOTE:
         if(!inQuote)
           {
            inQuote=TRUE;
            QuoteType=thisChar;
           }
         else
           {
            if(thisChar==QuoteType) inQuote=FALSE;
           }
         WrkArea[wrkcnt++]=thisChar;
         break;
        case SLASH:
         tempChar=Text[i+1];
         if(tempChar==ASTERISK)
           {
            for(;i<*TextLen;i++)
             {
              tempChar=Text[i];
              if(tempChar==ASTERISK&&Text[i+1]==SLASH) break;
             }
           }
           else
         if(tempChar==SLASH)
           {
            for(;i<*TextLen;i++)
             {
              tempChar=Text[i];
              if(tempChar==NEWLINE||tempChar==END_OF_BUFFER) break;
             }
            break;
           }
           else
         WrkArea[wrkcnt++]=thisChar;
         break;
        default:
          WrkArea[wrkcnt++]=thisChar;
       }
     }
    WrkArea[wrkcnt]='\0';
    strcpy(Text,WrkArea);
    *TextLen=strlen(Text);
    return;
   }
