/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlgda.cpp  Earl Cox  04/01/93 Get Data                    |
| This procedure extracts a block of data from a buffer       |
| staring at position <strOffset> and going for <forBytes>.   |
| This procedure does not work on null-terminated strings,    |
| so the length must be exact number of bytes you want to     |
| move.                                                       |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
char *MtsGetdata(char *inStr,int strOffset,int strBytes)
  {
    int i,n;
    char *outStr;
//
//--Allocate a new buffer area.
    outStr=new char[strBytes+1];
//
//--Extract the substring
    for(i=strOffset,n=0;n<strBytes;i++,n++) outStr[n]=inStr[i];
    return(outStr);
  }
