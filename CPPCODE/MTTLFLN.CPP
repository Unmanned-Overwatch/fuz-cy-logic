/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlfln.cpp   Earl Cox  04/01/93 Format a long int variable |
| This routine takes an long integer and returns a left       |
| justified character string containing the number.           |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "mtsptype.hpp"
char *MtsFormatLong(long Number)
  {
    char  LngBuff[23];
    char *Fmtptr;

    sprintf(LngBuff,"%16ld",Number);
    if(!(Fmtptr=new char[strlen(LngBuff)+1])) return(NULL);
    strcpy(Fmtptr,LngBuff);
    MtsLeftJustify(Fmtptr);
    return(Fmtptr);
  }
