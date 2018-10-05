/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlljf.cpp   Earl Cox  04/01/93 Left Justify String        |
| Given a character string with leading blanks, this routine  |
| will left justify the contents.                             |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
void MtsLeftJustify(char *String)
 {
  int i,j,k;
  int strlength=strlen(String);
  for(i=0;i<strlength;i++)
   if(String[i]!=' '&&String[i]!='\t')
     {
      if(i==0) return;
      for(j=0,k=i;j<strlength;j++,k++) String[j]=String[k];
      return;
     }
   return;
 }
