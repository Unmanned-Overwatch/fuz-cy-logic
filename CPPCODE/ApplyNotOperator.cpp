/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtfzapn.cpp   Earl Cox  04/01/93 Apply NOT operator         |
| Although the standard Zadeh NOT is available through the    |
| hedge manager (FzyApplyHedge), this function supports       |
| various families of NOT operators. Note that this function  |
| is destructive--it overwrites the incoming fuzzy set.       |
*-------------------------------------------------------------*/
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <FuzzysetDescriptor.hpp>
#include   <fuzzy.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
void CompleteNot(char*,FuzzysetDescriptor*);
void FzyApplyNOT(
   int NotClass,float NotWeight,FuzzysetDescriptor *FuzzysetDescriptorptr,int *statusPtr)
  {
   char       *PgmId="mtfzapn";
   int        i;
   int        decimals=3;
   double     Power,InversePower;
   double     Pi=3.14159;
   float      thisMV;
   const int  MaxWeight = 128;

   *statusPtr=0;
   switch(NotClass)
    {
     case ZADEHNOT:
      for(i=0;i<VECMAX;i++) FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=1-FuzzysetDescriptorptr->FuzzysetDescriptorvector[i];
      CompleteNot("ZADEH",FuzzysetDescriptorptr);
      return;
     case YAGERNOT:
      if(NotWeight<1||NotWeight>MaxWeight)
        {
         *statusPtr=1;
         MtsSendError(51,PgmId,MtsFormatFlt(NotWeight,decimals));
         return;
        }
      Power=NotWeight;
      InversePower=(1/Power);
      for(i=0;i<VECMAX;i++)
          FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=
           (float)(pow(1-pow(FuzzysetDescriptorptr->FuzzysetDescriptorvector[i],Power),InversePower));
      CompleteNot("YAGER",FuzzysetDescriptorptr);
      return;
     case SUGENONOT:
      if(NotWeight<-1||NotWeight>MaxWeight)
        {
         *statusPtr=3;
         MtsSendError(52,PgmId,MtsFormatFlt(NotWeight,decimals));
         return;
        }
      for(i=0;i<VECMAX;i++)
         {
          thisMV=FuzzysetDescriptorptr->FuzzysetDescriptorvector[i];
          FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=(1-thisMV)/(1+(NotWeight*thisMV));
         }
      CompleteNot("SUGENO",FuzzysetDescriptorptr);
      return;
     case THRESHOLDNOT:
      if(NotWeight<0||NotWeight>VECMAX)
        {
         *statusPtr=5;
         MtsSendError(53,PgmId,MtsFormatFlt(NotWeight,decimals));
         return;
        }
      for(i=0;i<VECMAX;i++)
         {
          thisMV=FuzzysetDescriptorptr->FuzzysetDescriptorvector[i];
          if(thisMV<=NotWeight)
              FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=1;
             else
              FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=0;
         }
      CompleteNot("THRESHOLD",FuzzysetDescriptorptr);
      return;
     case COSINENOT:
      for(i=0;i<VECMAX;i++)
         {
          thisMV=(float)(FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]);
          FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=(float)(.5*(1+cos(Pi*thisMV)));
         }
      CompleteNot("COSINE",FuzzysetDescriptorptr);
      return;
     default:
      *statusPtr=7;
      MtsSendError(54,PgmId,MtsFormatInt(NotClass));
      return;
    }
  }
//--Update the fuzzy set to indicate the the NOT hedge has been
//--applied. The NOT is a fuzzy operator buttreated like a hedge.
  void CompleteNot(char *TypeofNot,FuzzysetDescriptor *FuzzysetDescriptorptr)
    {
     int        status;
     char       NameBuf[DESCLEN+1];
     char       wrkBuff[80];

     sprintf(wrkBuff,"%s%s%s%s%s",
      "Hedge '",TypeofNot,"' NOT applied to Fuzzy Set \"",
        FuzzysetDescriptorptr->FuzzysetDescriptorid,"\"");
     MtsWritetoLog(SYSMODFILE,wrkBuff,&status);
    //--Now update the name and the description of the new
    //--hedged fuzzy set.
     strcpy(NameBuf,TypeofNot);
     strcat(NameBuf," NOT ");
     strcat(NameBuf,FuzzysetDescriptorptr->FuzzysetDescriptorid);
     strcpy(FuzzysetDescriptorptr->FuzzysetDescriptordesc,NameBuf);
     return;
    }
