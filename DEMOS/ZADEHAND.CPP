/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| zadehand.cpp Earl Cox  04/01/93 Zadeh Min/Max AND operator  |
| This program prints out the MxN matrix for the standard     |
| Zadeh min/max AND operator across selected truth values.    |
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
void ZadehMinMaxAND(void);
void main(void)
 {
  ZadehMinMaxAND();
  return;
 }
void ZadehMinMaxAND(void)
 {
  int     i,j;
  int     TruthMax=5;
  double  f1,f2,f3;
  double  TruthValue[5]={0.0,0.25,0.50,0.75,1.0};
  double  d1;

  fprintf(stdout,"%s\n",
   "         ZADEH MIN/MAX FUZZY 'AND' OPERATORS");
  fputc('\n',stdout);
  fprintf(stdout,"%s","        ");
  for(i=0;i<TruthMax;i++)
    fprintf(stdout,"%6.4f ",TruthValue[i]);
  fputc('\n',stdout);
  fprintf(stdout,"%s","        ");
  for(i=0;i<TruthMax;i++)
    fprintf(stdout,"%s"   ,"------ "    );
  fputc('\n',stdout);
  for(i=0;i<TruthMax;i++)
   {
     fprintf(stdout,"%3.2f%s",TruthValue[i]," |  ");
     f1=TruthValue[i];
     for(j=0;j<TruthMax;j++)
      {
       f2=TruthValue[j];
       d1=min(f1,f2);
       fprintf(stdout,"%6.4f ",d1);
      }
     fputc('\n',stdout);
   }
  fputc('\n',stdout);
 }
