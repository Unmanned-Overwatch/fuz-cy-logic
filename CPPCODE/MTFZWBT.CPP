/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzwbt.cpp  Earl Cox  04/01/93 BETA curve generator        |
| This function creates a Beta distribution curve A Beta curve|
| is much narrower than the PI curve and does not go to zero  |
| at the edges of the domain.                                 |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <FuzzysetDescriptor.hpp>
#include   <fuzzy.hpp>
#include <SystemPrototypes.hpp>
void FzyWgtdBetaCurve(
   FuzzysetDescriptor *FuzzysetDescriptorptr,double Center,double flexpoint,double Wght,int *statusPtr)
 {
  int i;
  double  dwidth,memval,BetaPoint;

  *statusPtr=0;
  dwidth=FuzzysetDescriptorptr->FuzzysetDescriptordomain[1]-FuzzysetDescriptorptr->FuzzysetDescriptordomain[0];
  for(i=0;i<VECMAX;i++)
    {
     memval=FuzzysetDescriptorptr->FuzzysetDescriptordomain[0]+(float)i/(VECMAX-1)*dwidth;
     BetaPoint=(memval-Center)/flexpoint;
     FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=(float)(1/(1+(Wght*pow(BetaPoint,2))));
    }
  FuzzysetDescriptorptr->FuzzysetDescriptorgentype=WGTDBETA;
  FuzzysetDescriptorptr->FuzzysetDescriptorparms[0]=Center;
  FuzzysetDescriptorptr->FuzzysetDescriptorparms[1]=flexpoint;
 }
