/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlrnd.cpp  Earl Cox  04/01/93 Uniform Random Number       |
| This facility uses the system random number generator to    |
| return a uniformly distributed random number within the     |
| domain boundaries (inclusive)                               |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdlib.h>
#include <time.h>
double MtsRandomNumber(void)
 {
  return((double)rand()/(double)RAND_MAX);
 }
