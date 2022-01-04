/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdihd.cpp  Earl Cox  04/01/93 Insert Default Hedges       |
| This function loads the default hedges into the indicated   |
| Policy.                                                     |
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
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
void MdlInsertHedges(PDB *PDBptr,int *HdgCnt,int *statusPtr)
 {
  HDB  *HDBptr;
  int   i,Hedgemax=12;
  char *PgmId="mtmdihd";
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
     HDBptr->HDBmode=i+1;
     HDBptr->HDBop=0;
     HDBptr->HDBvalue=0.0;
     MdlLinkHDB(HDBptr,PDBptr,statusPtr);
     if(*statusPtr!=0) return;
     (*HdgCnt)++;
    }
  sprintf(wrkBuff,"%s%s%s",
   "Default Hedges installed in Policy '",PDBptr->PDBid,"'");
  MtsWritetoLog(SYSMODFILE,wrkBuff,statusPtr);
  return;
 }
