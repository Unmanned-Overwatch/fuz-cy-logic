/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzxfr.cpp   Earl Cox  04/01/93 Reset the Fuzzy WorkArea   |
| This procedure resets the fuzzy work area by setiing the    |
| membership function in the FSV to zeros.                    |
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
void FzyResetFZYctl(int *statusPtr)
 {
  FuzzysetDescriptor  *FuzzysetDescriptorptr;
  FSV  *FSVptr;
  int   i,j,status;
  char  wrkBuff[80];

  *statusPtr=0;
  sprintf(wrkBuff,"%s %5d",
    "FMSNote(012): under-generation sets:",XFZYctl.XFZYvarcnt);
  MtsWritetoLog(SYSMODFILE,wrkBuff,&status);
//
  for(i=0;i<XFZYctl.XFZYvarcnt+1;i++)
     {
      FSVptr=XFZYctl.XFZYoutvars[i];
      if(FSVptr!=NULL)
        {
         FuzzysetDescriptorptr=FSVptr->FzySVFuzzysetDescriptorptr;
         if(FuzzysetDescriptorptr!=NULL)
           {
            sprintf(wrkBuff,"%s%s%s",
              "....Resetting '",FuzzysetDescriptorptr->FuzzysetDescriptorid,"'");
            MtsWritetoLog(SYSMODFILE,wrkBuff,&status);
            for(j=0;j<VECMAX;j++)  FuzzysetDescriptorptr->FuzzysetDescriptorvector[j]=0;
            FuzzysetDescriptorptr->FuzzysetDescriptorempty=TRUE;
           }
        }
     }
 sprintf(wrkBuff,"%s","FMSNote(009): Fuzzy Work Area Reset.");
 MtsWritetoLog(SYSMODFILE,wrkBuff,&status);
 return;
 }
