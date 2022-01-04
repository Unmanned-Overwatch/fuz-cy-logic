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
#include <FuzzysetDescriptor.hpp>
#include <HDB.hpp>
#include   <SystemTypes.hpp>
#include   <fuzzy.hpp>
#include <SystemPrototypes.hpp>
void Complete_hedge(const HDB*,const FuzzysetDescriptor*,FuzzysetDescriptor*);
void FzyApplyHedge(
   const FuzzysetDescriptor* inFuzzysetDescriptorptr,const HDB* HDBptr,FuzzysetDescriptor* outFuzzysetDescriptorptr,int *statusPtr)
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
   FzyCopySet(inFuzzysetDescriptorptr,outFuzzysetDescriptorptr,statusPtr);
   double  range=inFuzzysetDescriptorptr->FuzzysetDescriptordomain[1]-inFuzzysetDescriptorptr->FuzzysetDescriptordomain[0];
   double  hedgeval=HDBptr->HDBvalue;
   if(HDBptr->HDBmode==0)
     {
       switch(HDBptr->HDBop)
        {
         case ADD:
          for(i=0;i<VECMAX;i++)
           outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]+(float)hedgeval;
          break;
         case SUBTRACT:
          for(i=0;i<VECMAX;i++)
           outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]-(float)hedgeval;
          break;
         case MULTIPLY:
          for(i=0;i<VECMAX;i++)
           outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]*(float)hedgeval;
          break;
         case DIVIDE:
          for(i=0;i<VECMAX;i++)
           outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]/(float)hedgeval;
          break;
         case POWER:
          for(i=0;i<VECMAX;i++)
           outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=(float)pow(inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i],hedgeval);
          break;
         default:
          {
            *statusPtr=1;
            MtsSendError(18,PgmId,HDBptr->HDBid);
            return;
          }
        }/* Usertype */
      Complete_hedge(HDBptr,inFuzzysetDescriptorptr,outFuzzysetDescriptorptr);
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
        if(inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]!=0)
          {
           x=(double)i;
           for(j=0;j<VECMAX;j++)
            {
             part1=(float)(fabs(float(j)-(float)x)*range/VECMAX);
             part2=(float)((1.000/(1+pow(part1,EXPval)))*inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]);
             local[j]=max(local[j],part2);
            }
          }
       }
      for(i=0;i<VECMAX;++i) outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=local[i];
      break;
     case ABOVE:
      x=0.0;
      j=0;
      for(i=0;i<VECMAX;++i)
       if(inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i] >= x)
          {
           j=i;
           x=inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i];
           if(x==1.00)
             goto above_exit;
          }
      above_exit:
       for(i=0;i<VECMAX;++i)
        {
         if(i <= j)
           outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=0.0;
          else
           outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=1-inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i];
        }
      break;
     case POSITIVE:
      x=.5;
      for(i=0;i<VECMAX;++i)
       if(inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i] >= x)
           {
            hv=inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i];
            hv=(float)2*pow(hv,TWO);
            outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=(float)hv;
           }
         else
           {
            hv=inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i];
            hv=(float)1-(2*(pow(1-hv,TWO)));
            outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=(float)hv;
           }
      break;
     case AFTER:
      n=0;
      m=inFuzzysetDescriptorptr->FuzzysetDescriptorvector[0];
      for(i=0;i<VECMAX;i++)
         {
          if(inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]>m)m=inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i];
          if(inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]>0) if(n==0) n=i;
         }
      for(i=0;i<VECMAX;++i) outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=0.0;
      for(i=0;i<VECMAX;++i)
       if(inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i] >= m)
           {
            for(j=i,k=n+1;j<VECMAX;++j,k++)
                outFuzzysetDescriptorptr->FuzzysetDescriptorvector[j]=inFuzzysetDescriptorptr->FuzzysetDescriptorvector[k];
           }
      break;
     case BEFORE:
      n=0;
      m=inFuzzysetDescriptorptr->FuzzysetDescriptorvector[0];
      for(i=0;i<VECMAX;i++)
          if(inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]>m)m=inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i];
      for(i=VECMAX-1;i>=0;i--)
          if(inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]>0) if(n==0) n=i;
      for(i=0;i<VECMAX;++i) outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=0.0;
      for(i=VECMAX-1;i>=0;--i)
       if(inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i] >= m)
           {
            for(j=i,k=n-1;j>=0,k>=0;--j,k--)
               {
                if(j>=0 && k>=0)
                  outFuzzysetDescriptorptr->FuzzysetDescriptorvector[j]=inFuzzysetDescriptorptr->FuzzysetDescriptorvector[k];
               }
           }
      break;
     case BELOW:
      x=0.0;
      j=VECMAX;
      for(i=0;i<VECMAX;++i)
       if(inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i] >= x)
          {
           j=i;
           x=inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i];
           if(x==1.00)
             goto below_exit;
          }
      below_exit:
       for(i=0;i<VECMAX;++i)
        {
         if(i >= j)
           outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=0.0;
          else
           outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=1-inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i];
        }
      break;
     case GENERALLY:
      x=.5;
      for(i=0;i<VECMAX;++i)
       if(inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i] >= x)
           {
            hv=inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i];
            hv=(float)0.8*pow(hv,.5);
            outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=(float)hv;
           }
         else
           {
            hv=inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i];
            hv=(float)1-(0.8*(pow(1-hv,.5)));
            outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=(float)hv;
           }
      break;
     case NOT:
      for(i=0;i<VECMAX;++i)
       outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=1-inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i];
      break;
     case SOMEWHAT:
      for(i=0;i<VECMAX;++i)
       outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=(float)pow(inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i],POINTFIVE);
      break;
     case VERY:
      for(i=0;i<VECMAX;++i)
       outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=(float)pow(inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i],TWO);
      break;
     case EXTREMELY:
      for(i=0;i<VECMAX;++i)
       outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=(float)pow(inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i],THREE);
      break;
     case SLIGHTLY:
      for(i=0;i<VECMAX;++i)
       outFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=(float)pow(inFuzzysetDescriptorptr->FuzzysetDescriptorvector[i],POINTTHREE);
      break;
     default:
      {
        *statusPtr=3;
        MtsSendError(17,PgmId,HDBptr->HDBid);
        return;
      }
    }
   Complete_hedge(HDBptr,inFuzzysetDescriptorptr,outFuzzysetDescriptorptr);
   return;
  }

/*------------------------------------------------------------*
| The Complete_hedge routine (1) applies the current alpha-cut|
| to the hedge, (2) initiates any trace output to the model   |
| log, and (3) plots the currently hedged fuzzyset (if the    |
| active plot window state has been specified)                |
*-------------------------------------------------------------*/
  void Complete_hedge(
      const HDB* HDBptr,const FuzzysetDescriptor* inFuzzysetDescriptorptr,FuzzysetDescriptor* outFuzzysetDescriptorptr)
    {
     int     status;
     char    NameBuf[DESCLEN+1];
     char    wrkBuff[80];

     sprintf(wrkBuff,"%s%s%s%s%s",
      "Hedge '",HDBptr->HDBid,"' applied to Fuzzy Set \"",
        inFuzzysetDescriptorptr->FuzzysetDescriptorid,"\"");
     MtsWritetoLog(SYSMODFILE,wrkBuff,&status);
    //--Now update the name and the description of the new
    //--hedged fuzzy set.
     strcpy(outFuzzysetDescriptorptr->FuzzysetDescriptorid,inFuzzysetDescriptorptr->FuzzysetDescriptorid);
     strcpy(NameBuf,HDBptr->HDBid);
     strcat(NameBuf," ");
     strcat(NameBuf,inFuzzysetDescriptorptr->FuzzysetDescriptorid);
     strcpy(outFuzzysetDescriptorptr->FuzzysetDescriptordesc,NameBuf);
     return;
    }
