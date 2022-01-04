/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzfsc.cpp  Earl Cox  04/01/93 Fuzzify a Scalar Number     |
| This function takes a number and converts it to a fuzzy     |
| set.                                                        |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stddef.h>
#include <string.h>
#include <FuzzysetDescriptor.hpp>
#include   <fuzzy.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
FuzzysetDescriptor *FzyFuzzyScalar(
   char *Varid,double Scalar,int SetType,int *statusPtr)
 {
   FuzzysetDescriptor    *FuzzysetDescriptorptr,*nullFuzzysetDescriptor=NULL;
   char   *PgmId="mtfzfsc";
   char   *option;
   int     k;
   double  Hi,Lo,Range,Width,Center,Left,Right,Inflexpoint;

   *statusPtr=0;
//
//--Search through the variable dictionary to see if a domain
//--exists for the current number. If not, the find domain
//--function will generate a pseudo-domain for our use.
   MdlFindFzyDomain(Varid,&Hi,&Lo,statusPtr);
//
//--Allocate a new fuzzy set descriptor and complete it with
//--the the information from the variable and domain/
   if(!(FuzzysetDescriptorptr=new FuzzysetDescriptor))
     {
      *statusPtr=1;
      MtsSendError(2,PgmId,Varid);
      return(nullFuzzysetDescriptor);
     }
   FzyInitFuzzysetDescriptor(FuzzysetDescriptorptr);
   strcpy(FuzzysetDescriptorptr->FuzzysetDescriptorid,Varid);
   FuzzysetDescriptorptr->FuzzysetDescriptordomain[0]=Lo;
   FuzzysetDescriptorptr->FuzzysetDescriptordomain[1]=Hi;
//
//--Calculate the basic curve parameters.
   Range=Hi-Lo;
   k=(int)(1.00+((Scalar-Lo)/Range)*VECMAX);
   Width=(Hi-Lo)/2;
   Center=Lo+Width;
   Inflexpoint=Width;
//
//--Create the fuzzified scalar based on the  type of
//--option we have specified.
   switch(SetType)
    {
     case FZYPOINT:
       FuzzysetDescriptorptr->FuzzysetDescriptorvector[k]=1.0;
       return(FuzzysetDescriptorptr);
     case FZYPI:
       FzyPiCurve(FuzzysetDescriptorptr,Center,Width,statusPtr);
       return(FuzzysetDescriptorptr);
     case FZYBETA:
       FzyBetaCurve(FuzzysetDescriptorptr,Center,Inflexpoint,statusPtr);
       return(FuzzysetDescriptorptr);
     case FZYTRIANGLE:
       Left=Center-Width;
       Right=Center+Width;
       FzyTriangleCurve(FuzzysetDescriptorptr,Left,Center,Right,statusPtr);
       return(FuzzysetDescriptorptr);
     default:
       *statusPtr=3;
       option=MtsFormatInt(SetType);
       MtsSendError(8,PgmId,option);
       return(nullFuzzysetDescriptor);
    }
 }
