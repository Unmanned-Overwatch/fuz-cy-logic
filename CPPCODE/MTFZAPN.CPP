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
#include "FDB.hpp"
#include "fuzzy.hpp"
#include "mtypes.hpp"
#include "mtsptype.hpp"
void CompleteNot(char*,FDB*);
void FzyApplyNOT(
   int NotClass,float NotWeight,FDB *FDBptr,int *statusPtr)
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
      for(i=0;i<VECMAX;i++) FDBptr->FDBvector[i]=1-FDBptr->FDBvector[i];
      CompleteNot("ZADEH",FDBptr);
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
          FDBptr->FDBvector[i]=
           (float)(pow(1-pow(FDBptr->FDBvector[i],Power),InversePower));
      CompleteNot("YAGER",FDBptr);
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
          thisMV=FDBptr->FDBvector[i];
          FDBptr->FDBvector[i]=(1-thisMV)/(1+(NotWeight*thisMV));
         }
      CompleteNot("SUGENO",FDBptr);
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
          thisMV=FDBptr->FDBvector[i];
          if(thisMV<=NotWeight)
              FDBptr->FDBvector[i]=1;
             else
              FDBptr->FDBvector[i]=0;
         }
      CompleteNot("THRESHOLD",FDBptr);
      return;
     case COSINENOT:
      for(i=0;i<VECMAX;i++)
         {
          thisMV=(float)(FDBptr->FDBvector[i]);
          FDBptr->FDBvector[i]=(float)(.5*(1+cos(Pi*thisMV)));
         }
      CompleteNot("COSINE",FDBptr);
      return;
     default:
      *statusPtr=7;
      MtsSendError(54,PgmId,MtsFormatInt(NotClass));
      return;
    }
  }
//--Update the fuzzy set to indicate the the NOT hedge has been
//--applied. The NOT is a fuzzy operator buttreated like a hedge.
  void CompleteNot(char *TypeofNot,FDB *FDBptr)
    {
     int        status;
     char       NameBuf[DESCLEN+1];
     char       wrkBuff[80];

     sprintf(wrkBuff,"%s%s%s%s%s",
      "Hedge '",TypeofNot,"' NOT applied to Fuzzy Set \"",
        FDBptr->FDBid,"\"");
     MtsWritetoLog(SYSMODFILE,wrkBuff,&status);
    //--Now update the name and the description of the new
    //--hedged fuzzy set.
     strcpy(NameBuf,TypeofNot);
     strcat(NameBuf," NOT ");
     strcat(NameBuf,FDBptr->FDBid);
     strcpy(FDBptr->FDBdesc,NameBuf);
     return;
    }
