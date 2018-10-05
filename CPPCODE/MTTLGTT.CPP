/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlgtt.cpp  Earl Cox  04/01/93 Get Time Information        |
| This function accesses the DOS time structure and returns   |
| the current time of day.                                    |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stddef.h>
#include <string.h>
#include <dos.h>
#include "mtypes.hpp"
#include "mtsptype.hpp"
char *MtsGetTime(int *statusPtr)
 {
  dostime_t   thisTime;
  char       *ToDayTimeptr,*nullChar=NULL;
  const int   Timelen=8;
  _dos_gettime(&thisTime);
  if(!(ToDayTimeptr=new char[Timelen]))
    {
     *statusPtr=1;
     return(nullChar);
    }
  sprintf(ToDayTimeptr,"%02d%02d%02d",
    thisTime.hour,thisTime.minute,thisTime.second);
  return(ToDayTimeptr);
 }
