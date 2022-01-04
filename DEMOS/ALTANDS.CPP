/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| altands.cpp  Earl Cox  04/01/93 The Algebraic AND operators |
| This program produces the MxM truth tables for various      |
| types of non-Zadeh AND operators.                           |
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
void main(void)
 {
  int    i,j;
  int    Classlmt=12;
  int     TruthMax=5;
  double  f1,f2,f3;
  double  TruthValue[5]={0.0,0.25,0.50,0.75,1.0};
  double  d1;

//
//--The Mean operators
//
  fprintf(stdout,"%s\n",
   "         MEAN (AVERAGE) FUZZY 'AND' OPERATOR");
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
       d1=(f1+f2)/2;
       fprintf(stdout,"%6.4f ",d1);
      }
     fputc('\n',stdout);
   }
  fputc('\n',stdout);
//
//
//
//--The Mean operators
//
  fprintf(stdout,"%s\n",
   "         VERY MEAN (AVERAGE) FUZZY 'AND' OPERATOR");
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
       d1=(f1+f2)/2;
       d1=pow(d1,2);
       fprintf(stdout,"%6.4f ",d1);
      }
     fputc('\n',stdout);
   }
  fputc('\n',stdout);
//
//
  fprintf(stdout,"%s\n",
   "         SOMEWHAT (AVERAGE) FUZZY 'AND' OPERATOR");
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
       d1=(f1+f2)/2;
       d1=pow(d1,.5);
       fprintf(stdout,"%6.4f ",d1);
      }
     fputc('\n',stdout);
   }
  fputc('\n',stdout);
//
//
  fprintf(stdout,"%s\n",
   "         PRODUCT FUZZY 'AND' OPERATOR");
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
       d1=(f1*f2);
       fprintf(stdout,"%6.4f ",d1);
      }
     fputc('\n',stdout);
   }
  fputc('\n',stdout);
//
//
  fprintf(stdout,"%s\n",
   "         BOUNDED DIFFERENCE 'AND' OPERATOR");
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
       d1=(f1+f2)-1;
       d1=max(0,d1);
       fprintf(stdout,"%6.4f ",d1);
      }
     fputc('\n',stdout);
   }
  fputc('\n',stdout);
 }
