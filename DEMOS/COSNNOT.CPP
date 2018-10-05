/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| cosnnot.cpp  Earl Cox  04/01/93 The Cosine NOT operator     |
| This program prints the truth vector for the cosine type    |
| NOT operator.                                               |
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
void CosineCompNOT(double);
void main(void)
 {
  int    i;
  int    Classlmt=5;
  double ClassValues[]= { 0,.25,.50,.75,1.0};

  for(i=0;i<Classlmt;i++)
     CosineCompNOT(ClassValues[i]);
  return;
 }
void CosineCompNOT(double ClassValue)
 {
  int     i,j;
  int     TruthMax=5;
  double  f1,f2,d1;
  double  Pi=3.14159;
  double  TruthValue[5]={0.0,0.25,0.50,0.75,1.0};

  fputc('\n',stdout);
  fputc('\n',stdout);
  fprintf(stdout,"%s\n",
   "         COSINE COMPENSATORY FUZZY 'NOT' OPERATORS");
  fprintf(stdout,"%s%4.2f\n",
   "                Threshold Truth Value: ",ClassValue);
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
     d1=.5*(1+cos(Pi*f1));
     fprintf(stdout,"%6.4f ",d1);
    }
  fputc('\n',stdout);
 }
