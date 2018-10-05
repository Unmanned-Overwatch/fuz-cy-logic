/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlipn.cpp  Earl Cox  04/01/93 Is this a Prime Number?     |
| We apply the sieve method of square roots to decide if      |
| the number X is prime.                                      |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <math.h>
#include "mtypes.hpp"
bool MtsIsPrime(long N)
 {
   long   M=2;                      // Two is the smallest prime
   double X=(double)N;              // Convert to double for sqrt
   while(FOREVER)
    {
     if(M>sqrt(X))  return(TRUE);
     if((N/M)*M==N) return(FALSE);
     ++M;
    }
 }
