/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttldtc.cpp   Earl Cox  04/01/93 Display Token Chain        |
| This utility routine is called to display the contents of   |
| each node in a native token chain.                          |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "toknode.hpp"
#include "mtsptype.hpp"
#define  VERYBIG  1024
static char far * far TokenType[] =
     {
      "String",
      "Quoted String",
      "Operator",
      "Function",
      "Integer",
      "Floating Point",
      "Fuzzy Set",
      "Hedge",
      "Variable",
      "Hedged Fuzzy Set",
      "UNKNOWN"
     };
static const int TokTypemax=9;
void MtsDisplayTokens(TokenNode *Tokenhd,char *Title)
 {
   TokenNode   *Tokptr;
   char         wrkBuff[12];
   int          Tokno,TypeIdx;

   Tokno=1;
   Tokptr=Tokenhd;
   fprintf(stdout,"%s\n",Title);
   while(Tokptr!=NULL)
    {
     if(Tokno>VERYBIG)
       {
        fprintf(stdout,"%s\n","Too many tokens [probable bad pointer]");
        return;
       }
     fprintf(stdout,"%4d%s%s\n",
         Tokno++,". Token       : ",Tokptr->token);
     fprintf(stdout,"%s%d\n",
         "      Length      : ",Tokptr->toklen );
     if((TypeIdx=Tokptr->toktype)>TokTypemax) TypeIdx=TokTypemax+1;
     fprintf(stdout,"%s%s\n",
         "      Type        : ",TokenType[TypeIdx]);
     fprintf(stdout,"%s%d\n",
         "      SymValue    : ",Tokptr->toksym);
     Tokptr=Tokptr->toknext;
    }
  fprintf(stdout,"%s\n","End of Tokens");
  fflush(stdin);
  printf("%s\n","Press Any Key to Continue");
  gets(wrkBuff);
  return;
 }
