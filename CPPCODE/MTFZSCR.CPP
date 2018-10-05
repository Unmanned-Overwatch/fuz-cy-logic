/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzscr.cpp   Earl Cox  04/01/93  Create a new Fuzzy Set    |
| This routine allocates a new fuzzy set block and initializes|
| it with any information passed by the user. We then take the|
| generation type and call the correct fuzzy surface builder. |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stddef.h>
#include <string.h>
#include "FDB.hpp"
#include "fuzzy.hpp"
#include "mtypes.hpp"
#include "mtsptype.hpp"
void Complete_Fuzzyset(const FDB*);
//
FDB* FzyCreateSet(
   char *SetId,int SetType,double Domain[],double Parms[],
    int ParmCnt, int *statusPtr)
  {
    FILE   *mdllog;
    FDB*    FDBptr;
    char   *PgmId="mtfzscr";
    int     i,MaxParms=4;
    float   TruthSeries[128];
    double  Hi,Lo,Center,Width;

    *statusPtr=0;
    FDBptr=NULL;
    Lo=Domain[0];
    Hi=Domain[1];
    if(Lo==0&&Hi==0)
      {
       *statusPtr=1;
       MtsSendError(50,PgmId,SetId);
       return(FDBptr);
      }
    if(Lo>=Hi)
      {
       *statusPtr=1;
       MtsSendError(49,PgmId,SetId);
       return(FDBptr);
      }
//--Create a new fuzzy set and initialize it to the default state
    if(!(FDBptr=new FDB))
      {
       *statusPtr=1;
       MtsSendError(2,PgmId,SetId);
       return(FDBptr);
      }
    FzyInitFDB(FDBptr);
    mdllog=MtsGetSystemFile(SYSMODFILE);
//
//--Now copy in the parameters to complete the general properties
//--of the fuzzy set.
    strcpy(FDBptr->FDBid,SetId);
    FDBptr->FDBgentype=SetType;
    FDBptr->FDBdomain[0]=Domain[0];
    FDBptr->FDBdomain[1]=Domain[1];
//
//--If any of the standard curve types have been specified we
//--create the fuzzy set surface topolgies at this point. At
//--this juncture we do not handle co-ordinate specifications.
    switch(SetType)
     {
      case INCREASE:
       if(ParmCnt!=0)
         {
          Lo=Parms[0];
          Hi=Parms[1];
         }
       FzyLinearCurve(FDBptr,Lo,Hi,INCREASE,statusPtr);
       break;
      case DECREASE:
       if(ParmCnt!=0)
         {
          Lo=Parms[0];
          Hi=Parms[1];
         }
       FzyLinearCurve(FDBptr,Lo,Hi,DECREASE,statusPtr);
       break;
      case DECLINE:
       if(ParmCnt==0) Parms[0]=Lo+((Hi-Lo)/2);
       Center=Parms[0];
       FzySCurve(FDBptr,Lo,Center,Hi,DECLINE,statusPtr);
       break;
      case GROWTH:
       if(ParmCnt==0) Parms[0]=Lo+((Hi-Lo)/2);
       Center=Parms[0];
       FzySCurve(FDBptr,Lo,Center,Hi,GROWTH,statusPtr);
       break;
      case PI:
      case BETA:
       if(ParmCnt==0)
         {
           Parms[1]=(Hi-Lo)/2;
           Parms[0]=Lo+Parms[1];
         }
       Center=Parms[0];
       Width=Parms[1];
       if(SetType==PI)  FzyPiCurve(FDBptr,Center,Width,statusPtr);
          else          FzyBetaCurve(FDBptr,Center,Width,statusPtr);
       break;
      case MEMSERIES:
       for(i=0;i<ParmCnt;i++) TruthSeries[i]=(float)Parms[i];
       FzyMemSeries(FDBptr,TruthSeries,ParmCnt,statusPtr);
       break;
      case EMPTYSET:
       break;
      default:
       *statusPtr=3;
       MtsSendError(35,PgmId,MtsFormatInt(SetType));
       delete FDBptr;
       FDBptr=NULL;
       break;
     }
    Complete_Fuzzyset(FDBptr);
    return(FDBptr);
  }
void Complete_Fuzzyset(const FDB* FDBptr)
 {
  char *SetType[]=
   {
    "Empty",
    "Linear Increasing",
    "Linear Decreasing",
    "Decline S-Curve",
    "Growth S-Curve",
    "PI",
    "Beta",
    "Truth Series",
    "Coordinate Designated"
   };
  int     status;
  char    wrkBuff[180];

  sprintf(wrkBuff,"%s%s%s%s",
     SetType[FDBptr->FDBgentype],
      " FuzzySet '",FDBptr->FDBid,"' created.");
  MtsWritetoLog(SYSMODFILE,wrkBuff,&status);
  return;
 }
