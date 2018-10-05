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
#include "FDB.hpp"
#include "mtypes.hpp"
#include "mtsptype.hpp"
void Complete_hedge(FDB*,FDB*,double);
//
void FzyContrastHedge(
    FDB* inFDBptr,FDB* outFDBptr,double HdgCoeff,int *statusPtr)
  {
   int    i;
   double  x,hv;

   *statusPtr=0;
   FzyCopySet(inFDBptr,outFDBptr,statusPtr);
   x=.5;
   for(i=0;i<VECMAX;++i)
     if(inFDBptr->FDBvector[i] >= x)
       {
        hv=(double)inFDBptr->FDBvector[i];
        hv=HdgCoeff*pow(hv,HdgCoeff);
        outFDBptr->FDBvector[i]=(float)hv;
       }
     else
       {
        hv=(double)inFDBptr->FDBvector[i];
        hv=(1-(HdgCoeff*(pow(fabs(1-hv),HdgCoeff))));
        outFDBptr->FDBvector[i]=(float)hv;
       }
   Complete_hedge(inFDBptr,outFDBptr,HdgCoeff);
   return;
  }

/*------------------------------------------------------------*
| The Complete_hedge routine (1) applies the current alpha-cut|
| to the hedge, (2) initiates any trace output to the model   |
| log, and (3) plots the currently hedged fuzzyset (if the    |
| active plot window state has been specified)                |
*-------------------------------------------------------------*/
 void Complete_hedge(FDB *inFDBptr,FDB *outFDBptr,double HdgCoeff)
    {
     int     status;
     char    NameBuf[DESCLEN+1];
     char    wrkBuff[128];

     sprintf(wrkBuff,"%s%s%s%s%s",
      "Contrast Hedge with Coeff: '",HdgCoeff,"' applied to Fuzzy Set \"",
        inFDBptr->FDBid,"\"");
     MtsWritetoLog(SYSMODFILE,wrkBuff,&status);
    //--Now update the name and the description of the new
    //--hedged fuzzy set.
     strcpy(outFDBptr->FDBid,inFDBptr->FDBid);
     strcpy(NameBuf,"Contrast");
     strcat(NameBuf," ");
     strcat(NameBuf,inFDBptr->FDBid);
     strcpy(outFDBptr->FDBdesc,NameBuf);
     return;
    }
