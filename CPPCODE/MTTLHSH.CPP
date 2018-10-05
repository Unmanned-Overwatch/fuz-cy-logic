/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlhsh.cpp   Earl Cox  04/01/93 The Hashing Algorithm      |
| This is a straight-forward modulo hash used for all the     |
| in-core directories. We treat the identifier as a character |
| string; take the numeric value of the Ascii byte, shift it  |
| left two bits, and fold it into the compisite key. We then  |
| take the key moduo the slots to generate a hash address.    |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stddef.h>
long MtsHashString(char *StrItem,long MaxSlots)
  {
   if(StrItem==NULL) return((long)-1);
   if(MaxSlots<1)    return((long)-2);
   unsigned long Hval=0;               //initialize hash
   char *Byteptr=StrItem;              //get address of identifier
   for(;*Byteptr;++Byteptr)
    {
      Hval<<=1;                        //shift one bit to left
      Hval+=*Byteptr;                  //add in the byte value
    }
   return((long)(Hval%MaxSlots));      //take the modulo
  }
