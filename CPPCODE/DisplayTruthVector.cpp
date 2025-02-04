/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtfzdtv.cpp  Earl Cox  04/01/93 Display Fuzzy Truth Vector  |
| In cases where the FzyExamineSet is insufficient, this      |
| routine can be used to dump the entire truth membership     |
| vector to the model log.                                    |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <FuzzysetDescriptor.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
void FzyDisplayMemVector(FuzzysetDescriptor *FuzzysetDescriptorptr,float AlfaCut,int *statusPtr)
  {
   int        i;
   double     lo,hi;
   FILE      *mdlout;

   *statusPtr=0;
   mdlout=MtsGetSystemFile(SYSMODFILE);
   lo=FuzzysetDescriptorptr->FuzzysetDescriptordomain[0];
   hi=FuzzysetDescriptorptr->FuzzysetDescriptordomain[1];
//--find the underlying support set. This is the non-zero part
//--of the fuzzy set domain.
//--output the fuzzy possibility density report. We print
//--the fuzzy set description and the domain/plateau values.
   fputc('\f',mdlout);
   fputc('\n',mdlout);
   fprintf(mdlout,"%s%s\n","FuzzySet:    ",FuzzysetDescriptorptr->FuzzysetDescriptorid);
   fprintf(mdlout,"%s%s\n","Description: ",FuzzysetDescriptorptr->FuzzysetDescriptordesc);
   fprintf(mdlout,"%s%10.2f%s%10.2f\n","Domain     : ",lo," to ",hi);
   fputc('\n',mdlout);
   for(i=0;i<VECMAX;i++)
     if(FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]>=AlfaCut)
       fprintf(mdlout,"%4d%s%10.6f\n",i,". ",FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]);
   fputc('\n',mdlout);
   if(AlfaCut!=0)
     fprintf(mdlout,"%s%6.2f\n","    Display AlphaCut:  ",AlfaCut);
   fputc('\n',mdlout);
   return;
  }

