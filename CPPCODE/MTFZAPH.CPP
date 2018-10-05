/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtfzaph.cpp   Earl Cox  04/01/93 Apply a Hedge. This is the |
| meta-controller for all the fuzzy set hedge operations. With|
| this one program we can specify both builtin and user hedges|
*-------------------------------------------------------------*/
#include <math.h>
#include <stdio.h>
#include <string.h>
double max(double,double);
#include "FDB.hpp"
#include "HDB.hpp"
#include "mtypes.hpp"
#include "fuzzy.hpp"
#include "mtsptype.hpp"
void Complete_hedge(const HDB*,const FDB*,FDB*);
void FzyApplyHedge(
   const FDB* inFDBptr,const HDB* HDBptr,FDB* outFDBptr,int *statusPtr)
  {
   int      i,j,k,n;
   double   x,
            hv;
   float    local[VECMAX+1],m,part1,part2;
   double   EXPval;
   char    *PgmId="mtfzaph";
   // char     buff[80];
   // FILE    *mdllog;

   *statusPtr=0;
   FzyCopySet(inFDBptr,outFDBptr,statusPtr);
   double  range=inFDBptr->FDBdomain[1]-inFDBptr->FDBdomain[0];
   double  hedgeval=HDBptr->HDBvalue;
   if(HDBptr->HDBmode==0)
     {
       switch(HDBptr->HDBop)
        {
         case ADD:
          for(i=0;i<VECMAX;i++)
           outFDBptr->FDBvector[i]=inFDBptr->FDBvector[i]+(float)hedgeval;
          break;
         case SUBTRACT:
          for(i=0;i<VECMAX;i++)
           outFDBptr->FDBvector[i]=inFDBptr->FDBvector[i]-(float)hedgeval;
          break;
         case MULTIPLY:
          for(i=0;i<VECMAX;i++)
           outFDBptr->FDBvector[i]=inFDBptr->FDBvector[i]*(float)hedgeval;
          break;
         case DIVIDE:
          for(i=0;i<VECMAX;i++)
           outFDBptr->FDBvector[i]=inFDBptr->FDBvector[i]/(float)hedgeval;
          break;
         case POWER:
          for(i=0;i<VECMAX;i++)
           outFDBptr->FDBvector[i]=(float)pow(inFDBptr->FDBvector[i],hedgeval);
          break;
         default:
          {
            *statusPtr=1;
            MtsSendError(18,PgmId,HDBptr->HDBid);
            return;
          }
        }/* Usertype */
      Complete_hedge(HDBptr,inFDBptr,outFDBptr);
      return;
     }
   switch(HDBptr->HDBmode)
    {
     case ABOUT:
     case VICINITY:
     case CLOSE:
      if(HDBptr->HDBmode==ABOUT)    EXPval=2;
      if(HDBptr->HDBmode==VICINITY) EXPval=4;
      if(HDBptr->HDBmode==CLOSE)    EXPval=1.2;
      for(i=0;i<VECMAX;++i) local[i]=0.0;
      for(i=0;i<VECMAX;i++)
       {
        if(inFDBptr->FDBvector[i]!=0)
          {
           x=(double)i;
           for(j=0;j<VECMAX;j++)
            {
             part1=(float)(fabs(float(j)-(float)x)*range/VECMAX);
             part2=(float)((1.000/(1+pow(part1,EXPval)))*inFDBptr->FDBvector[i]);
             local[j]=max(local[j],part2);
            }
          }
       }
      for(i=0;i<VECMAX;++i) outFDBptr->FDBvector[i]=local[i];
      break;
     case ABOVE:
      x=0.0;
      j=0;
      for(i=0;i<VECMAX;++i)
       if(inFDBptr->FDBvector[i] >= x)
          {
           j=i;
           x=inFDBptr->FDBvector[i];
           if(x==1.00)
             goto above_exit;
          }
      above_exit:
       for(i=0;i<VECMAX;++i)
        {
         if(i <= j)
           outFDBptr->FDBvector[i]=0.0;
          else
           outFDBptr->FDBvector[i]=1-inFDBptr->FDBvector[i];
        }
      break;
     case POSITIVE:
      x=.5;
      for(i=0;i<VECMAX;++i)
       if(inFDBptr->FDBvector[i] >= x)
           {
            hv=inFDBptr->FDBvector[i];
            hv=(float)2*pow(hv,TWO);
            outFDBptr->FDBvector[i]=(float)hv;
           }
         else
           {
            hv=inFDBptr->FDBvector[i];
            hv=(float)1-(2*(pow(1-hv,TWO)));
            outFDBptr->FDBvector[i]=(float)hv;
           }
      break;
     case AFTER:
      n=0;
      m=inFDBptr->FDBvector[0];
      for(i=0;i<VECMAX;i++)
         {
          if(inFDBptr->FDBvector[i]>m)m=inFDBptr->FDBvector[i];
          if(inFDBptr->FDBvector[i]>0) if(n==0) n=i;
         }
      for(i=0;i<VECMAX;++i) outFDBptr->FDBvector[i]=0.0;
      for(i=0;i<VECMAX;++i)
       if(inFDBptr->FDBvector[i] >= m)
           {
            for(j=i,k=n+1;j<VECMAX;++j,k++)
                outFDBptr->FDBvector[j]=inFDBptr->FDBvector[k];
           }
      break;
     case BEFORE:
      n=0;
      m=inFDBptr->FDBvector[0];
      for(i=0;i<VECMAX;i++)
          if(inFDBptr->FDBvector[i]>m)m=inFDBptr->FDBvector[i];
      for(i=VECMAX-1;i>=0;i--)
          if(inFDBptr->FDBvector[i]>0) if(n==0) n=i;
      for(i=0;i<VECMAX;++i) outFDBptr->FDBvector[i]=0.0;
      for(i=VECMAX-1;i>=0;--i)
       if(inFDBptr->FDBvector[i] >= m)
           {
            for(j=i,k=n-1;j>=0,k>=0;--j,k--)
               {
                if(j>=0 && k>=0)
                  outFDBptr->FDBvector[j]=inFDBptr->FDBvector[k];
               }
           }
      break;
     case BELOW:
      x=0.0;
      j=VECMAX;
      for(i=0;i<VECMAX;++i)
       if(inFDBptr->FDBvector[i] >= x)
          {
           j=i;
           x=inFDBptr->FDBvector[i];
           if(x==1.00)
             goto below_exit;
          }
      below_exit:
       for(i=0;i<VECMAX;++i)
        {
         if(i >= j)
           outFDBptr->FDBvector[i]=0.0;
          else
           outFDBptr->FDBvector[i]=1-inFDBptr->FDBvector[i];
        }
      break;
     case GENERALLY:
      x=.5;
      for(i=0;i<VECMAX;++i)
       if(inFDBptr->FDBvector[i] >= x)
           {
            hv=inFDBptr->FDBvector[i];
            hv=(float)0.8*pow(hv,.5);
            outFDBptr->FDBvector[i]=(float)hv;
           }
         else
           {
            hv=inFDBptr->FDBvector[i];
            hv=(float)1-(0.8*(pow(1-hv,.5)));
            outFDBptr->FDBvector[i]=(float)hv;
           }
      break;
     case NOT:
      for(i=0;i<VECMAX;++i)
       outFDBptr->FDBvector[i]=1-inFDBptr->FDBvector[i];
      break;
     case SOMEWHAT:
      for(i=0;i<VECMAX;++i)
       outFDBptr->FDBvector[i]=(float)pow(inFDBptr->FDBvector[i],POINTFIVE);
      break;
     case VERY:
      for(i=0;i<VECMAX;++i)
       outFDBptr->FDBvector[i]=(float)pow(inFDBptr->FDBvector[i],TWO);
      break;
     case EXTREMELY:
      for(i=0;i<VECMAX;++i)
       outFDBptr->FDBvector[i]=(float)pow(inFDBptr->FDBvector[i],THREE);
      break;
     case SLIGHTLY:
      for(i=0;i<VECMAX;++i)
       outFDBptr->FDBvector[i]=(float)pow(inFDBptr->FDBvector[i],POINTTHREE);
      break;
     default:
      {
        *statusPtr=3;
        MtsSendError(17,PgmId,HDBptr->HDBid);
        return;
      }
    }
   Complete_hedge(HDBptr,inFDBptr,outFDBptr);
   return;
  }

/*------------------------------------------------------------*
| The Complete_hedge routine (1) applies the current alpha-cut|
| to the hedge, (2) initiates any trace output to the model   |
| log, and (3) plots the currently hedged fuzzyset (if the    |
| active plot window state has been specified)                |
*-------------------------------------------------------------*/
  void Complete_hedge(
      const HDB* HDBptr,const FDB* inFDBptr,FDB* outFDBptr)
    {
     int     status;
     char    NameBuf[DESCLEN+1];
     char    wrkBuff[80];

     sprintf(wrkBuff,"%s%s%s%s%s",
      "Hedge '",HDBptr->HDBid,"' applied to Fuzzy Set \"",
        inFDBptr->FDBid,"\"");
     MtsWritetoLog(SYSMODFILE,wrkBuff,&status);
    //--Now update the name and the description of the new
    //--hedged fuzzy set.
     strcpy(outFDBptr->FDBid,inFDBptr->FDBid);
     strcpy(NameBuf,HDBptr->HDBid);
     strcat(NameBuf," ");
     strcat(NameBuf,inFDBptr->FDBid);
     strcpy(outFDBptr->FDBdesc,NameBuf);
     return;
    }
