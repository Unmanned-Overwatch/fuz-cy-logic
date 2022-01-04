/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdmcr.cpp  Earl Cox  04/01/93 Create a Model              |
| This procedure allocates and initializes a Model Descriptor |
| Block (PDB) and returns its address.                        |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stddef.h>
#include <string.h>
#include "MDB.hpp"
#include   <mtypes.hpp>
#include <mtsptype.hpp>
void Complete_Model(const ModelDescription*);
ModelDescription *MdlCreateModel(char *Mdlid,int StoreAction,int *statusPtr)
 {
  ModelDescription*    MDBptr;
  char   *PgmId="mtmdpcr";

  *statusPtr=0;
  MDBptr=NULL;
//--Create a new model and initialize it to the default state
  if(!(MDBptr=new ModelDescription))
    {
     *statusPtr=1;
     MtsSendError(2,PgmId,Mdlid);
     return(MDBptr);
    }
   MdlInitMDB(MDBptr);
//
//--Now copy in the parameters to complete the general properties
//--of the Model
    strcpy(MDBptr->MDBid,Mdlid);
    if(StoreAction==MODELADD)   MdlLinkMDB(MDBptr,TRUE,statusPtr);
    Complete_Model(MDBptr);
    return(MDBptr);
  }
void Complete_Model(const ModelDescription* MDBptr)
 {
  int     status;
  char    wrkBuff[180];

  sprintf(wrkBuff,"%s%s%s","Model '",MDBptr->MDBid,"' created.");
  MtsWritetoLog(SYSMODFILE,wrkBuff,&status);
  return;
 }
