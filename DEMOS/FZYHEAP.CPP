/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| fzyheap.cpp  Earl Cox  06/10/93 The fuzzy logic heap paradox|
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include "mtypes.hpp"
void main(void)
 {
  int     Removedstones[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
  int     stoneMax=16;
  int     heapMax=1000;
  int     heapInterval=100;
  int     i,n;
  float   isAHeap;
  float   Heapstones=1000;
  float   ReducedTruth=(1/Heapstones);
  float   isNOTAHeapTruth=1-ReducedTruth;

 printf("%s\n",      "THE HEAP PARADOX");
 printf("%s%10.2f\n","Heapstones        : ",Heapstones);
 printf("%s%10.6f\n","ReducedTruth      : ",ReducedTruth);
 printf("%s%10.6f\n","isNOTAHeapTruth   : ",isNOTAHeapTruth);
 printf("%s\n\n",    "Fuzzy Product AND operator");
 printf("%s\n%s\n%s\n",
  "Stones           Is a",
  "Removed          Heap",
  "-------      --------");
 isAHeap=1;
 for(i=0;i<stoneMax;i++)
    {
      isAHeap*=isNOTAHeapTruth;
      printf("%7d       %8.6f\n",Removedstones[i],isAHeap);
    }
 for(i=17;i<heapMax;i++)
    {
      isAHeap*=isNOTAHeapTruth;
      if((i%heapInterval)==0)
        printf("%7d       %8.6f\n",i,isAHeap);
    }
 printf("\n\n%s\n",    "Fuzzy minimum AND operator");
 printf("%s\n%s\n%s\n",
  "Stones           Is a",
  "Removed          Heap",
  "-------      --------");
 isAHeap=1;
 for(i=0;i<stoneMax;i++)
    {
      isAHeap=min(isAHeap,isNOTAHeapTruth);
      printf("%7d       %8.6f\n",Removedstones[i],isAHeap);
    }
 }
