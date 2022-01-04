/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlfdo.cpp   Earl Cox  04/01/93 Format a Double variable   |
| This routine takes a double precison foating point number   |
| and returns a left justified character string cotaining the |
| number to the specified decimal places.                     |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <SystemPrototypes.hpp>
char *MtsFormatDbl(double Number,int decimals)
  {
    int   i,j,k;
    char  DblBuff[23];
    char *Fmtptr;

    sprintf(DblBuff,"%21.8f",Number);
    j=MtsStrIndex(DblBuff,'.');
    for(i=j+1,k=0;DblBuff[i];i++,k++)
     if(k>decimals-1) DblBuff[i]='\0';
    if(decimals==0) DblBuff[j]='\0';
    if(!(Fmtptr=new char[strlen(DblBuff)+1])) return(NULL);
    strcpy(Fmtptr,DblBuff);
    MtsLeftJustify(Fmtptr);
    return(Fmtptr);
  }
