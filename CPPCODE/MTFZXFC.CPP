/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzxfc.cpp   Earl Cox  04/01/93 Close the Fuzzy WorkArea   |
| This procedure closes the fuzzy work area. We also free any |
| fuzzy sets that are allocated in this section.              |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include <XFZYctl.hpp>
#include <FuzzysetDescriptor.hpp>
#include <FSV.hpp>
#include   <SystemTypes.hpp>
#include   <fuzzy.hpp>
#include <SystemPrototypes.hpp>
void FzyCloseFZYctl(int *statusPtr)
 {
  FuzzysetDescriptor  *FuzzysetDescriptorptr;
  FSV  *FSVptr;
  int   i,status;
  char  wrkBuff[80];

  *statusPtr=0;
  for(i=0;i<XFZYctl.XFZYvarcnt;i++)
     {
      FSVptr=XFZYctl.XFZYoutvars[i];
      if(FSVptr!=NULL)
        {
         FuzzysetDescriptorptr=FSVptr->FzySVFuzzysetDescriptorptr;
         if(FuzzysetDescriptorptr!=NULL)
           {
            sprintf(wrkBuff,"%s%s%s",
              "....Releasing '",FuzzysetDescriptorptr->FuzzysetDescriptorid,"'");
            MtsWritetoLog(SYSMODFILE,wrkBuff,&status);
            delete FuzzysetDescriptorptr;
           }
         delete FSVptr;
        }
      XFZYctl.XFZYoutvars[i]=NULL;
     }
 sprintf(wrkBuff,"%s","FMSNote(009): Fuzzy Work Area Closed.");
 MtsWritetoLog(SYSMODFILE,wrkBuff,&status);
 return;
 }
