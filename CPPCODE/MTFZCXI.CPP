/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtfzcxi.cpp   Earl Cox  04/01/93 Initialize the CIX area    |
| This routine is called to initialize the Statistical        |
| Compatibility Index block.                                  |
*-------------------------------------------------------------*/
#include <stddef.h>
#include "CIX.hpp"
#include "fuzzy.hpp"
void FzyInitCIX(CIX *CIXptr)
  {
   CIXptr->CIXmodelid=NULL;
   CIXptr->CIXsegmentid=NULL;
   CIXptr->CIXvarid=NULL;
   CIXptr->CIXruncount=0;
   CIXptr->CIXcompType=STRONG;
//--Zero out the cumulative truth variables
   CIXptr->CIXCummaxTruth=0.0;
   CIXptr->CIXCumminTruth=0.0;
   CIXptr->CIXCumdeltaTruth=0.0;
   CIXptr->CIXCumexpvTruth=0.0;
//--Set up the minimum and maximum threshold defaults
   CIXptr->CIXMinTruth=.18;
   CIXptr->CIXMaxTruth=.92;
//--Zero out the average truth variables
   CIXptr->CIXAvgmaxTruth=0.0;
   CIXptr->CIXAvgminTruth=0.0;
   CIXptr->CIXAvgdeltaTruth=0.0;
   CIXptr->CIXAvgexpvTruth=0.0;
  }
