/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlsix.cpp   Earl Cox  04/01/93  String Index Function.    |
| This routine finds the location of a character in a string. |
| We use this instead of the built-in functions to get the    |
| actual offset in the string.                                |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
int MtsStrIndex(char *String,char Item)
 {
   int i;
   for(i=0;String[i];i++) if(String[i]==Item) return(i);
   return(-1);
 }
