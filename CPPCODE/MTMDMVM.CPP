/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdmvm.cpp  Earl Cox  04/01/93  Make a Virtual Model.      |
| A "virtual" model is one that is created 'out of thin air'  |
| that is, it doesn't exist in the repository. This type of   |
| service is need for embedded programming.                   |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "MDB.hpp"
#include "PDB.hpp"
#include "XSYSctl.hpp"
#include "mtypes.hpp"
#include "mtsptype.hpp"
MDB *MdlMakeVirtualModel(
   char *Modelid,char *Modeldesc,
    char *Policyid,PDB **PDBptr,int *statusPtr)
 {
  PDB     *tempPDBptr;
  MDB     *MDBptr,*nullMDB=NULL;
  char    *PgmId="mtmdvm";
  char    wrkbuff[120];

  *statusPtr=0;
  if(!(MDBptr=new MDB))
    {
     *statusPtr=1;
     MtsSendError(2,PgmId,Modelid);
     return(nullMDB);
    }
  MdlInitMDB(MDBptr);
  strcpy(MDBptr->MDBid,Modelid);
  strcpy(MDBptr->MDBdesc,Modeldesc);
  strcpy(MDBptr->MDBpolicy,Policyid);
  XSYSctl.XSYScurrMDBptr=MDBptr;
  if(Policyid!=NULL)
    if(!(tempPDBptr=new PDB))
      {
       *statusPtr=1;
       MtsSendError(2,PgmId,Policyid);
       XSYSctl.XSYScurrMDBptr=NULL;
       delete MDBptr;
       return(nullMDB);
      }
  strcpy(tempPDBptr->PDBid,Policyid);
  MdlLinkPDB(tempPDBptr,statusPtr);
  *PDBptr=tempPDBptr;
  strcpy(XSYSctl.XSYSmodel,Modelid);
  strcpy(XSYSctl.XSYSpolicy,Policyid);
  sprintf(wrkbuff,"%s%s%s%s","FMSNote(33): Virtual Model '",Modelid,
   "' Activated with Policy: ",Policyid);
  MtsWritetoLog(SYSLOGFILE,wrkbuff,statusPtr);
  return(MDBptr);
 }
