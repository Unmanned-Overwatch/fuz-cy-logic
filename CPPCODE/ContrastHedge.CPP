/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtfzchd.cpp   Earl Cox  04/01/93 Apply Contrast Hedge.      |
| This function supports the general contrast intensification |
| and dilution hedge                                          |
*-------------------------------------------------------------*/
#include <math.h>
#include <stdio.h>
#include <string.h>
double max(double,double);
#include <FuzzysetDescriptor.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
void Complete_hedge(FuzzysetDescriptor*,FuzzysetDescriptor*,double);
//
void FzyContrastHedge(
    FuzzysetDescriptor* inFuzzysetDescriptorptr,FuzzysetDescriptor* outFuzzysetDescriptorptr,double HdgCoeff,int *statusPtr)
  {
   int    i;
   double  x,hv;

   *statusPtr=0;
   FzyCopySet(inFuzzysetDescriptorptr,outFuzzysetDescriptorptr,statusPtr);
   x=.5;
   for(i=0;i<VECMAX;++i)
     if(inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i] >= x)
       {
        hv=(double)inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i];
        hv=HdgCoeff*pow(hv,HdgCoeff);
        outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=(float)hv;
       }
     else
       {
        hv=(double)inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i];
        hv=(1-(HdgCoeff*(pow(fabs(1-hv),HdgCoeff))));
        outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=(float)hv;
       }
   Complete_hedge(inFuzzysetDescriptorptr,outFuzzysetDescriptorptr,HdgCoeff);
   return;
  }

/*------------------------------------------------------------*
| The Complete_hedge routine (1) applies the current alpha-cut|
| to the hedge, (2) initiates any trace output to the model   |
| log, and (3) plots the currently hedged fuzzyset (if the    |
| active plot window state has been specified)                |
*-------------------------------------------------------------*/
 void Complete_hedge(FuzzysetDescriptor *inFuzzysetDescriptorptr,FuzzysetDescriptor *outFuzzysetDescriptorptr,double HdgCoeff)
    {
     int     status;
     char    NameBuf[DESCLEN+1];
     char    wrkBuff[128];

     sprintf(wrkBuff,"%s%s%s%s%s",
      "Contrast Hedge with Coeff: '",HdgCoeff,"' applied to Fuzzy Set \"",
        inFuzzysetDescriptorptr->FuzzysetDescriptorid,"\"");
     MtsWritetoLog(SYSMODFILE,wrkBuff,&status);
    //--Now update the name and the description of the new
    //--hedged fuzzy set.
     strcpy(outFuzzysetDescriptorptr->FuzzysetDescriptorid,inFuzzysetDescriptorptr->FuzzysetDescriptorid);
     strcpy(NameBuf,"Contrast");
     strcat(NameBuf," ");
     strcat(NameBuf,inFuzzysetDescriptorptr->FuzzysetDescriptorid);
     strcpy(outFuzzysetDescriptorptr->FuzzysetDescriptordesc,NameBuf);
     return;
    }
