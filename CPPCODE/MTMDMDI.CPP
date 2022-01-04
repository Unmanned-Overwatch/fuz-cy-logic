/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdmdi.cpp   Earl Cox  04/01/93  Initialize MDB block      |
| This routine initializes the logical description of an      |
| operational model. A model must be initialized before it    |
| can be populated with policies.                             |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "MDB.hpp"
#include   <SystemTypes.hpp>
void MdlInitMDB(ModelDescription *MDBptr)
  {
    int i;
//--Blank out the model and environment identification
//--slots. These will be set as the system starts.
    memset(MDBptr->MDBid,       ' ',IDENLEN);
    memset(MDBptr->MDBdesc,     ' ',DESCLEN);
    memset(MDBptr->MDBpolicy,   ' ',IDENLEN);
    memset(MDBptr->MDBpsw,      ' ',IDENLEN);
    MDBptr->MDBmdltype=  NORMAL;
    MDBptr->MDBprivate=  FALSE;
    MDBptr->MDBdynvars=  TRUE;
    MDBptr->MDBnext=     NULL;
    return;
  }
