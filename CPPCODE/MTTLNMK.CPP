/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlnmk.cpp  Earl Cox  04/01/93 Normalize Key for Hashing   |
| This procedure modifies the contents of a character string  |
| by removing white space, left justifying the string, etc.   |
| REPLACE THIS FUNCTION WITH YOUR OWN NORMALIZATION FUNCTION  |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include "string.h"
#include "ctype.h"
#include   <mtypes.hpp>
#include <mtsptype.hpp>
void MtsNormalizeKey(char *hashKey)
 {
  char   tempKey[128],byte;
  int    i,t_pos,keylen;

  MtsLeftJustify(hashKey);
  keylen=min(strlen(hashKey),128);
  t_pos=0;
  for(i=0;i<keylen;i++)
     if(hashKey[i]!=' '&&hashKey[i]!='\t')
       {
        byte=toupper(hashKey[i]);
        tempKey[t_pos]=byte;
        t_pos++;
       }
  memset(hashKey,'\0',keylen);
  for(i=0;i<t_pos;i++) hashKey[i]=tempKey[i];
  return;
 }
