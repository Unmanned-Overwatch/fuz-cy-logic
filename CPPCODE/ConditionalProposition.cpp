/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtfzcfp.cpp   Earl Cox  04/01/93 Conditional Fuzzy Prop.    |
| This procedure handles the conditional (if-then) fuzzy      |
| proposition.  If the target fuzzy set is empty, then we     |
| just copy over the fuzzy set, otherwise we take the maximum |
| of the two sets across the domain.                          |
*-------------------------------------------------------------*/
#include <FuzzysetDescriptor.hpp>
#include <XFZYctl.hpp>
#include <XSYSctl.hpp>
#include   <fuzzy.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
void FzyCondProposition(
  FuzzysetDescriptor *inFuzzysetDescriptorptr,FSV *FSVptr,
      int CorrMethod,float PredTruth,int *statusPtr)
 {
   FuzzysetDescriptor   *outFuzzysetDescriptorptr;
   char   wrkBuff[80];
   int    i,thisCorrMethod,thisImplMethod;
   float  memvector[VECMAX];

   *statusPtr=0;
   if(PredTruth<XSYSctl.XSYSalfacut)
     {
      sprintf(wrkBuff,"%s%6.4f",
       "Rule fails. Premise truth is below alpha threshold: ",
         XSYSctl.XSYSalfacut);
      MtsWritetoLog(SYSMODFILE,wrkBuff,statusPtr);
      *statusPtr=RULEBELOWALFA;
      return;
     }
//
//--Apply any correlation restriction to the incoming fuzzy set.
//--we make a copy of the method and then change it if necessary.
//--If CORRNONE is specified we simply drop through without any
//--restriction on the incoming fuzzy set.
   FzyCopyVector(memvector,inFuzzysetDescriptorptr->FuzzysetDescriptorvector,VECMAX);
   thisCorrMethod=CorrMethod;
   if(CorrMethod==CORRDEFAULT)
       thisCorrMethod=FSVptr->FzySVimplMethod;
   if(thisCorrMethod==CORRMINIMUM)
      FzyCorrMinimum(memvector,PredTruth,statusPtr);
   if(thisCorrMethod==CORRPRODUCT)
      FzyCorrProduct(memvector,PredTruth,statusPtr);
   if(thisCorrMethod==CORRAVERAGE)
      FzyCorrAverage(memvector,PredTruth,statusPtr);
//
//--Now find the solution fuzzy set and apply the conditional
//--proposition method. This is equivalent to ORing the two
//--fuzzy regions.
   thisImplMethod=FSVptr->FzySVimplMethod;
   outFuzzysetDescriptorptr=FSVptr->FzySVFuzzysetDescriptorptr;
   if(outFuzzysetDescriptorptr->FuzzysetDescriptorempty)
     {
      FzyCopyVector(outFuzzysetDescriptorptr->FuzzysetDescriptorvector,memvector,VECMAX);
      outFuzzysetDescriptorptr->FuzzysetDescriptorempty=FALSE;
      return;
     }
    else
     {
      switch(thisImplMethod)
       {
        case MINMAX:
          for(i=0;i<VECMAX;i++)
           outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=
             max(outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i],memvector[i]);
          break;
        case BOUNDEDADD:
          for(i=0;i<VECMAX;i++)
           outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=
             min(1,outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]+memvector[i]);
          break;
        case BOUNDEDMEAN:
          for(i=0;i<VECMAX;i++)
           outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=
             min(1,(outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]+memvector[i])/2);
          break;
        case PRODUCTSUM:
          for(i=0;i<VECMAX;i++)
           outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=
             max(0,outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]*memvector[i]);
          break;
        default:
          sprintf(wrkBuff,"%s%4d",
           "Unknown Implication Function: ",thisImplMethod);
          MtsWritetoLog(SYSMODFILE,wrkBuff,statusPtr);
          *statusPtr=5;
          return;
       }
     }
//
//--Now update the possibility density arrays so that if we are
//--using the preponderance of evidence technique the statistics
//--will be available.
   FSVptr->FzySVupdcnt++;
   for(i=0;i<VECMAX;i++)
    if(outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]>0) FSVptr->FzySVcntarray[i]++;
   return;
 }
