/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| yagerand.cpp Earl Cox  04/01/93 Yager Compensatory AND      |
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
void YagerCompAND(double);
void main(void)
 {
  int    i;
  int    Classlmt=12;
  double ClassValues[]=
   {1,2,6,8,12,16,24,32,48,64,96,128};

  for(i=0;i<Classlmt;i++)
     YagerCompAND(ClassValues[i]);
  return;
 }
void YagerCompAND(double ClassValue)
 {
  int     i,j;
  int     TruthMax=5;
  double  f1,f2,f3;
  double  TruthValue[5]={0.0,0.25,0.50,0.75,1.0};
  double  d1;

  fprintf(stdout,"%s\n",
   "         YAGER COMPENSATORY FUZZY 'AND' OPERATORS");
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
  for(i=0;i<TruthMax;i++)
   {
     fprintf(stdout,"%3.2f%s",TruthValue[i]," |  ");
     f1=TruthValue[i];
     for(j=0;j<TruthMax;j++)
      {
       f2=TruthValue[j];
       f3=pow((1-f1),ClassValue)+pow((1-f2),ClassValue);
       d1=pow(f3,(1/ClassValue));
       d1=1-min(1,d1);
       fprintf(stdout,"%6.4f ",d1);
      }
     fputc('\n',stdout);
   }
  fputc('\n',stdout);
 }
