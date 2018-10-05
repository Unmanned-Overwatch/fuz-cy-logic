/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlpda.cpp  Earl Cox  04/01/93 Put Data                    |
| This procedure puts a block of character data into another  |
| block at a specified starting position and for the length   |
| indicated. No null-terinator testing is performed.          |
|                                                             |
|   MtsPutdata(s1,s2,4,8)                                     |
|                                                             |
| move into <s1> at byte 4, the first 8 bytes of string <s2>  |
| and make sure that <s1> is still a valid C string.          |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
void MtsPutdata(
   char *tgtStr,char *srcStr,int strOffset,int strBytes)
  {
    int i,n;
//
//--Move in the substring
    for(n=strOffset,i=0;i<strBytes;i++,n++) tgtStr[n]=srcStr[i];
    return;
  }
