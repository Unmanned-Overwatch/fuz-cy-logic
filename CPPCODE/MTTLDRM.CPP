/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttldrm.cpp  Earl Cox  04/01/93 Display remaining memory    |
| This procedure fetches the amount of remaining memory using |
| Borland's coreleft routine and writes it to the indicated   |
| medium.                                                     |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <alloc.h>
unsigned long MtsDisplayCoreLeft(char *Message,int *statusPtr)
 {
  *statusPtr=0;
  unsigned long CoreLeft=coreleft();
  if(strlen(Message)!=0)
     fprintf(stdout,"%s: %lu\n",Message,CoreLeft);
  return(CoreLeft);
 }
