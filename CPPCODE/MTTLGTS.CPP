/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlgts.cpp  Earl Cox  04/01/93 General Table Search        |
| This routine searches a table of character strings and      |
| returns an index to the position that contains a match with |
| the search paramter. We search for equal length strings.    |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include "string.h"
#include   <mtypes.hpp>
int MtsSearchTable(char *Word,char **Table,int tabmax,int *statusPtr)
  {
   int k,i;

   *statusPtr=0;
   k=strlen(Word);
   for(i=0;i<tabmax;i++)
      if(strncmp(Word,Table[i],k)==0) return(i);
   *statusPtr=9;
   return(-1);
  }
