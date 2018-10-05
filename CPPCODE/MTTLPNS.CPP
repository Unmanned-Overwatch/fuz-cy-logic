/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlpns.cpp  Earl Cox  04/01/93 Generate a table of Primes  |
| This procedure produces an array containing primes from     |
| one through a limit imposed by the user.                    |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <math.h>
#include <mtsptype.hpp>
void Mtsprimes(int maxPrimes,int Primes[],int *PCnt,int *statusPtr)
 {
  long MaxNum;
  int  i;
//--Figure out the maximum number that we can use on a 32 bit
//--machine. This will always terminate our loop.
  MaxNum=(long)pow(2,31)-1;
  *PCnt=0;
  *statusPtr=0;
  for(i=2;;i++)
    {
     if(MtsIsPrime(i))
       {
        Primes[*PCnt]=i;
        if(*PCnt>=maxPrimes) return;
        if(i>MaxNum)
          {
           *statusPtr=1;
           return;
          }
        (*PCnt)++;
       }
    }
 }
