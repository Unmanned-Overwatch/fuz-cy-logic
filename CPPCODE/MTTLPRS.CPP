/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlprs.cpp  Earl Cox 04/01/93  A simple line entokener.    |
| This routine returns a linearly linked list containing a    |
| set of nodes: one for each individual token. The actual     |
| delimeters are not returned.                                |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include   <fuzzy.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
bool IsDelimiter(char);
void MtsEntoken(
   char *Line,char **Tokens,int MaxTokCnt,int *TokCnt,int *statusPtr)
  {
   int  i,bufflen,k=0;
   int  MaxTokLen=80;
   char token[82];
   char *newTOKptr;
   char *PgmId="mttlprs";

   *statusPtr=0;
   *TokCnt=0;
   memset(token,'\0',MaxTokLen);
   bufflen=strlen(Line);
//--For each byte in the line we check to see if it's a member of
//--the delimiter class. If so, we store the current token up to
//--that point, otherwise we continue building the token.
   for(i=0;;i++)
    {
     if(IsDelimiter(Line[i]))
       {
       //--if token length is zero, then nothing has been built.
       //--this happens when we find multiple delimiters (such as
       //--blanks) in succession.
        if(strlen(token)!=0)
          {
           if(*TokCnt>MaxTokCnt)
             {
              *statusPtr=1;
              MtsSendError(4,PgmId,token);
              return;
             }
          //--now allocate a new token and copy the current
          //--working token buffer into this space. Then put it's
          //--address on the token array.
           if(!(newTOKptr=new char[MaxTokLen+1]))
             {
              *statusPtr=5;
              MtsSendError(2,PgmId,token);
              return;
             }
           strcpy(newTOKptr,token);
           Tokens[*TokCnt]=newTOKptr;
           memset(token,'\0',MaxTokLen);
           (*TokCnt)++;
           k=0;
          }
       }
      else
       {
        if(k>MaxTokLen)
          {
           *statusPtr=3;
           MtsSendError(5,PgmId,token);
           return;
          }
        token[k]=Line[i];
        k++;
       }
      if(i>=bufflen)    return;
      if(Line[i]=='\0') return;
    }
  }
//--The class of builtin token delimiters.
bool IsDelimiter(char byte)
  {
    if(  byte==' '||byte==','||byte==';' ||byte=='/' ||byte=='\\'
      || byte=='('||byte==')'||byte=='\n'||byte=='\t'||byte=='\0')
       return(TRUE);
      else
       return(FALSE);
  }
