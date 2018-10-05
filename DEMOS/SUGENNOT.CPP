/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| sugennot.cpp Earl Cox  04/01/93 Seugeno Compensatory NOT    |
| This program prints out the linear truth matrix for the     |
| Seugeno Compensatory NOT operator. This operator's strength |
| is determined by a "Class Weight" that acts to intensify    |
| the NOT operation for larger and larger values.             |
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
void SugenoCompNOT(double);
void main(void)
 {
  int    i;
  int    Classlmt=11;
  double ClassValues[]=
   {-.9,-.7,-.5,-.3,-.1,0,1,3,5,7,9};

  for(i=0;i<Classlmt;i++)
     SugenoCompNOT(ClassValues[i]);
  return;
 }
void SugenoCompNOT(double ClassValue)
 {
  int     i,j;
  int     TruthMax=5;
  double  f1,f2,f3,d1;
  double  TruthValue[5]={0.0,0.25,0.50,0.75,1.0};

  fputc('\n',stdout);
  fputc('\n',stdout);
  fprintf(stdout,"%s\n",
   "         SUGENO COMPENSATORY FUZZY 'NOT' OPERATORS");
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
     f2=1-f1;
     f3=1+(ClassValue*f1);
     d1=f2/f3;
     fprintf(stdout,"%6.4f ",d1);
    }
  fputc('\n',stdout);
 }
