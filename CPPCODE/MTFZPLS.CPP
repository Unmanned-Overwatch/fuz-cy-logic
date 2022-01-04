/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtfzpls.cpp   Earl Cox  04/01/93 Draw a fuzzy set           |
| This procedure draws a set of fuzzy sets along the same     |
| horizontal domain. It is used principally to display all the|
| sets associated with a particular control/solution variable |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#define PLOTROWS   26
#define PLOTCOLS   70
#define BIGNUMBER  999999999
#include <stdio.h>
#include <string.h>
#include <FuzzysetDescriptor.hpp>
#include   <fuzzy.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
void FzyPlotSets(
   char *Varid,FuzzysetDescriptor *FuzzysetDescriptorptr[],int FzySetCnt,int Medium,int *statusPtr)
  {
    char        WkArea[PLOTROWS][PLOTCOLS+1];
    int         i,j,k,PltHgt,Sidx,N,HorzPos,VertPos;
    int         ScalingIdx=1,ScaleCtl=4;
    double      x,Domain[2];
    FILE        *outfp;

    const char  Symbol[]=".*+:^!@-#$=";
    const int   SymCnt=11;
    const int   PlotHeight[]    = {0,11,21,26,51};
    const float ScalingFactor[] = {0,10.0,20.0,25.0,50.0};

    *statusPtr=0;
    if(FzySetCnt==0) return;
    if(FzySetCnt>SymCnt) FzySetCnt=SymCnt;
    outfp=MtsGetSystemFile(Medium);
//--Blank out the plot area and then put a string terminator
//--at the end of each row. This is used in the fprint output.
    for(i=0;i<26;i++)
     {
       for(j=0;j<70;j++) WkArea[i][j]=' ';
       WkArea[i][j]='\0';
     }
//--Fill out the plot MxN area.
   Domain[0]=BIGNUMBER;
   Domain[1]=0;
   for(i=0;i<FzySetCnt;i++)
    {
     Domain[0]=min(FuzzysetDescriptorptr[i]->FuzzysetDescriptordomain[0],Domain[0]);
     Domain[1]=max(FuzzysetDescriptorptr[i]->FuzzysetDescriptordomain[1],Domain[1]);
     for(k=0;k<VECMAX;k+=ScaleCtl)
       {
        Sidx=ScalingFactor[ScalingIdx];
        VertPos=(int)(Sidx*(FuzzysetDescriptorptr[i]->FuzzysetDescriptorvector[k]+NUDGE));
        HorzPos= k / ScaleCtl;
        if((VertPos+1>=0)&&(VertPos+1<PLOTROWS))
             WkArea[VertPos+1][HorzPos]=Symbol[i];
       }
    }
//--Now we write out the plot area
    fputc('\f',outfp);
    fprintf(outfp,"%s%s%s\n","                     '",Varid,"'");
    fputc('\n',outfp);
    PltHgt=PlotHeight[ScalingIdx];
    for(N=PltHgt,i=0;i<PltHgt;i++,--N)
      {
       j=PltHgt-i;
       x=(j-1)/ScalingFactor[ScalingIdx];
       fprintf(outfp,"%10.2f%s\n",x,&WkArea[N][0]);
      }
    fprintf(outfp,"%s%s",
     "          0---|---|---|---|---|---|---|---|---|---|---|---|",
     "---|---|---|---0\n");
    x=(Domain[1]-Domain[0])/8.0;
    fputs("     ",outfp);
    for(i=0;i<9;i++) fprintf(outfp,"%8.2f",Domain[0]+(x*i));
    fputc('\n', outfp);
    for(i=0;i<FzySetCnt;i++)
     {
      fprintf(outfp,"%s%c%s%s\n",
       "     ",Symbol[i],          "   FuzzySet:    ",FuzzysetDescriptorptr[i]->FuzzysetDescriptorid);
      fprintf(outfp,"%s%s\n","         Description: ",FuzzysetDescriptorptr[i]->FuzzysetDescriptordesc);
      fprintf(outfp,
       "%s%10.2f%s%10.2f\n","         Domained:   ",
         FuzzysetDescriptorptr[0]->FuzzysetDescriptordomain[0]," to ",FuzzysetDescriptorptr[0]->FuzzysetDescriptordomain[1]);
    if(FuzzysetDescriptorptr[i]->FuzzysetDescriptoralfacut>0)
      fprintf(outfp,
       "%s%10.2f\n",        "         AlphaCut:   ",FuzzysetDescriptorptr[i]->FuzzysetDescriptoralfacut);
     }
    fputc('\n',outfp);
  }
