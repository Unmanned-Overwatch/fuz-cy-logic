/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| yagernot.cpp Earl Cox  04/01/93 Yager Compensatory NOT      |
| This program prints our the MxN matrix space for the Yager  |
| compensatory NOT. This NOT operator is mediated by a class  |
| weight that causes the NOT operation to approach the Zadeh  |
| definition as the weight increases in value.                |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "mtypes.hpp"
void YagerCompNOT(double);
void main(void)
 {
  int    i;
  int    Classlmt=7;
  double ClassValues[]= {.7,.5,1,2,3,4,5};


  for(i=0;i<Classlmt;i++)
     YagerCompNOT(ClassValues[i]);
  return;
 }
void YagerCompNOT(double ClassValue)
 {
  int     i,j;
  int     TruthMax=5;
  double  f1,f2,d1;
  double  TruthValue[5]={0.0,0.25,0.50,0.75,1.0};

  fputc('\n',stdout);
  fputc('\n',stdout);
  fprintf(stdout,"%s\n",
   "         YAGER COMPENSATORY FUZZY 'NOT' OPERATORS");
  fprintf(stdout,"%s%4.2f\n",
   "                Class Intensity Value: ",ClassValue);
  fputc('\n',stdout);
  fprintf(stdout,"%s","        ");
  for(i=0;i<TruthMax;i++)
    fprintf(stdout,"%6.4f ",TruthValue[i]);
  fputc('\n',stdout);
  fprintf(stdout,"%s","        ");
  for(i=0;i<TruthMax;i++)
    fprintf(stdout,"%s"   ,"------ "    );
  fputc('\n',stdout);
  fprintf(stdout,"%s","    |  ");
  for(j=0;j<TruthMax;j++)
    {
     f1=TruthValue[j];
     f2=1-pow(f1,ClassValue);
     d1=pow(f2,(1/ClassValue));
     fprintf(stdout,"%6.4f ",d1);
    }
  fputc('\n',stdout);
 }
