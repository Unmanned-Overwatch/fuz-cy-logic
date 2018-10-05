/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlrou.cpp  Earl Cox  04/01/93 Round off float double      |
| This procedure rounds a double precision floating point to  |
| the indicated precision.                                    |
|                                                             |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
double MtsRound(double Number,int position,int *statusPtr)
 {
  *statusPtr=0;
  double factor=pow(10,position);
  double tempNumber=floor((Number*factor)+.5000);
  return(tempNumber/factor);
 }
