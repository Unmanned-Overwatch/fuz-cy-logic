/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzihd.cpp  Earl Cox  04/01/93 Insert Default Hedges       |
| This function loads the default hedges into an array of     |
| HDBpointers and is used for basic embedded code modelling   |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <stddef.h>
#include <HDB.hpp>
#include <PDB.hpp>
#include   <mtypes.hpp>
#include <mtsptype.hpp>
void FzyInsertHedges(HDB **HDBarray,int *HdgCnt,int *statusPtr)
 {
  HDB  *HDBptr;
  int   i,Hedgemax=12;
  char *PgmId="mtfzihd";
  char  wrkBuff[80];
  char *HedgeNames[]=
   {
    "about",
    "above",
    "positively",
    "below",
    "vicinity",
    "generally",
    "close",
    "not",
    "somewhat",
    "very",
    "extremely",
    "slightly"
   };

  *statusPtr=0;
  for(i=0;i<Hedgemax;i++)
    {
     if(!(HDBptr=new HDB))
       {
        *statusPtr=1;
        MtsSendError(2,PgmId,HedgeNames[i]);
        return;
       }
     FzyInitHDB(HDBptr);
     strcpy(HDBptr->HDBid,HedgeNames[i]);
     HDBptr->HDBmode  =i+1;
     HDBptr->HDBop    =0;
     HDBptr->HDBvalue =0.0;
     (*HdgCnt)++;
     HDBarray[i]=HDBptr;
    }
  sprintf(wrkBuff,"%s","Default Hedges installed.");
  MtsWritetoLog(SYSMODFILE,wrkBuff,statusPtr);
  return;
 }
