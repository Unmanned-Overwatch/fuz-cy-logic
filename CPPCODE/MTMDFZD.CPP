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
#include "VariableDescriptor.hpp"
#include <XSYSctl.hpp>
#include <SystemPrototypes.hpp>
void MdlFindFzyDomain(
  char *Varid,double *Hi,double *Lo,int *statusPtr)
 {
   PDB    *PDBptr;
   VariableDescriptor    *VariableDescriptorptr;
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
   if((VariableDescriptorptr=MdlFindVariableDescriptor(Varid,PDBptr,statusPtr))==NULL)
     {
      *statusPtr=3;
      MtsSendError(100,PgmId,Varid);
      return;
     }
   *Lo=VariableDescriptorptr->VariableDescriptordomain[0];
   *Hi=VariableDescriptorptr->VariableDescriptordomain[1];
   return;
 }
