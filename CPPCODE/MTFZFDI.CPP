/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzfdi.cpp   Earl Cox  04/01/93  This procedure initializes|
| a fuzzy set. It is called when ever we create a new set     |
| structure.                                                  |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "FDB.hpp"
#include "XSYSctl.hpp"
#include "mtypes.hpp"
#include "fuzzy.hpp"
void FzyInitFDB(FDB* FDBptr)
  {
   int i;
   memset(FDBptr->FDBid,  '\0',IDENLEN);
   memset(FDBptr->FDBdesc,'\0',DESCLEN);
   FDBptr->FDBgentype     = 0;
   FDBptr->FDBempty       = TRUE;
   FDBptr->FDBorder       = 1;
   FDBptr->FDBdomain[0]   = 0;
   FDBptr->FDBdomain[1]   = 0;
   FDBptr->FDBalfacut     = XSYSctl.XSYSalfacut;
   for(i=0;i<PARMMAX;i++) FDBptr->FDBparms[i] =0.0;
   for(i=0;i<VECMAX; i++) FDBptr->FDBvector[i]=0.0;
   FDBptr->FDBnext=NULL;
   return;
  }

