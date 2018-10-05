/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| altors.cpp   Earl Cox  04/01/93 The Algebraic OR operators  |
| This program produces the MxM truth tables for various      |
| types of non-Zadeh OR operators.                            |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include   <mtypes.hpp>
void main(void)
 {
  int    i,j;
  int    Classlmt=12;
  int     TruthMax=5;
  double  f1,f2;
  double  TruthValue[5]={0.0,0.25,0.50,0.75,1.0};
  double  d1,d2,d3;

//
//--The Mean operators
//
  fprintf(stdout,"%s\n",
   "         WEIGHTED MEAN (AVERAGE) FUZZY 'OR' OPERATOR");
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
       d2=2*min(f1,f2);
       d3=4*max(f1,f2);
       d1=min(1,(d2+d3)/6);
       fprintf(stdout,"%6.4f ",d1);
      }
     fputc('\n',stdout);
   }
  fputc('\n',stdout);
//
  fprintf(stdout,"%s\n",
   "         PROBABILISTIC SUM FUZZY 'OR' OPERATOR");
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
       d2=(f1+f2);
       d3=(f1*f2);
       d1=d2-d3;
       fprintf(stdout,"%6.4f ",d1);
      }
     fputc('\n',stdout);
   }
  fputc('\n',stdout);
//
//
  fprintf(stdout,"%s\n",
   "         BOUNDED SUM 'OR' OPERATOR");
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
       d1=(f1+f2);
       d1=min(1,d1);
       fprintf(stdout,"%6.4f ",d1);
      }
     fputc('\n',stdout);
   }
  fputc('\n',stdout);
 }
