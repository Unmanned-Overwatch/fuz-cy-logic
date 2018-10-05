/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlisb.cpp   Earl Cox  04/01/93 Is Item a Boolean?         |
| This routines checks to see whether or not the <item> is    |
| some kind of boolean representation. This function looks    |
| at character strings so it is independent of the symbolic   |
| booleans stored in the mtypes.hpp header. We use a case     |
| independent string compare to check the results.            |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|  1     n/a 01/21/93       1    0  changed to "strcmpi" so   |
|  string comparisons are not case senstitive. Added "1" and  |
|  "0" as possible boolean character strings. [EDC]           |
*-------------------------------------------------------------*/
#include <string.h>
#include   <mtypes.hpp>
bool MtsIsBoolean(char *Item,int *Boolvalue)
 {
   *Boolvalue=-1;
   if(strcmpi(Item,"y")==0)      *Boolvalue=1;
   if(strcmpi(Item,"n")==0)      *Boolvalue=0;

   if(strcmpi(Item,"1")==0)      *Boolvalue=1;
   if(strcmpi(Item,"0")==0)      *Boolvalue=0;

   if(strcmpi(Item,"yes")==0)    *Boolvalue=1;
   if(strcmpi(Item,"no")==0)     *Boolvalue=0;

   if(strcmpi(Item,"on")==0)     *Boolvalue=1;
   if(strcmpi(Item,"off")==0)    *Boolvalue=0;

   if(strcmpi(Item,"true")==0)   *Boolvalue=1;
   if(strcmpi(Item,"false")==0)  *Boolvalue=0;
//
//--if the default boolean value is still negative, then
//--none of the compares suceeded. The input value is not
//--a boolean, so we return false, otherwise we return true.
   if(*Boolvalue==-1) return(FALSE);
   return(TRUE);
 }
