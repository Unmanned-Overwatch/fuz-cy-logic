/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzplc.cpp  Earl Cox  04/01/93 Plateau Count               |
| This routine examines a fuzzy set to see if it contains     |
| more than a single plateau at the specified height.         |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include "FDB.hpp"
#include "mtypes.hpp"
int FzyPlateauCnt(FDB *FDBptr,float height,int *statusPtr)
 {
  bool   inPlateau;
  int    i,StartIDX,pCount=0;

  *statusPtr=0;
  //--locate the start of a plateau
  StartIDX=(int)MINUSONE;
  for(i=0;i<VECMAX;i++)
    if(FDBptr->FDBvector[i]!=0) StartIDX=i;
  if(StartIDX==MINUSONE) return(0);

//--We found trhe start of the first plateau. We now say
//--that we are in a plateau and we count this region.
  inPlateau=TRUE;
  pCount++;
//
//--Anytime we hit a zero, we have left the plateau. So
//--the next nonzero we hit will be start of another plateau.
//
  for(i=StartIDX;i<VECMAX;i++)
    if(FDBptr->FDBvector[i]==0) inPlateau=FALSE;
        else
         {
          if(inPlateau==FALSE)
            {
             pCount++;
             inPlateau=TRUE;
            }
         }
  return(pCount);
 }
