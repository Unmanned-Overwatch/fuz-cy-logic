/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzgcd.cpp   Earl Cox  04/01/93 Get Coordinate Data Points |
| This procedure takes a character string holding coordinate  |
| data in the form "value/mem value/mem value/mem ..." and    |
| returns an array holding the values and the membership      |
| values.                                                     |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <stdlib.h>
#include <SystemPrototypes.hpp>
void FzyGetCoordinates(
  char *Coords,double Values[],float Members[],
   int *VcntPtr,int *statusPtr)
  {
    char   *Tokens[128];
    char   *PgmId="mtfzgcd";
    int     i,NumType,TokCnt,toknum;
    int     PartLength=16;
    int     MaxTokens=128;
    double  Scalar,MFvalue;

    *VcntPtr=0;
    *statusPtr=0;
//--Step 1. Entoken the co-ordinate character string into a set
//--of individual value and membership elements. This simplifies our
//--processing of each element.
    TokCnt=0;
    MtsEntoken(Coords,Tokens,MaxTokens,&TokCnt,statusPtr);
    if(*statusPtr!=0) return;
    if(TokCnt==0)     return;
//--Step 2.For each token, extract the scalar value and the
//--membership. We convert the scalar to a double precision
//--number and the membership to the single precision floating
//--point number.
    toknum=0;
    for(i=0;i<TokCnt/2;i++)
     {
       if(!(MtsIsNumeric(Tokens[toknum],&NumType)))
         {
          *statusPtr=1;
          MtsSendError(7,PgmId,Tokens[toknum]);
          return;
         }
       Scalar=atof(Tokens[toknum]);
       toknum++;
       if(!(MtsIsNumeric(Tokens[toknum],&NumType)))
         {
          *statusPtr=3;
          MtsSendError(7,PgmId,Tokens[toknum]);
          return;
         }
       MFvalue=atof(Tokens[toknum]);
       if(MFvalue<0||MFvalue>1)
         {
          *statusPtr=5;
          MtsSendError(46,PgmId,Tokens[toknum]);
          return;
         }
       Values[*VcntPtr]=Scalar;
       Members[*VcntPtr]=(float)MFvalue;
       (*VcntPtr)++;
       toknum++;
     }
    return;
  }
