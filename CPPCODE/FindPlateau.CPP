/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzfpl.cpp   Earl Cox  04/01/93 Find Plateau in FuzzySet.  |
| Used primarily in the defuzzification process, this routine |
| looks at the consequent set and isolates the plateaus.      |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <FuzzysetDescriptor.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
static char   wrkBuff[225];
void IssueWarning(FuzzysetDescriptor*,float,int);
void FzyFindPlateau(
   FuzzysetDescriptor* FuzzysetDescriptorptr,int Edges[],int *EdgeCnt,int *statusPtr)
  {
   FuzzysetDescriptor    *WrkFuzzysetDescriptorptr;
   char   *PgmId="mtfzfpl";
   int     i,j,pCount,pRight=(VECMAX-1);
   float   SetHeight;

   *statusPtr=0;
   *EdgeCnt=0;
    Edges[0]=0;
    Edges[1]=0;
   SetHeight=FzyGetHeight(FuzzysetDescriptorptr);
   if(SetHeight==0)
     {
      sprintf(wrkBuff,"%s%s%s%6.4f",
       "IMPORTANT: Solution Fuzzy Set '",FuzzysetDescriptorptr->FuzzysetDescriptorid,
        "' is empty (set height == ",SetHeight);
      MtsWritetoLog(SYSMODFILE,wrkBuff,statusPtr);
      return;
     }
   if(!(WrkFuzzysetDescriptorptr=new FuzzysetDescriptor))
     {
      *statusPtr=1;
      MtsSendError(2,PgmId,"WrkFuzzysetDescriptor");
      return;
     }
   FzyCopySet(FuzzysetDescriptorptr,WrkFuzzysetDescriptorptr,statusPtr);
   for(i=0;i<VECMAX;i++)
     if(WrkFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]<SetHeight) WrkFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]=0.0;
   if((pCount=FzyPlateauCnt(FuzzysetDescriptorptr,SetHeight,statusPtr))>1)
       IssueWarning(FuzzysetDescriptorptr,SetHeight,pCount);
   for(i=0;i<pRight;i++)
    {
      if(WrkFuzzysetDescriptorptr->FuzzysetDescriptorvector[i]>0)
        {
         for(j=pRight;j>=0;j--)
          {
           if(j<i)
             {
              *statusPtr=3;
              MtsSendError(94,PgmId,FuzzysetDescriptorptr->FuzzysetDescriptorid);
              return;
             }
           if(WrkFuzzysetDescriptorptr->FuzzysetDescriptorvector[j]>0)
             {
              Edges[0]=i;
              Edges[1]=j;
             //--Ok, we now have the left and right hand side of
             //--the plateau in the truth membership function.
             //--if the right and left hand indexes are inside
             //--the fuzzy set, then this is a double edged plateau.
              if(i>0&&j<pRight)  *EdgeCnt=2;
                else             *EdgeCnt=1;
              delete WrkFuzzysetDescriptorptr;
              return;
             }
          }
        }
    }
  }
//
//
void IssueWarning(FuzzysetDescriptor *FuzzysetDescriptorptr,float SetHeight,int pCount)
 {
  int    status;

  sprintf(wrkBuff,"%s%s%s%4d%s%6.4f",
   "CAUTION: Solution Fuzzy Set '",FuzzysetDescriptorptr->FuzzysetDescriptorid,
    "' has ",pCount," plateau(s) at height: ",SetHeight);
  MtsWritetoLog(SYSMODFILE,wrkBuff,&status);
 }
