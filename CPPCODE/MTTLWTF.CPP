/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlwtf.cpp  Earl Cox  04/01/93 Write String to File        |
| This procedure opens a new file under the indicated name    |
| and then writes the string to this file.                    |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mtsptype.hpp"
void MtsWritetoFile(
  char *outrec,int reclen,char *outputfn,char *fnMode,int *statusPtr)
 {
  FILE   *outfp;
  if((outfp=fopen(outputfn,fnMode))==NULL)
    {
      perror(outputfn);
      exit(5);
    }
  fwrite(outrec,reclen,1,outfp);
  if(ferror(outfp))
    {
     perror(outputfn);
     exit(7);
    }
  fflush(outfp);
  fclose(outfp);
 }
