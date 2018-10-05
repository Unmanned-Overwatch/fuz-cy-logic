/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtfmdrl.cpp  Earl Cox  04/01/93 Display a Rule in Array     |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <mtsptype.hpp>
void FzyDisplayRule(
  char **Rules,
  int RuleNo,int RuleIDX[],int RuleSLN[],int FileMedium,int *statusPtr)
 {
  int    i,j,k;
  FILE  *mdlout;

  *statusPtr=0;
  if((mdlout=MtsGetSystemFile(FileMedium))==NULL)
    {
     *statusPtr=9;
     return;
    }
  j=RuleIDX[RuleNo];
  k=RuleSLN[RuleNo];
  i=0;
  for(i=0;i<k;i++,j++)  fprintf(mdlout,"%s\n",Rules[j]);
  return;
 }
