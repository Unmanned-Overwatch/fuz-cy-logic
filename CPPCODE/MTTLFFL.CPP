/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlffl.cpp   Earl Cox  04/01/93 Format a Float variable.   |
| This routine takes a single precison foating point number   |
| and returns a left justified character string containing the|
| number to the specified decimal places.                     |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <mtsptype.hpp>
char *MtsFormatFlt(float Number,int decimals)
  {
    int   i,j,k;
    char  FltBuff[23];
    char *Fmtptr;

    sprintf(FltBuff,"%21.8f",Number);
    j=MtsStrIndex(FltBuff,'.');
    for(i=j+1,k=0;FltBuff[i];i++,k++)
     if(k>decimals-1) FltBuff[i]='\0';
    if(decimals==0) FltBuff[j]='\0';
    if(!(Fmtptr=new char[strlen(FltBuff)+1])) return(NULL);
    strcpy(Fmtptr,FltBuff);
    MtsLeftJustify(Fmtptr);
    return(Fmtptr);
  }
