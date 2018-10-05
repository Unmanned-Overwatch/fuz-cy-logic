/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlcls.cpp   Earl Cox  04/01/93 Center a Literal String    |
| We use this routine to center the contents of a literal     |
| string. Note that this procedure is destructive.            |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
void MtsCenterString(char *String,int FieldWidth)
 {
  int    i,j,k,offset,Rightedge;
//
//--Get the string length and calculate the amount of space
//--we need on the left side to center the string. If the
//--string is as wide or wider than the field length, just
//--return.
  j=strlen(String);
  if(j>=FieldWidth) return;
  offset=(FieldWidth-j)/2;
  Rightedge=j+offset;
//
//--Set all the unused string elements to blanks and then
//--re-insert the NULL byte.
  for(i=j;i<FieldWidth;i++) String[i]=' ';
  String[Rightedge+1]='\0';
//
//--Okay, we now move each byte out to its proper position
//--and, at the same time, erase the byte we leave behind.
//--when i=0, we have moved everything, so we leave.
  for(k=Rightedge-1,i=j-1;;k--,i--)
   {
    String[k]=String[i];
    String[i]=' ';
    if(i==0) return;
   }
 }
