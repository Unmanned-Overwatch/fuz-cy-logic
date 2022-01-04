/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtfzdrw.cpp   Earl Cox  04/01/93 Draw a fuzzy set           |
| This procedure draws a fuzzy set on the current model log   |
| file. We use variable scaling to get the set at different   |
| degrees of resolution. This is a character oriented graph.  |
*-------------------------------------------------------------*/
#define PLOTROWS   26
#define PLOTCOLS   70
#include <stdio.h>
#include <string.h>
#include <FuzzysetDescriptor.hpp>
#include   <fuzzy.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
void FzyDrawSet(FuzzysetDescriptor *FuzzysetDescriptorptr,int Medium,int *statusPtr)
  {
    char        WkArea[PLOTROWS][PLOTCOLS+1];
    int         i,j,k,Sidx,PltHgt,N,HorzPos,VertPos;
    int         ScalingIdx=1,ScaleCtl  =4;
    double      x,Domain[2];
    FILE       *outfp;

    const char  Symbol='.';
    const int   PlotHeight[]    = {0,11,21,26,51};
    const float ScalingFactor[] = {0,10.0,20.0,25.0,50.0};

    *statusPtr=0;
    outfp=MtsGetSystemFile(Medium);
    Domain[0]=FuzzysetDescriptorptr->FuzzysetDescriptordomain[0];
    Domain[1]=FuzzysetDescriptorptr->FuzzysetDescriptordomain[1];
//--Blank out the plot area and then put a string terminator
//--at the end of each row. This is used in the fprint output.
    for(i=0;i<26;i++)
     {
       for(j=0;j<70;j++)  WkArea[i][j]=' ';
       WkArea[i][j]='\0';
     }
//--Fill out the plot MxN area.
    Sidx=ScalingFactor[ScalingIdx];
    for(k=0;k<VECMAX;k+=ScaleCtl)
      {
       VertPos=(int)(Sidx*(FuzzysetDescriptorptr->FuzzysetDescriptorvector[k]+NUDGE));
       HorzPos= k / ScaleCtl;
       if((VertPos+1>=0)&&(VertPos+1<PLOTROWS))
            WkArea[VertPos+1][HorzPos]=Symbol;
      }
//--Now we write out the plot area
    fputc('\f',outfp);
    fputc('\n',outfp);
    fprintf(outfp,"%s%s\n","        FuzzySet:    ",FuzzysetDescriptorptr->FuzzysetDescriptorid);
    fprintf(outfp,"%s%s\n","        Description: ",FuzzysetDescriptorptr->FuzzysetDescriptordesc);
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
    fprintf(outfp,
      "%s%10.2f%s%10.2f\n", "        Domained:   ",
         FuzzysetDescriptorptr->FuzzysetDescriptordomain[0]," to ",FuzzysetDescriptorptr->FuzzysetDescriptordomain[1]);
    if(FuzzysetDescriptorptr->FuzzysetDescriptoralfacut>0)
      fprintf(outfp,
       "%s%10.2f\n",        "         AlphaCut:   ",FuzzysetDescriptorptr->FuzzysetDescriptoralfacut);
    fputc('\n',outfp);
  }
