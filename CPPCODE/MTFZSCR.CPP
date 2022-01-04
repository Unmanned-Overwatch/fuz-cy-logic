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
#include <FuzzysetDescriptor.hpp>
#include   <fuzzy.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
void Complete_Fuzzyset(const FuzzysetDescriptor*);
//
FuzzysetDescriptor* FzyCreateSet(
   char *SetId,int SetType,double Domain[],double Parms[],
    int ParmCnt, int *statusPtr)
  {
    FILE   *mdllog;
    FuzzysetDescriptor*    FuzzysetDescriptorptr;
    char   *PgmId="mtfzscr";
    int     i,MaxParms=4;
    float   TruthSeries[128];
    double  Hi,Lo,Center,Width;

    *statusPtr=0;
    FuzzysetDescriptorptr=NULL;
    Lo=Domain[0];
    Hi=Domain[1];
    if(Lo==0&&Hi==0)
      {
       *statusPtr=1;
       MtsSendError(50,PgmId,SetId);
       return(FuzzysetDescriptorptr);
      }
    if(Lo>=Hi)
      {
       *statusPtr=1;
       MtsSendError(49,PgmId,SetId);
       return(FuzzysetDescriptorptr);
      }
//--Create a new fuzzy set and initialize it to the default state
    if(!(FuzzysetDescriptorptr=new FuzzysetDescriptor))
      {
       *statusPtr=1;
       MtsSendError(2,PgmId,SetId);
       return(FuzzysetDescriptorptr);
      }
    FzyInitFuzzysetDescriptor(FuzzysetDescriptorptr);
    mdllog=MtsGetSystemFile(SYSMODFILE);
//
//--Now copy in the parameters to complete the general properties
//--of the fuzzy set.
    strcpy(FuzzysetDescriptorptr->FuzzysetDescriptorid,SetId);
    FuzzysetDescriptorptr->FuzzysetDescriptorgentype=SetType;
    FuzzysetDescriptorptr->FuzzysetDescriptordomain[0]=Domain[0];
    FuzzysetDescriptorptr->FuzzysetDescriptordomain[1]=Domain[1];
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
       FzyLinearCurve(FuzzysetDescriptorptr,Lo,Hi,INCREASE,statusPtr);
       break;
      case DECREASE:
       if(ParmCnt!=0)
         {
          Lo=Parms[0];
          Hi=Parms[1];
         }
       FzyLinearCurve(FuzzysetDescriptorptr,Lo,Hi,DECREASE,statusPtr);
       break;
      case DECLINE:
       if(ParmCnt==0) Parms[0]=Lo+((Hi-Lo)/2);
       Center=Parms[0];
       FzySCurve(FuzzysetDescriptorptr,Lo,Center,Hi,DECLINE,statusPtr);
       break;
      case GROWTH:
       if(ParmCnt==0) Parms[0]=Lo+((Hi-Lo)/2);
       Center=Parms[0];
       FzySCurve(FuzzysetDescriptorptr,Lo,Center,Hi,GROWTH,statusPtr);
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
       if(SetType==PI)  FzyPiCurve(FuzzysetDescriptorptr,Center,Width,statusPtr);
          else          FzyBetaCurve(FuzzysetDescriptorptr,Center,Width,statusPtr);
       break;
      case MEMSERIES:
       for(i=0;i<ParmCnt;i++) TruthSeries[i]=(float)Parms[i];
       FzyMemSeries(FuzzysetDescriptorptr,TruthSeries,ParmCnt,statusPtr);
       break;
      case EMPTYSET:
       break;
      default:
       *statusPtr=3;
       MtsSendError(35,PgmId,MtsFormatInt(SetType));
       delete FuzzysetDescriptorptr;
       FuzzysetDescriptorptr=NULL;
       break;
     }
    Complete_Fuzzyset(FuzzysetDescriptorptr);
    return(FuzzysetDescriptorptr);
  }
void Complete_Fuzzyset(const FuzzysetDescriptor* FuzzysetDescriptorptr)
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
     SetType[FuzzysetDescriptorptr->FuzzysetDescriptorgentype],
      " FuzzySet '",FuzzysetDescriptorptr->FuzzysetDescriptorid,"' created.");
  MtsWritetoLog(SYSMODFILE,wrkBuff,&status);
  return;
 }
