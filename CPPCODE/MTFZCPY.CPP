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
#include   <mtypes.hpp>
#include   <fuzzy.hpp>
#include <fdb.hpp>
#include <mtsptype.hpp>
void FzyCopySet(const FDB* inFDBptr,FDB* outFDBptr,int *statusPtr)
  {
    int i;
    FILE *mdllog;

    *statusPtr=0;
    mdllog=MtsGetSystemFile(SYSMODFILE);    // Get default model log file
    strcpy(outFDBptr->FDBid,inFDBptr->FDBid);
    strcpy(outFDBptr->FDBdesc,inFDBptr->FDBdesc);
    outFDBptr->FDBgentype     =inFDBptr->FDBgentype;
    outFDBptr->FDBempty       =inFDBptr->FDBempty;
    outFDBptr->FDBorder       =inFDBptr->FDBorder;
    outFDBptr->FDBdomain[0]   =inFDBptr->FDBdomain[0];
    outFDBptr->FDBdomain[1]   =inFDBptr->FDBdomain[1];
    outFDBptr->FDBalfacut     =inFDBptr->FDBalfacut;
    for(i=0;i<PARMMAX;i++) outFDBptr->FDBparms[i] =inFDBptr->FDBparms[i];
    for(i=0;i<VECMAX; i++) outFDBptr->FDBvector[i]=inFDBptr->FDBvector[i];
    outFDBptr->FDBnext=NULL;
    fprintf(mdllog,"%s%s%s%s%s\n",
     "OK. Fuzzy set '",inFDBptr->FDBid,
       "' copied into Fuzzy set '",outFDBptr->FDBid,"'");
   return;
  }
