/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzimm.cpp   Earl Cox  04/01/93 The implication matrix     |
| This function creates the implication matrix associated     |
| with two fuzzy sets. The implication matrix is defined as   |
| the intersection of the two sets (that is the minimum of    |
| each truth value.                                           |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <FuzzysetDescriptor.hpp>
#include   <fuzzy.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
void FzyImplMatrix(
   FuzzysetDescriptor *FuzzysetDescriptorptr1,FuzzysetDescriptor *FuzzysetDescriptorptr2,
    double DomValues[],int DomCnt,int *statusPtr)
  {
   FuzzysetDescriptor    WrkFuzzysetDescriptor;
   char   FSname1[IDENLEN+1],FSname2[IDENLEN+1];
   char   PrtBuff[256];
   int    i,j,m,n;
   double Scalar,Lo[2],Hi[2],value1[21],value2[21];
   float  TheMatrix[21][21],
          scale1,scale2,truth1[21],truth2[21],
          memvalue;
   FILE  *mdlout;

   const int MaxCells=9;
   const int PrtBufflen=256;

   *statusPtr=0;
   mdlout=MtsGetSystemFile(SYSMODFILE);
   for(i=0,n=0;i<VECMAX;i+=32,n++)
    for(j=0,m=0;j<VECMAX;j+=32,m++)
     TheMatrix[n][m]=
      min(FuzzysetDescriptorptr1->FuzzysetDescriptorvector[i],FuzzysetDescriptorptr2->FuzzysetDescriptorvector[j]);
//--Pick up the names and domains of the two fuzzy sets.
   strcpy(FSname1,FuzzysetDescriptorptr1->FuzzysetDescriptorid);
   strcpy(FSname2,FuzzysetDescriptorptr2->FuzzysetDescriptorid);
   Lo[0]=FuzzysetDescriptorptr1->FuzzysetDescriptordomain[0];
   Hi[0]=FuzzysetDescriptorptr1->FuzzysetDescriptordomain[1];
   Lo[1]=FuzzysetDescriptorptr2->FuzzysetDescriptordomain[0];
   Hi[1]=FuzzysetDescriptorptr2->FuzzysetDescriptordomain[1];
//--Calculate any autoscaling necessary to fit the domains
//--into the current default print width for the report
   scale1=FzyAutoScale(Hi[0],Lo[0]);
   scale2=FzyAutoScale(Hi[1],Lo[1]);
   fprintf(mdlout,"%s\n",
    "                      Approximate Reasoning System");
   fprintf(mdlout,"%s%s%s%s%s\n",
    "                      Implication Matrix for '",
        FSname1,"' and '",FSname2,"'");
   fputs("\n",mdlout);
   for(n=0,i=0;i<VECMAX;i+=32,n++)
     {
      value1[n]=FzyGetScalar(FuzzysetDescriptorptr1,i,statusPtr);
      truth1[n]=FuzzysetDescriptorptr1->FuzzysetDescriptorvector[i];
      value2[n]=FzyGetScalar(FuzzysetDescriptorptr2,i,statusPtr);
      truth2[n]=FuzzysetDescriptorptr2->FuzzysetDescriptorvector[i];
     }
   memset(PrtBuff,'\0',PrtBufflen);
   strcpy(PrtBuff,FSname1);
   strcat(PrtBuff,"                ");
   fprintf(mdlout,"%s%s\n","              ",FSname2);
   fprintf(mdlout,"%13.13s",PrtBuff);
   for(i=0;i<MaxCells;i++)
    fprintf(mdlout," %5.2f",value2[i]/scale2);
   fputc('\n',mdlout);
   for(i=0;i<MaxCells;i++)
     {
      fprintf(mdlout,"%5.2f%s%3.2f%s",
        value1[i]/scale1," ",truth1[i]," | ");
      fputc('  ',mdlout);
      for(j=0;j<MaxCells;j++)
        fprintf(mdlout,"%5.2f ",TheMatrix[i][j]);
      fputc('\n',mdlout);
     }
   if(scale1>1||scale2>1)
     {
      fprintf(mdlout,"\n%s\n","Scaling:");
      if(scale1>1)
        fprintf(mdlout,"%s%s%8.2f\n",FSname1,".....x",scale1);
      if(scale2>1)
        fprintf(mdlout,"%s%s%8.2f\n",FSname2,".....x",scale2);
     }
   fputs("\n\n",mdlout);
//--Now we look to see whether or not the user wants to plot the
//--implication relations.
   if(DomCnt==0) return;
   for(i=0;i<DomCnt;i++)
    {
      Scalar=DomValues[i];
      memvalue=FzyGetMembership(FuzzysetDescriptorptr1,Scalar,&j,statusPtr);
      FzyCopySet(FuzzysetDescriptorptr2,&WrkFuzzysetDescriptor,statusPtr);
      for(j=0;j<VECMAX;j++)
       WrkFuzzysetDescriptor.FuzzysetDescriptorvector[j]=min(memvalue,WrkFuzzysetDescriptor.FuzzysetDescriptorvector[j]);
      fprintf(mdlout,"%s%s%s%s%s%10.2f\n",
       "        '",FSname2,"' when '",FSname1,"' is ",Scalar);
      FzyDrawSet(&WrkFuzzysetDescriptor,SYSMODFILE,statusPtr);
    }
   return;
  }
