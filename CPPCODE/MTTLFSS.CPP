/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlfss.cpp  Earl Cox  04/01/93 Find a Substring            |
| This procedure finds one string in another string.  We take |
| the source string <srcStr> and search through the target    |
| <tgtStr> starting at the indicated byte offset and compares |
| for the number of bytes in the source. It works like this:  |
|                                                             |
|   MtsFindsubstr(s1,s2,4)                                    |
|                                                             |
| search <s1> for an occurrence of <s2> starting at byte 4.   |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include   <SystemTypes.hpp>
bool stringsEqual(char*,char*,int,int);
//
int MtsFindsubstr(char *tgtStr,char *srcStr,int strOffset)
  {
    int i,n,srcLength,tgtLength;

    tgtLength=strlen(tgtStr);
    srcLength=strlen(srcStr);
    for(i=strOffset,n=0;n<tgtLength-srcLength;i++,n++)
         if(stringsEqual(tgtStr,srcStr,i,srcLength)) return(i);
    return(-1);
  }
//
bool stringsEqual(char *s1,char *s2,int from,int length)
  {
   int k,i;
   for(k=from,i=0;i<length;k++,i++) if(s1[k]!=s2[i]) return(FALSE);
   return(TRUE);
  }
