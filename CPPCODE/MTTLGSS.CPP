/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlgss.cpp  Earl Cox  04/01/93 Get Substring               |
| This procedure extracts a sub-string from a character string|
| staring at position <strOffset> and going for <forBytes>.   |
| if the length of the substring at the offset exceeds the    |
| length of the source string, we assume we are just taking   |
| the remainder of the source string.                         |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
char *MtsGetsubstr(char *inStr,int strOffset,int strBytes)
  {
    int i,n,strSize,strLength;
    char *outStr,*nullstr=NULL;
//
//--Get the actual size of the source string and do some preliminary
//--checks. We also calculate the correct extraction length.
    strSize=strlen(inStr);
    if(strOffset>strSize) return(nullstr);
    if((strOffset+strBytes)>strSize) strLength=strSize-(strOffset+1);
        else                         strLength=strBytes;
//
//--Allocate a new string area and initialize it with terminators
    outStr=new char[strLength+1];
    memset(outStr,'\0',strLength+1);
//
//--Extract the substring
    for(i=strOffset,n=0;n<strLength;i++,n++) outStr[n]=inStr[i];
    return(outStr);
  }
