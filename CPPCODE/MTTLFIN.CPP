/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlfin.cpp   Earl Cox  04/01/93 Format an Integer variable |
| This routine takes an integer number and returns a left     |
| justified character string containing the number.           |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <SystemPrototypes.hpp>
char *MtsFormatInt(int Number)
  {
    char  IntBuff[23];
    char *Fmtptr;

    sprintf(IntBuff,"%16d",Number);
    if(!(Fmtptr=new char[strlen(IntBuff)+1])) return(NULL);
    strcpy(Fmtptr,IntBuff);
    MtsLeftJustify(Fmtptr);
    return(Fmtptr);
  }
