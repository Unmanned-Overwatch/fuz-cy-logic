/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtfzcpy.cpp   Earl Cox  04/01/93 Copy a FuzzySet            |
| This procedures copies the contents of one fuzzy set into   |
| another fuzzy set. This is a way of making a copy of a set  |
| (prior to hedging, as an example)                           |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include   <SystemTypes.hpp>
#include   <fuzzy.hpp>
#include <FuzzysetDescriptor.hpp>
#include <SystemPrototypes.hpp>
void FzyCopySet(const FuzzysetDescriptor* inFuzzysetDescriptorptr,FuzzysetDescriptor* outFuzzysetDescriptorptr,int *statusPtr)
  {
    int i;
    FILE *mdllog;

    *statusPtr=0;
    mdllog=MtsGetSystemFile(SYSMODFILE);    // Get default model log file
    strcpy(outFuzzysetDescriptorptr->FuzzysetDescriptorid,inFuzzysetDescriptorptr->FuzzysetDescriptorid);
    strcpy(outFuzzysetDescriptorptr->FuzzysetDescriptordesc,inFuzzysetDescriptorptr->FuzzysetDescriptordesc);
    outFuzzysetDescriptorptr->FuzzysetDescriptorgentype     =inFuzzysetDescriptorptr->FuzzysetDescriptorgentype;
    outFuzzysetDescriptorptr->FuzzysetDescriptorempty       =inFuzzysetDescriptorptr->FuzzysetDescriptorempty;
    outFuzzysetDescriptorptr->FuzzysetDescriptororder       =inFuzzysetDescriptorptr->FuzzysetDescriptororder;
    outFuzzysetDescriptorptr->FuzzysetDescriptordomain[0]   =inFuzzysetDescriptorptr->FuzzysetDescriptordomain[0];
    outFuzzysetDescriptorptr->FuzzysetDescriptordomain[1]   =inFuzzysetDescriptorptr->FuzzysetDescriptordomain[1];
    outFuzzysetDescriptorptr->FuzzysetDescriptoralfacut     =inFuzzysetDescriptorptr->FuzzysetDescriptoralfacut;
    for(i=0;i<PARMMAX;i++) outFuzzysetDescriptorptr->FuzzysetDescriptorparms[i] =inFuzzysetDescriptorptr->FuzzysetDescriptorparms[i];
    for(i=0;i<VECMAX; i++) outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i];
    outFuzzysetDescriptorptr->FuzzysetDescriptornext=NULL;
    fprintf(mdllog,"%s%s%s%s%s\n",
     "OK. Fuzzy set '",inFuzzysetDescriptorptr->FuzzysetDescriptorid,
       "' copied into Fuzzy set '",outFuzzysetDescriptorptr->FuzzysetDescriptorid,"'");
   return;
  }
