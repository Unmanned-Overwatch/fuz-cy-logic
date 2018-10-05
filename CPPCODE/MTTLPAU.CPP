/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlpau.cpp  Earl Cox  04/01/93 Issue a Pause               |
| This facility issues a pause. Note that it uses "gets" so   |
| that the amount of text entered cannot be controlled. This  |
| should be used as a diagnostic tool only!                   |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
void Mtspause(void)
 {
   char  ioBuff[8];
   printf("\nPAUSE........press <enter> to continue\n");
   fflush(stdin);
   gets(ioBuff);
   return;
 }
