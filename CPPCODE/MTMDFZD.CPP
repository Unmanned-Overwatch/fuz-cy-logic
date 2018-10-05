/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdfzd.cpp  Earl Cox  04/01/93 Find a Domain for Scalar    |
| This function locates and returns the Hi and Lo domains     |
| for a scalar. We use the domain values for the scalar       |
| fuzzification procedure.                                    |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stddef.h>
#include <PDB.hpp>
#include "VDB.hpp"
#include <XSYSctl.hpp>
#include <mtsptype.hpp>
void MdlFindFzyDomain(
  char *Varid,double *Hi,double *Lo,int *statusPtr)
 {
   PDB    *PDBptr;
   VDB    *VDBptr;
   char   *PgmId="mtmdfzd";

   *statusPtr=0;
   *Hi=0;
   *Lo=100;
   if((PDBptr=XSYSctl.XSYScurrPDBptr)==NULL)
     {
      *statusPtr=1;
      MtsSendError(102,PgmId,Varid);
      return;
     }
   if((VDBptr=MdlFindVDB(Varid,PDBptr,statusPtr))==NULL)
     {
      *statusPtr=3;
      MtsSendError(100,PgmId,Varid);
      return;
     }
   *Lo=VDBptr->VDBdomain[0];
   *Hi=VDBptr->VDBdomain[1];
   return;
 }
