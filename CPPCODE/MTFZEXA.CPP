/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzexa.cpp   Earl Cox  04/01/93 Examine fuzzy truth table  |
| This procedure builds an MxN matrix showing the distribution|
| of values acoss the fuzzy set. we use this to look at how   |
| the fuzzy set is population in its possibility distribution |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include "FDB.hpp"
#include "mtypes.hpp"
#include "mtsptype.hpp"
void FzyExamineSet(FDB *FDBptr,int *statusPtr)
  {
   int        L,M,i,k,n,cellno,N1,N2;
   float      scale;
   double     lo,
              hi,
              xo,
              XL,
              XM,
              range,
              Pedge1,
              Pedge2,
              LeftDomVal,
              RightDomVal;
   double     Scalars[2];
   int        Truth[2];
   FILE      *mdlout;

   *statusPtr=0;
   mdlout=MtsGetSystemFile(SYSMODFILE);
//--startup. We zero out the plateau arrays, get the fuzzy set
//--domains (and cuculate the range), then we find out what scaling
//--factor, if any, we want to use.
   for(i=0;i<2;i++) Scalars[i]=0.0;
   for(i=0;i<2;i++) Truth[i]=0;
   lo=FDBptr->FDBdomain[0];
   hi=FDBptr->FDBdomain[1];
   range=hi-lo;
   scale=FzyAutoScale(hi,lo);
   xo=lo/scale;
//--find the underlying support set. This is the non-zero part
//--of the fuzzy set domain.
   FzySupportSet(FDBptr,Scalars,Truth,statusPtr);
   if(*statusPtr!=0) return;
   Pedge1=Truth[0];
   Pedge2=Truth[1];
//--output the fuzzy possibility density report. We print
//--the fuzzy set description and the domain/plateau values.
   fputc('\f',mdlout);
   fputc('\n',mdlout);
   fprintf(mdlout,"%s%s\n","FuzzySet:    ",FDBptr->FDBid);
   fprintf(mdlout,"%s%s\n","Description: ",FDBptr->FDBdesc);
   fprintf(mdlout,"%s%10.2f%s%10.2f\n",
      "Domain     : ",lo," to ",hi);
   fprintf(mdlout,"%s%10.2f%s%10.2f\n",
      "Plateau    : ",Pedge1," to ",Pedge2);
   fputc('\n',mdlout);
   fprintf(mdlout,"%s",
    " % Value                    Truth                         ");
   fprintf(mdlout,"%s\n","  Value  %");
   if(FDBptr->FDBvector[0]!=0)
      fprintf(mdlout,"%s%6.2f%5.2f\n"," 0",xo,FDBptr->FDBvector[0]);
    else
      fprintf(mdlout,"%s%6.2f%s\n"," 0",xo," ");
   for(k=0;k<10;k++)
     {
      L=1+k*10;           // move to the L-th percent of membership
      M=L+9;              // make bracet the next 10% up
      N1=L+1;
      N2=M+1;
      LeftDomVal =VECMAX*(((float)L)/100);
      RightDomVal=VECMAX*(((float)M)/100);
      XL=(lo+LeftDomVal/VECMAX*range)/scale;
      XM=(lo+RightDomVal/VECMAX*range)/scale;
      fprintf(mdlout,"%2.0d%6.2f",L,XL);
      cellno=(int)(VECMAX*((float)L/100));
      for(n=N1;n<N2+1;n++)
       {
         if(n>=VECMAX) {fputs("ABORT!!",mdlout); return;}
         if(FDBptr->FDBvector[cellno]!=0)
             fprintf(mdlout,"%5.2f",FDBptr->FDBvector[cellno]);
           else
             fprintf(mdlout,"%s","     ");
        ++cellno;
       }
      fprintf(mdlout,"%6.2f%4.0d\n",XM,M);
     }
   if(FDBptr->FDBalfacut!=0)
     fprintf(mdlout,"%s%6.2f\n","AlphaCut:  ",FDBptr->FDBalfacut);
   if(scale==1) return;
   fputc('\n',mdlout);
   fprintf(mdlout,"%s%6.2f%s\n","Scaling:   ",scale,"(x)");
   return;
  }
