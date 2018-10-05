#include <stdio.h>
#include <stdlib.h>
#include "mtsptype.hpp"
void main(void)
 {
  char    number[16],prec[8];
  double  Num,rndNumber;
  int     n,Prc,status;

  n=0;
 looptop:
  n++;
  if(n>10) return;
  fflush(stdin);
  printf("Enter a number     : ");
  gets(number);
  Num=atof(number);
  if(Num==0) return;
  fflush(stdin);
  printf("Enter the precision: ");
  gets(prec);
  Prc=atoi(prec);
  rndNumber=MtsRound(Num,Prc,&status);
  printf("%s%12.7f\n","Number       :",Num);
  printf("%s%12d\n",  "Precison     :",Prc);
  printf("%s%12.7f\n","rndNumber    :",rndNumber);
  goto looptop;
 }
