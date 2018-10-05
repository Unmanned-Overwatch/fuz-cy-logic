/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlsqs.cpp   Earl Cox  04/01/93 Perform Sequential Search  |
| This procedure performs a serial (sequential) search on a   |
| target table. It will return a match based on the COMPTYPE  |
| argument. If comptype=FULL then the match must be exact,    |
| if comptype=PARTIAL, then any left hand subset will match,  |
| and if comptype=ANY, then we also match on embedded strings.|
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include   <mtypes.hpp>
int MtsSerialSearch(
     char *Word,const char **Table,int TblCnt,int CompType)
  {
    int i;
    int Wordlen=strlen(Word);
    switch(CompType)
     {
      case FULL:
       for(i=0;i<TblCnt;i++)
        if(strcmp(Word,Table[i])==0) return(i);
       return(-1);
      case PARTIAL:
       for(i=0;i<TblCnt;i++)
        if(strncmp(Word,Table[i],Wordlen)==0) return(i);
        return(-1);
      case ANY:
       for(i=0;i<TblCnt;i++)
        if(strstr(Word,Table[i])!=NULL) return(i);
        return(-1);
      default:
        return(-3);
     }
  }
