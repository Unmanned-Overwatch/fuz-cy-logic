/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlpss.cpp  Earl Cox  04/01/93 Put Substring               |
| This procedure puts one string into another string. We take |
| the source string <srcStr> and put it into the target string|
| <tgtStr> starting at the specified offset for the required  |
| numer of bytes. NOTE: the target string must be large       |
| enough to accompdate the expansion. Function works as:      |
|                                                             |
|   MtsPutsubstr(s1,s2,4,8)                                   |
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
void MtsPutsubstr(
   char *tgtStr,char *srcStr,int strOffset,int strBytes)
  {
    int i,n,strSize,strLength;
//
//--Get the actual size of the source string and do some preliminary
//--checks. We also calculate the correct extraction length.
    strSize=strlen(srcStr);
    strLength=strBytes;
    if(strBytes>strSize)  strLength=strSize;
//
//--Move in the substring
    for(n=strOffset,i=0;i<strLength;i++,n++) tgtStr[n]=srcStr[i];
    return;
  }
