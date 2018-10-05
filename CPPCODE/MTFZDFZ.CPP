/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtfzdfz.cpp   Earl Cox  04/01/93 Defuzzification Methods    |
| This procedure takes a pointer to the solution variable's   |
| fuzzy region and returns a double pecision floating point   |
| scalar that is the expected value from the fuzzy set region.|
/*-------------------W  A  R  N  I  N  G  S-------------------*
| (1) The procedure FzyFindPlateau will modify the fuzzy set  |
|  by setting all truth values below the maximum to zero (0). |
|                                                             |
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <fdb.hpp>
#include   <fuzzy.hpp>
#include   <mtypes.hpp>
#include <mtsptype.hpp>
static char  wrkBuff[128];
static char *DefuzzNames[]=
 {
  "Centroid",
  "Maximum Plateau",
  "Maximum Height",
  "Average Support Set",
  "Best Evidence",
  "Least Entropy",
  "Near Edge",
  "  Edge"
 };
void CompleteDefuzz(char*,double,float);
double FzyDefuzzify(
     FDB* FDBptr,const int DefuzzMethod,float *Grade,int *statusPtr)
   {
    int        i,j,k,n,tvpos,EdgeCnt;
    int        Edges[2];
    float      x,y,tval;
    double     Scalar,SumofScalars;
    const int  Left = 0;
    const int  Right = 1;
    char       *PgmId="mtfzdfz";

    *statusPtr=0;
    EdgeCnt=0;

  /* Apply alpha-cut pruning to the solution fuzzy set */
    FzyApplyAlfa(FDBptr,FDBptr->FDBalfacut,STRONG);
  /*
     Check to make sure that, either originally or after
     the aspplication of the alfa cut, the solution fuzzy
     set is not empty (max value == 0)
  */
    if(FzyGetHeight(FDBptr)==0)
      {
       *Grade=0.0;
       Scalar=0.0;
       sprintf(wrkBuff,"%s%s%s%s%s%s",
        "Cannot Apply \"",DefuzzNames[DefuzzMethod-1],
          "\" Defuzzification--",
        "'",FDBptr->FDBid,"' is empty. [height==0].");
       MtsWritetoLog(SYSMODFILE,wrkBuff,statusPtr);
       *statusPtr=99;
       return(Scalar);
      }

    switch(DefuzzMethod)
     {
        case BESTEVIDENCE:
         FzyIsolatePDR(FDBptr);
        case CENTROID:
         x=0.0;
         y=0.0;
         for(i=0;i<VECMAX;i++)
          {
            x=x+FDBptr->FDBvector[i]*(float)i;
            y=y+FDBptr->FDBvector[i];
          }
         tvpos=(int)(x/y);
         if(y==0)
           {
            *Grade=0.0;
            Scalar=0.0;
            sprintf(wrkBuff,"%s%s%s",
             "CENTROID Failed. '",FDBptr->FDBid,"' is empty. [height==0].");
            MtsWritetoLog(SYSMODFILE,wrkBuff,statusPtr);
            *statusPtr=99;
            return(Scalar);
           }
         Scalar=FzyGetScalar(FDBptr,tvpos,statusPtr);
         *Grade=FDBptr->FDBvector[tvpos];
         CompleteDefuzz("CENTROID",Scalar,*Grade);
         return(Scalar);

        case MAXPLATEAU:
         FzyFindPlateau(FDBptr,Edges,&EdgeCnt,statusPtr);
         if(EdgeCnt==2)
             tvpos=(Edges[Left]+Edges[Right])/2;
            else
             {
              tvpos=Edges[Left];
              if(Edges[Left]==0) tvpos=Edges[Right];
              if(Edges[Right]>=VECMAX) tvpos=Edges[Left];
             }
         Scalar=FzyGetScalar(FDBptr,tvpos,statusPtr);
         *Grade=FDBptr->FDBvector[tvpos];
         CompleteDefuzz("MAXPLATEAU",Scalar,*Grade);
         sprintf(wrkBuff,"%s%s%2d%s",
           FDBptr->FDBid," is a ",EdgeCnt," edged surface.");
         MtsWritetoLog(SYSMODFILE,wrkBuff,statusPtr);
         return(Scalar);

        case MAXIMUM:
//        This maximum is the highest point in the fuzzy set.
//        if this is a plateau, then we look along the surface
//        until we find its end and take the midpoint of the
//        plateau.
         x=FDBptr->FDBvector[0];
         k=0;
         for(i=0;i<VECMAX;i++)
          if(FDBptr->FDBvector[i]>x)
            {
             x=FDBptr->FDBvector[i];
             k=i;
            }
         for(j=k+1;j<VECMAX;j++)
           if(FDBptr->FDBvector[j]!=x) break;
         tvpos=(int)(((float)j-(float)k)/2);
         if(tvpos==0) tvpos=k;
         Scalar=FzyGetScalar(FDBptr,tvpos,statusPtr);
         *Grade=FDBptr->FDBvector[tvpos];
         CompleteDefuzz("MAXIMUM",Scalar,*Grade);
         return(Scalar);

        case AVGSUPPORT:
         tval=0;
         SumofScalars=0;
         n=0;
         for(i=0;i<VECMAX;i++)
          {
            if(FDBptr->FDBvector[i]>0)
              {
               n++;
               tval=tval+FDBptr->FDBvector[i];
               Scalar=FzyGetScalar(FDBptr,i,statusPtr);
               SumofScalars=SumofScalars+Scalar;
              }
          }
         if(n==0)
           {
            *statusPtr=3;
            return((double)0);
           }
         *Grade=(tval/n);
         Scalar=SumofScalars/n;
         CompleteDefuzz("AVGSUPPORT",Scalar,*Grade);
         return(Scalar);

        case NEAREDGE:
         FzyFindPlateau(FDBptr,Edges,&EdgeCnt,statusPtr);
         tvpos=Edges[Left];
         Scalar=FzyGetScalar(FDBptr,tvpos,statusPtr);
         *Grade=FDBptr->FDBvector[tvpos];
         CompleteDefuzz("NEAREDGE",Scalar,*Grade);
         return(Scalar);

        case  FAREDGE:
         FzyFindPlateau(FDBptr,Edges,&EdgeCnt,statusPtr);
         tvpos=Edges[Right];
         *Grade=FDBptr->FDBvector[tvpos];
         Scalar=FzyGetScalar(FDBptr,tvpos,statusPtr);
         CompleteDefuzz("FAREDGE",Scalar,*Grade);
         return(Scalar);

        default:
         Scalar=0.0;
         *statusPtr=99;
         MtsSendError(28,PgmId,MtsFormatInt(DefuzzMethod));
         return(Scalar);
     }

   }
 void CompleteDefuzz(char *DefuzzType,double Scalar,float Grade)
  {
   int   status;
   char  tmpBuff[28];

   memset(tmpBuff,'\0',28);
   strcpy(tmpBuff,"'");
   strcat(tmpBuff,DefuzzType);
   strcat(tmpBuff,"' ");
   sprintf(wrkBuff,"%-14.14s%s%10.3f%s%6.4f%s",
     tmpBuff," defuzzification. Value: ",Scalar,", [",Grade,"]");
   MtsWritetoLog(SYSMODFILE,wrkBuff,&status);
   return;
  }
