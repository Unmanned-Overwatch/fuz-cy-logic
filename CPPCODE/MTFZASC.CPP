/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtfzasc.cpp   Earl Cox  04/01/93  Fuzzyset Autoscaling      |
| This procedure takes the hi and lo domains of the fuzzyset  |
| and returns a scaling factor so that the value will fit     |
| within the standard display window (about 10.2)             |
*-------------------------------------------------------------*/
#include <cmath>
#include <cstdlib>
double log10(double);
double fabs(double);
float FzyAutoScale(double Hi,double Lo)
  {
    float Scale=1.0;
    int   Power=0;
    if(Hi!=0) Power=(int)log10(fabs(Hi));
    if(Lo!=0)
      {
       double LogofLo=log10(fabs(Lo));
       if(Power<LogofLo) Power=(int)LogofLo;
      }
    if(Lo<0||Hi<0) ++Power;
    if(Power>1) Scale=(float)pow(10,Power-1);
    return(Scale);
  }
