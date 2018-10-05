/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtfzdfa.cpp   Earl Cox  04/01/93 Display Fuzzy Work Area    |
| This routine will dump out the contents of the fuzzy work   |
| area at the specified address.                              |
*-------------------------------------------------------------*/
#include <stdio.h>
#include "VDB.hpp"
#include "FDB.hpp"
#include "XFZYctl.hpp"
#include "fuzzy.hpp"
#include "mtypes.hpp"
#include "mtsptype.hpp"
void FzyDisplayFSV(FSV *FSVptr,char *DisplayTitle)
 {
  VDB  *VDBptr;
  FDB  *FDBptr;
  int   status;
  FILE *mdlout;

  if(FSVptr==NULL)
    {
     fprintf(mdlout,"%s\n","Sorry. FSVptr is NULL.");
     return;
    }
  mdlout=MtsGetSystemFile(SYSMODFILE);
  VDBptr=FSVptr->FzySVvarptr;
  FDBptr=FSVptr->FzySVfdbptr;
  fputc('\f',mdlout);
  fputc('\n',mdlout);
  fprintf(mdlout,"%s\n","Fuzzy Model Output Variable Generation Area");
  fprintf(mdlout,"%s\n",DisplayTitle);
  fprintf(mdlout,"%s%s\n",
   "Variable Name..............",FSVptr->FzySVvarid);
  fprintf(mdlout,"%s%8.2d\n",
   "   datatype................",VDBptr->VDBdatatype);
  fprintf(mdlout,"%s%8.2d\n",
   "  Defuzzification..........",FSVptr->FzySVdefuzzMethod);
  fprintf(mdlout,"%s%8.2d\n",
   "  Geometry.................",FSVptr->FzySVgeometry);
  fprintf(mdlout,"%s%8.2d\n",
   "  Implication..............",FSVptr->FzySVimplMethod);
  fprintf(mdlout,"%s%8.2d\n",
   "  Update Count.............",FSVptr->FzySVupdcnt);
  fprintf(mdlout,"%s%8.2f\n",
   "  Alfa Cut.................",FSVptr->FzySValfacut);
  FzyDrawSet(FDBptr,SYSMODFILE,&status);
  fprintf(mdlout,"%s\n",
   "--------------E  N  D      O F     D I S P L A Y--------------");
  return;
 }
