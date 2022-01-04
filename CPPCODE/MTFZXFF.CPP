/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzxff.cpp   Earl Cox  04/01/93 Find Variable in Fuzzy     |
| Workarea. This procedure looks through the fuzzy working    |
| area to find a specified variable. When found, it returns   |
| a pointer to the FSV as well as a pointer the VariableDescriptor.          |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include "VariableDescriptor.hpp"
#include <FSV.hpp>
#include <XFZYctl.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
FSV *FzyFindFZYctl(char *Varid,VariableDescriptor **VariableDescriptorptr)
 {
  FSV    *FSVptr,*nullFSVptr=NULL;
  int    i;

  for(i=0;i<XFZYctl.XFZYvarcnt;i++)
    {
     FSVptr=XFZYctl.XFZYoutvars[i];
     if(strcmp(FSVptr->FzySVvarid,Varid)==0)
       {
        *VariableDescriptorptr=FSVptr->FzySVvarptr;
        return(FSVptr);
       }
    }
  return(nullFSVptr);
 }
