/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtfzcpo.cpp   Earl Cox  04/01/93 Compensatory OR operators  |
| This procedure handles the management of the compensatory   |
| OR facilities. For the algebraic classes the ORCoeff is     |
| used as a weighting factor if it is not zero or greater than|
| two. For the other classes, the ORCoeff is used as the      |
| actual class generator function.                            |
*-------------------------------------------------------------*/
#include <math.h>
#include "mtypes.hpp"
#include "fuzzy.hpp"
#include "mtsptype.hpp"
double pow(double,double);
float FzyCompOR(
  int ORClass,double ORCoeff,float truth1,float truth2,int *statusPtr)
  {
    float tempTruth,t1,t2;
    char *PgmId="mtfzcpo";
    *statusPtr=0;
    switch(ORClass)
     {
      case MEANOR:
       {
        tempTruth=(truth1+truth2)/2;
        t1=2*min(truth1,truth2);
        t2=4*max(truth1,truth2);
        tempTruth=(t1+t2)/6;
        if(ORCoeff!=0&&ORCoeff<2) tempTruth=tempTruth*(float)ORCoeff;
        return(tempTruth);
       }
      case PRODUCTOR:
       {
        tempTruth=(truth1*truth2);
        if(ORCoeff!=0&&ORCoeff<2) tempTruth=tempTruth*(float)ORCoeff;
        return(tempTruth);
       }
      case BOUNDEDOR:
       {
        tempTruth=max(0,(truth1+truth2)-1);
        if(ORCoeff!=0&&ORCoeff<2) tempTruth=tempTruth*(float)ORCoeff;
        return(tempTruth);
       }
      case YAGEROR:
       {
        double Exponent=(1/ORCoeff);
        double Part1=pow(truth1,ORCoeff);
        double Part2=pow(truth2,ORCoeff);
        tempTruth=(float)(min(1,pow(Part1+Part2,Exponent)));
        return(tempTruth);
       }
      case ZADEHOR:
       {
        return(max(truth1,truth2));
       }
      default:
       *statusPtr=1;
       MtsSendError(22,PgmId,MtsFormatInt(ORClass));
       return((float)-1);
     }
  }
