/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzhcr.cpp   Earl Cox  04/01/93  Create a new Hedge        |
| This routine allocates a new hedge HDB block and initializes|
| it with any information passed by the user.                 |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stddef.h>
#include <string.h>
#include "HDB.hpp"
#include   <fuzzy.hpp>
#include   <mtypes.hpp>
#include <mtsptype.hpp>
void Complete_Hedge(const HDB*);
//
HDB* FzyCreateHedge(
   char *HdgeId,int HedgeOp,double Hedgeval,int *statusPtr)
  {
    HDB*    HDBptr;
    char   *PgmId="mtfzhcr";

    *statusPtr=0;
    HDBptr=NULL;
//--Create a new hedge and initialize it to the default state
    if(!(HDBptr=new HDB))
      {
       *statusPtr=1;
       MtsSendError(2,PgmId,HdgeId);
       return(HDBptr);
      }
    FzyInitHDB(HDBptr);
//
//--Now copy in the parameters to complete the general properties
//--of the Hedge
    strcpy(HDBptr->HDBid,HdgeId);
    HDBptr->HDBop     =HedgeOp;
    HDBptr->HDBvalue  =Hedgeval;
    Complete_Hedge(HDBptr);
    return(HDBptr);
  }
void Complete_Hedge(const HDB* HDBptr)
 {
  char *HedgeType[]=
   {
    "Add",
    "Substract",
    "Multiply",
    "Divide",
    "Power"
   };
  int     status;
  char    wrkBuff[180];

  sprintf(wrkBuff,"%s%s%10.3f%s%s%s",
     HedgeType[HDBptr->HDBop-1],
      "(",HDBptr->HDBvalue,
      ")  Hedge '",HDBptr->HDBid,"' created.");
  MtsWritetoLog(SYSMODFILE,wrkBuff,&status);
  return;
 }
