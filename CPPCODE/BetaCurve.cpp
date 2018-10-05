/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtfzbts.cpp  Earl Cox  04/01/93 BETA curve generator        |
| This function creates a Beta distribution curve A Beta curve|
| is much narrower than the PI curve and does not go to zero  |
| at the edges of the domain.                                 |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <fdb.hpp>
#include <fuzzy.hpp>
#include <mtsptype.hpp>
void FzyBetaCurve(
   FDB *FDBptr,double Center,double flexpoint,int *statusPtr)
 {
  int i;
  double  dwidth,memval,BetaPoint;

  *statusPtr=0;
  dwidth=FDBptr->FDBdomain[1]-FDBptr->FDBdomain[0];
  for(i=0;i<VECMAX;i++)
    {
     memval=FDBptr->FDBdomain[0]+(float)i/(VECMAX-1)*dwidth;
     BetaPoint=(memval-Center)/flexpoint;
     FDBptr->FDBvector[i]=(float)(1/(1+pow(BetaPoint,2)));
    }
  FDBptr->FDBgentype=BETA;
  FDBptr->FDBparms[0]=Center;
  FDBptr->FDBparms[1]=flexpoint;
 }
