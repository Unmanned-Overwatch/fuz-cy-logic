/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlpmt.cpp  Earl Cox  04/01/93 Prompt for Data             |
| These are line based procedures that ask for specic kinds of|
| information.                                                |
|                                                             |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
void DisplayValues(char*,char**,int,int);
//
double MtsAskforDBL(
  char *varid,char *prompt,double Domain[],int TryCtl[],int *statusPtr)
/*------------------------------------------------------------*
| This procedure prompts for a double precision floating      |
| point number. You can provide a domain minimum and maximum  |
| value so that the entered value is constrained within this  |
| limit.                                                      |
*-------------------------------------------------------------*/
 {
  char    dblBuff[21];
  int     numtype;
  bool    forever=TRUE;
  double  DBLdata=0;

  *statusPtr=0;
  while(forever)
   {
    fflush(stdin);
    printf(prompt);
//  scanf("%lf",&DBLdata);
    gets(dblBuff);
    if(!MtsIsNumeric(dblBuff,&numtype))
      {
       fprintf(stdout,"%s%s%s%s%s",
        "Error--This '",varid,"' value  of ",dblBuff," is not numeric");
       (TryCtl[1])++;
       if(TryCtl[1]>TryCtl[0])
         {
          *statusPtr=9;
          printf(
          "NOTE--Excessive data request failures. Terminating\n");
          return(DBLdata);
         }
      }
    DBLdata=atof(dblBuff);
    if(DBLdata<Domain[0]||DBLdata>Domain[1])
      {
       fprintf(stdout,"%s%s%s%10.3f%s\n%s%10.3f%s%10.3f\n",
        "Error--This '",varid,"' value  of ",DBLdata," is out of bounds",
        "       Domain is ",Domain[0]," to ",Domain[1]       );
       (TryCtl[1])++;
       if(TryCtl[1]>TryCtl[0])
         {
          *statusPtr=9;
          printf(
          "NOTE--Excessive data request failures. Terminating\n");
          return(DBLdata);
         }
      }
    else
     return(DBLdata);
   }
//--we should never get here, but this will protect us if the
//--code logic should change.
  return(DBLdata);
 }
//
long MtsAskforINT(
  char *varid,char *prompt,double Domain[],int TryCtl[],int *statusPtr)
/*------------------------------------------------------------*
| This procedure prompts for a long integer (32 bit) number.  |
| You can provide a domain minimum and maximum value so that  |
| the entered value is constrained within this limit.         |
*-------------------------------------------------------------*/
 {
  char    intBuff[21];
  int     numtype;
  bool    forever=TRUE;
  long    INTdata=0;

  *statusPtr=0;
  while(forever)
   {
    fflush(stdin);
    printf(prompt);
    gets(intBuff);
    if(!MtsIsNumeric(intBuff,&numtype))
      {
       fprintf(stdout,"%s%s%s%s%s",
        "Error--This '",varid,"' value  of ",intBuff," is not numeric");
       (TryCtl[1])++;
       if(TryCtl[1]>TryCtl[0])
         {
          *statusPtr=9;
          printf(
          "NOTE--Excessive data request failures. Terminating\n");
          return(INTdata);
         }
      }
    if(numtype!=INTEGER)
      {
       fprintf(stdout,"%s%s%s%s%s",
        "Error--This '",varid,
          "' value  of ",intBuff," is not an integer");
       (TryCtl[1])++;
       if(TryCtl[1]>TryCtl[0])
         {
          *statusPtr=9;
          printf(
          "NOTE--Excessive data request failures. Terminating\n");
          return(INTdata);
         }
      }
    INTdata=atol(intBuff);
    if(INTdata<Domain[0]||INTdata>Domain[1])
      {
       fprintf(stdout,"%s%s%s%10ld%s\n%s%10.3f%s%10.3f\n",
        "Error--This '",varid,"' value  of ",INTdata," is out of bounds",
        "       Domain is ",Domain[0]," to ",Domain[1]       );
       (TryCtl[1])++;
       if(TryCtl[1]>TryCtl[0])
         {
          *statusPtr=9;
          printf(
          "NOTE--Excessive data request failures. Terminating\n");
          return(INTdata);
         }
      }
    else
     return(INTdata);
   }
//--we should never get here, but this will protect us if the
//--code logic should change.
  return(INTdata);
 }
//
//
char  *MtsAskforSTR(
  char *varid,char *prompt,int maxlen,int TryCtl[],int *statusPtr)
/*------------------------------------------------------------*
| This procedure prompts for a character string. If you have  |
| provided a table of allowable values, then your response is |
| compared against the table entries and must match one. You  |
| can also enter a "?" to see trhe list of valiud values.     |
*-------------------------------------------------------------*/
 {
  bool    forever=TRUE;
  char    wrkBuff[180];
  char   *rsltBuff=NULL;
  int     j;

  *statusPtr=0;
  fflush(stdin);
  while(forever)
   {
    fflush(stdin);
    printf(prompt);
    gets(wrkBuff);
    if((j=strlen(wrkBuff))>maxlen)
      {
       fprintf(stdout,"%s%s%s%s%s\n%s%4d%s\n",
        "Error--This '",varid,"' value  of \"",wrkBuff,"\" is too long",
        "       String cannot exceed ",maxlen," characters.");
       (TryCtl[1])++;
       if(TryCtl[1]>TryCtl[0])
         {
          *statusPtr=9;
          printf(
          "NOTE--Excessive data request failures. Terminating\n");
          return(rsltBuff);
         }
      }
     else
      {
       rsltBuff=new char[j+1];
       if(rsltBuff!=NULL) strcpy(rsltBuff,wrkBuff);
       return(rsltBuff);
      }
   }
//--we should never get here, but this will protect us if the
//--code logic should change.
  return(rsltBuff);
 }

//
//
char  *MtsAskforVAL(
  char *varid,char *prompt,
    char **Classes,int Clcnt,int MinLen,
      int *ClIDX,int TryCtl[],int *statusPtr)
/*------------------------------------------------------------*
| This procedure prompts for a class member value. If you     |
| provide  a table of allowable values, then your response is |
| compared against the table entries and must match one. You  |
| can also enter a "?" to see trhe list of valiud values.     |
*-------------------------------------------------------------*/
 {
  bool    forever=TRUE;
  char    wrkBuff[180];
  char   *rsltBuff=NULL;
  int     i,j,match;

  *statusPtr=0;
  while(forever)
   {
    fflush(stdin);
    printf(prompt);
    gets(wrkBuff);
    j=strlen(wrkBuff);
    if(strcmp(wrkBuff,"?")==0)
      {
        printf("OK...\n");
        DisplayValues(varid,Classes,Clcnt,MinLen);
      }
    else if(Clcnt==0)
     {
      rsltBuff=new char[j+1];
      if(rsltBuff!=NULL) strcpy(rsltBuff,wrkBuff);
      return(rsltBuff);
     }
     else if(Clcnt>0)
      {
       for(i=0;i<Clcnt;i++)
        {
         if(MinLen==CHECKALL)
            match=strcmpi(wrkBuff,Classes[i]);
           else
            match=strncmp(wrkBuff,Classes[i],j);
         if(match==0)
           {
            *ClIDX=i;
            j=strlen(Classes[i]);
            rsltBuff=new char[j+MEMBUFF];
            if(rsltBuff!=NULL) strcpy(rsltBuff,Classes[i]);
            return(rsltBuff);
           }
        }
       fprintf(stdout,"%s%s%s%s%s\n",
        "Error--This '",varid,"' value  of \"",wrkBuff,"\" is illegal");
       DisplayValues(varid,Classes,Clcnt,MinLen);
       (TryCtl[1])++;
       if(TryCtl[1]>TryCtl[0])
         {
          *statusPtr=9;
          printf(
          "NOTE--Excessive data request failures. Terminating\n");
          return(rsltBuff);
         }
      }
   }
//--we should never get here, but this will protect us if the
//--code logic should change.
  return(rsltBuff);
 }

//
//
bool MtsAskforBOOL(
  char *varid,char *prompt,int TryCtl[],int *statusPtr)
/*------------------------------------------------------------*
| This procedure prompts for a boolean string. You can enter  |
| any value that is recognized as a valid boolean.            |
*-------------------------------------------------------------*/
 {
  bool    forever=TRUE;
  char    wrkBuff[180];
  int     value;

  *statusPtr=0;
  fflush(stdin);
  while(forever)
   {
    printf(prompt);
    gets(wrkBuff);
    if(MtsIsBoolean(wrkBuff,&value)) return(value);
    fprintf(stdout,"%s%s%s%s%s\n%s\n",
      "Error--This '",varid,"' value  of \"",wrkBuff,"\" is not valid",
      "       You reponse muse be a Yes or No.");
    (TryCtl[1])++;
    if(TryCtl[1]>TryCtl[0])
      {
       *statusPtr=9;
       printf(
        "NOTE--Excessive data request failures. Terminating\n");
       return(0);
      }
   }
//--we should never get here, but this will protect us if the
//--code logic should change.
  return(0);
 }

void DisplayValues(char *varid,char **Classes,int Clcnt,int MinLen)
 {
  int i;
  fprintf(stdout,"%s%4d%s%s%s\n",
    "There are ",Clcnt," allowable values for '",varid,"':");
  for(i=0;i<Clcnt;i++)
     {
      fprintf(stdout,"%4d%s%s\n",i+1,". ",Classes[i]);
     }
  if(MinLen==CHECKALL)
      fprintf(stdout,"%s\n","You must enter an exact match.");
    else
      fprintf(stdout,"%s%2d%s\n","Your choice must match the first ",
        MinLen," characters.");
  fprintf(stdout,"%s\n"," ");
  return;
 }

