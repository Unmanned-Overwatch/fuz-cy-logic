/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzexs.cpp  Earl Cox  04/01/93 Explanatory System : Convert|
| membership values to appproximate English equivalents. This |
| functon generates a random variable to decide which text    |
| string will be used.                                        |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <RXB.hpp>
#include <XSYSctl.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
//
static char *PgmId="mtfzexs";
//
char *FzyXPSmemtext(float memgrade)
 {
  double rndVal=MtsRandomNumber();
  if(memgrade<0)    return(" ");
    else
  if(memgrade<0.1)
    {
     if(rndVal>0.8)     return(" hardly at all ");
       else             return(" very, very slightly ");
    }
  if(memgrade<0.2)
    {
     if(rndVal>0.8)     return(" not really ");
       else             return(" only slightly "  );
    }
   else
  if(memgrade<0.35)
    {
     if(rndVal>0.5)     return(", to a small extent, ");
       else             return(", to a slight degree, ");
    }
   else
  if(memgrade<0.65)
    {
     if(rndVal<0.33)    return(", to some extent, ");
       else
     if(rndVal<0.66)    return(", in part, ");
       else             return(", to some degree, ");
    }
   else
  if(memgrade<0.85)
    {
     if(rndVal>0.5)     return(", for the most part, ");
       else             return(", to a large degree, ");
    }
   else
    {
     if(rndVal>0.5)     return(" certainly ");
       else             return(" definitely ");
    }
 }
//
char *FzyXPSandtext(void)
 {
  double rndVal=MtsRandomNumber();
  if(rndVal>0.8)    return(" but ");
  if(rndVal>0.5)    return(" yet ");
  return(" and ");
 }
//
char *FzyXPSdegtext(void)
 {
  double rndVal=MtsRandomNumber();
  if(rndVal>0.8)    return(" true ");
  if(rndVal>0.6)    return(" suggested ");
  if(rndVal>0.5)    return(" specified ");
  return(" indicated ");
 }
//
//
char *FzyXPSpostext(double position)
 {
  if(position>.95) return("an extremely high");
  if(position>.90) return("a very high");
  if(position>.80) return("a high");
  if(position>.70) return("a somewhat high");
  if(position>.50) return("a middle");
  if(position>.40) return("a slightly low");
  if(position>.30) return("a somewhat low");
  if(position>.20) return("a quite low");
  if(position>.10) return("a very low");
  return("an extremely marginal");
 }
//
char *FzyXPSprftext(float memgrade)
 {
  if(memgrade>.8) return("definitely concluded that");
    else
  if(memgrade>.5) return("positively suggested that");
    else
  if(memgrade>.3) return("weakly asserted that");
    else          return("barely supported the notion that");
 }
//
char *FzyXPSacctext(int thisruleno)
 {
  char     *ruleno;
  double    rndVal=MtsRandomNumber();
  char     *wrkBuff;

  wrkBuff=new char[80];
  ruleno=MtsFormatInt(thisruleno);
  sprintf(wrkBuff,"%s%s%s","According to rule ",ruleno,", ");
  if(rndVal>0.8)
      sprintf(wrkBuff,"%s%s%s","Rule ",ruleno," states that ");
    else
  if(rndVal>0.6)
      sprintf(wrkBuff,"%s%s%s",
        "The contribution of rule ",ruleno," means that ");
    else
  if(rndVal>0.5)
    sprintf(wrkBuff,"%s%s%s","In rule ",ruleno," ");
  delete ruleno;
  return(wrkBuff);
 }
//
//
char *FzyXPSthentext(void)
 {
  double rndVal=MtsRandomNumber();
  if(rndVal>0.8)    return(" so ");
  if(rndVal>0.6)    return(" therefore the ");
  if(rndVal>0.5)    return(" thus the ");
  return(" the ");
 }
//
//
void FzyXPSInitRXB(RXB *RXBptr)
 {
  RXBptr->RXBruleno     =0;
  RXBptr->RXBpvarcnt    =0;
  RXBptr->RXBpremiseTV  =0;
  RXBptr->RXBpredhd     =NULL;
  RXBptr->RXBpredend    =NULL;
  RXBptr->RXBconsptr    =NULL;
  RXBptr->RXBnext       =NULL;
  return;
 }
//
//
void FzyXPSInitRXC(RXC *RXCptr)
 {
  RXCptr->RXCvarID      =NULL;
  RXCptr->RXCFuzzysetDescriptorID      =NULL;
  RXCptr->RXChedgeID    =NULL;
  RXCptr->RXCpropTV     =0.0;
  RXCptr->RXCnext       =NULL;
  return;
 }
//
//
RXB *FzyXPScreateRXB(int ruleno,int varcnt,float premisetv)
 {
  RXB    *RXBptr;

  if(!(RXBptr=new RXB))
    {
     MtsSendError(2,PgmId,"RXB");
     return(NULL);
    }
  FzyXPSInitRXB(RXBptr);
  RXBptr->RXBruleno     =ruleno;
  RXBptr->RXBpvarcnt    =varcnt;
  RXBptr->RXBpremiseTV  =premisetv;
  return(RXBptr);
 }
//
//
RXC *FzyXPScreateRXC(
  char *varid,char *FuzzysetDescriptorid,char *hedgeid,float proptv)
 {
  RXC    *RXCptr;
  int     j;

  if(!(RXCptr=new RXC))
    {
     MtsSendError(2,PgmId,"RXC");
     return(NULL);
    }
  FzyXPSInitRXC(RXCptr);
  j=strlen(varid);
  RXCptr->RXCvarID      =new char[j+1];
  strcpy(RXCptr->RXCvarID,varid);

  j=strlen(FuzzysetDescriptorid);
  RXCptr->RXCFuzzysetDescriptorID      =new char[j+1];
  strcpy(RXCptr->RXCFuzzysetDescriptorID,FuzzysetDescriptorid);

  j=strlen(hedgeid);
  RXCptr->RXChedgeID    =new char[j+1];
  strcpy(RXCptr->RXChedgeID,hedgeid);

  RXCptr->RXCpropTV     =proptv;
  return(RXCptr);
 }
//
//
void FzyXPSaddRXC(RXB *RXBptr,RXC *RXCptr,int RXCtype,int *statusPtr)
 {
  RXC   *RXCwrkptr;

  *statusPtr=0;
  if(RXBptr==NULL)
    {
     *statusPtr=5;
     MtsSendError(175,PgmId,"");
     return;
    }
  if(RXCptr==NULL)
    {
     *statusPtr=5;
     MtsSendError(176,PgmId,"");
     return;
    }
  RXCptr->RXCnext=NULL;                // A bit of defensive code
  switch(RXCtype)
   {
    case RXCpredtype:
     if(RXBptr->RXBpredhd==NULL)       // Nothing on the chain
        {
         RXBptr->RXBpredhd  =RXCptr;   // Link this RXC to chain head
         RXBptr->RXBpredend =RXCptr;   // Make last RXC also this RXC
         return;
        }
     RXCwrkptr=RXBptr->RXBpredend;     // get address of last RXC
     RXCwrkptr->RXCnext=RXCptr;        // chain this RXC into that RXC
     RXBptr->RXBpredend =RXCptr;       // make last RXC this RXC
     return;
    case RXCconstype:
     RXBptr->RXBconsptr=RXCptr;
     return;
    default:
     *statusPtr=1;
     return;
   }
 }
void FzyXPSdeleteRXBchain(RXB **RXBptr)
 {
  RXB  *tempRXBptr;
  RXC  *RXCptr,*tempRXCptr;

  for(;*RXBptr;*RXBptr=tempRXBptr)
    {
     RXCptr=(*RXBptr)->RXBpredhd;
     for(;RXCptr;RXCptr=tempRXCptr)
       {
        tempRXCptr=RXCptr->RXCnext;
        delete RXCptr;
       }
     RXCptr=(*RXBptr)->RXBconsptr;
     delete RXCptr;
     tempRXBptr=(*RXBptr)->RXBnext;
     delete (*RXBptr);
    }
   return;
 }
//
void FzyXPSshowrules(RXB *RXBhead)
 {
   int     i,j,numRXB;
   bool    sorted;
   int     maxRXB=32;
   RXB    *RXBptr,*tempRXB,*RXBvec[32];
   FILE   *mdlout;

   mdlout=MtsGetSystemFile(SYSMODFILE);
   srand((unsigned)time(NULL));
   RXBptr=RXBhead;
   if(RXBptr==NULL) return;
//
//--copy all the RXB nodes into an array. In a parallel array
//--store the premise truth values. These are the sort keys.
//
   numRXB=0;
   while(RXBptr!=NULL)
    {
     if(numRXB<maxRXB) RXBvec[numRXB]=RXBptr;
     RXBptr=RXBptr->RXBnext;
     numRXB++;
    }
   if(numRXB==0) return;
//
//--Now perform a simple bubble-sort. We want this to go from highest
//--to lowest, so we swap any truth value that is lower than the one
//--at the current position.
//
   for(i=0;i<(numRXB-1);i++)
     {
      sorted=TRUE;
      for(j=i;j<numRXB;j++)
        {
         if(RXBvec[i]->RXBpremiseTV<RXBvec[j]->RXBpremiseTV)
           {
            tempRXB  =RXBvec[i];
            RXBvec[i]=RXBvec[j];
            RXBvec[j]=tempRXB;
            sorted=FALSE;
           }
        }
      if(sorted==TRUE) break;
     }
   fprintf(mdlout,"%s\n%s",
    "1   .75  .50  .25   0                                         ",
    "|----+----+----+----+---------------------------R U L E S----|");
   for(i=0;i<numRXB;i++) FzyXPSexplain(RXBvec[i]);
   return;
 }
//
//
void FzyXPSexplain(RXB *RXBptr)
 {
   RXC    *RXCptr;
   char   *buff;
   int     i,inset;
   float   memval;
   double  prefixrnd;
   FILE   *mdlout;

   if(RXBptr==NULL)
     {
      MtsSendError(177,PgmId,"");
      return;
     }
   if(RXBptr->RXBpremiseTV<XSYSctl.XSYSalfacut) return;
   mdlout=MtsGetSystemFile(SYSMODFILE);
   prefixrnd=MtsRandomNumber();
   inset=FzyXPSinset(RXBptr->RXBpremiseTV);
   if(!(buff=new char[inset+1]))
     {
      MtsSendError(2,PgmId,"buff");
      return;
     }
   memset(buff,' ',inset);
   buff[inset]='\0';
   fprintf(mdlout,"\n%s%s",buff,FzyXPSacctext(RXBptr->RXBruleno));
   RXCptr=RXBptr->RXBpredhd;
   if(RXCptr!=NULL)
      {
       fprintf(mdlout,"%s%s\n",
         "we have ",FzyXPSprftext(RXBptr->RXBpremiseTV));
       if(prefixrnd<0.3) fprintf(mdlout,"%s%s",buff,"since ");
         else            fprintf(mdlout,"%s%s",buff,"because ");
       i=0;
       while(RXCptr!=NULL)
        {
         if(i>0) fprintf(mdlout,"\n%s%s%s",buff,"   ",FzyXPSandtext());
         memval=RXCptr->RXCpropTV;
         fprintf(mdlout,"%s%s%s",
          RXCptr->RXCvarID," is",FzyXPSmemtext(memval));
         if(strlen(RXCptr->RXChedgeID)>0)
            fprintf(mdlout,"%s ",RXCptr->RXChedgeID);
         fprintf(mdlout,"%s",RXCptr->RXCFuzzysetDescriptorID);
         RXCptr=RXCptr->RXCnext;
        }
       fprintf(mdlout,"\n%s%s",buff,FzyXPSthentext());
      }
   RXCptr=RXBptr->RXBconsptr;
   memval=RXBptr->RXBpremiseTV;
   fprintf(mdlout,"%s%s%s",
    RXCptr->RXCvarID," is",FzyXPSmemtext(memval));
   if(strlen(RXCptr->RXChedgeID)>0)
      fprintf(mdlout,"%s ",RXCptr->RXChedgeID);
   fprintf(mdlout,"%s",RXCptr->RXCFuzzysetDescriptorID);
   fputc('\n',mdlout);
   delete buff;
   return;
 }
//
//
int FzyXPSinset(float memgrade)
 {
  return((int)(21.00-(20.00*memgrade)));
 }
//
//
void FzyXPSconclusion(
  RXC *RXCptr,double Results,double Domain[],float CIXval)
 {
  char   *rsltval;
  double  position=Results/((Domain[1]-Domain[0])+1);
  FILE   *mdlout;

  mdlout=MtsGetSystemFile(SYSMODFILE);

  fprintf(mdlout,"\n%s",
   "----------------------------------------S O L U T I O N S------");
  rsltval=MtsFormatDbl(Results,3);
  fprintf(mdlout,"\n\n%s","In Conclusion....");
  fprintf(mdlout,"%s%s%s\n%s%s%s%s%s\n",
   "From these rules we find that \"",
     RXCptr->RXCvarID,"\"",
     "has a value of '",rsltval,"' which is",
     FzyXPSmemtext(CIXval),"supported.");
  fprintf(mdlout,"%s%s%s\n",
   "This is ",FzyXPSpostext(position)," value.");
  fputc('\n',mdlout);
  fputc('\n',mdlout);
  return;
 }
