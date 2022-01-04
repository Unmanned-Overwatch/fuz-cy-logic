/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| thldnot.cpp  Earl Cox  04/01/93 The Threshold NOT operator  |
| This program prints our the array of truth values for the   |
| threshold compensatory NOT operator.                        |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include   <SystemTypes.hpp>
void THoldCompNOT(double);
void main(void)
 {
  int    i;
  int    Classlmt=5;
  double ClassValues[]= { 0,.25,.50,.75,1.0};


  for(i=0;i<Classlmt;i++)
     THoldCompNOT(ClassValues[i]);
  return;
 }
void THoldCompNOT(double ClassValue)
 {
  int     i,j;
  int     TruthMax=5;
  double  f1,f2,d1;
  double  TruthValue[5]={0.0,0.25,0.50,0.75,1.0};

  fputc('\n',stdout);
  fputc('\n',stdout);
  fprintf(stdout,"%s\n",
   "         THRESHOLD COMPENSATORY FUZZY 'NOT' OPERATORS");
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
     if(f1>=ClassValue) d1= 1.0;
       else             d1= 0.0;
     fprintf(stdout,"%6.4f ",d1);
    }
  fputc('\n',stdout);
 }
