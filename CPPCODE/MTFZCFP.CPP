/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtfzcfp.cpp   Earl Cox  04/01/93 Conditional Fuzzy Prop.    |
| This procedure handles the conditional (if-then) fuzzy      |
| proposition.  If the target fuzzy set is empty, then we     |
| just copy over the fuzzy set, otherwise we take the maximum |
| of the two sets across the domain.                          |
*-------------------------------------------------------------*/
#include "FDB.hpp"
#include "XFZYctl.hpp"
#include "XSYSctl.hpp"
#include "fuzzy.hpp"
#include "mtypes.hpp"
#include "mtsptype.hpp"
void FzyCondProposition(
  FDB *inFDBptr,FSV *FSVptr,
      int CorrMethod,float PredTruth,int *statusPtr)
 {
   FDB   *outFDBptr;
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
   FzyCopyVector(memvector,inFDBptr->FDBvector,VECMAX);
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
   outFDBptr=FSVptr->FzySVfdbptr;
   if(outFDBptr->FDBempty)
     {
      FzyCopyVector(outFDBptr->FDBvector,memvector,VECMAX);
      outFDBptr->FDBempty=FALSE;
      return;
     }
    else
     {
      switch(thisImplMethod)
       {
        case MINMAX:
          for(i=0;i<VECMAX;i++)
           outFDBptr->FDBvector[i]=
             max(outFDBptr->FDBvector[i],memvector[i]);
          break;
        case BOUNDEDADD:
          for(i=0;i<VECMAX;i++)
           outFDBptr->FDBvector[i]=
             min(1,outFDBptr->FDBvector[i]+memvector[i]);
          break;
        case BOUNDEDMEAN:
          for(i=0;i<VECMAX;i++)
           outFDBptr->FDBvector[i]=
             min(1,(outFDBptr->FDBvector[i]+memvector[i])/2);
          break;
        case PRODUCTSUM:
          for(i=0;i<VECMAX;i++)
           outFDBptr->FDBvector[i]=
             max(0,outFDBptr->FDBvector[i]*memvector[i]);
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
    if(outFDBptr->FDBvector[i]>0) FSVptr->FzySVcntarray[i]++;
   return;
 }
