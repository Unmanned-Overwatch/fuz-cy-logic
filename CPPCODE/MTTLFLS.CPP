/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlfls.cpp   Earl Cox  04/01/93 Fill String with Character |
| This routine relaces every blank of tab character with a    |
| character supplied by the user.                             |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
void MtsFillString(char *String,char Byte)
 {
   int i;
   for(i=0;String[i];i++)
     if(String[i]==' '||String[i]=='\t') String[i]=Byte;
   return;
 }
