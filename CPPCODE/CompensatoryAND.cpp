/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtfzcpa.cpp   Earl Cox  04/01/93 Compensatory AND operators |
| This procedure handles the management of the compensatory   |
| AND facilities. For the algebraic classes the ANDCoeff is   |
| used as a weighting factor if it is not zero or greater than|
| two. For the other classes, the ANDCoeff is used as the     |
| actual class generator function.                            |
*-------------------------------------------------------------*/
#include <math.h>
#include   <mtypes.hpp>
#include   <fuzzy.hpp>
#include <mtsptype.hpp>
double pow(double,double);
float FzyCompAND(
  int ANDClass,double ANDCoeff,float truth1,float truth2,int *statusPtr)
  {
    float    tempTruth;
    char     *PgmId="mtfzcpa";
    *statusPtr=0;
    switch(ANDClass)
     {
      case MEANAND:
       {
        tempTruth=(truth1+truth2)/2;
        if(ANDCoeff!=0&&ANDCoeff<2) tempTruth=tempTruth*(float)ANDCoeff;
        return(tempTruth);
       }
      case PRODUCTAND:
       {
        tempTruth=(truth1*truth2);
        if(ANDCoeff!=0&&ANDCoeff<2) tempTruth=tempTruth*(float)ANDCoeff;
        return(tempTruth);
       }
      case BOUNDEDAND:
       {
        tempTruth=max(0,(truth1+truth2)-1);
        if(ANDCoeff!=0&&ANDCoeff<2) tempTruth=tempTruth*(float)ANDCoeff;
        return(tempTruth);
       }
      case YAGERAND:
       {
        double Exponent=(1/ANDCoeff);
        double Part1=pow((1-truth1),ANDCoeff);
        double Part2=pow((1-truth2),ANDCoeff);
        tempTruth=(float)(1-min(1,pow(Part1+Part2,Exponent)));
        return(tempTruth);
       }
      case ZADEHAND:
       {
        return(min(truth1,truth2));
       }
      default:
       *statusPtr=1;
       MtsSendError(22,PgmId,MtsFormatInt(ANDClass));
       return((float)-1);
     }
  }
