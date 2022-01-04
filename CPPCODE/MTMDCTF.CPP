/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtmdctf.cpp   Earl Cox  04/01/93  Connect to Fuzzy System   |
| This routine initializes the top level       control block  |
| and must be called before we can use any of the modelling   |
| facilities.                                                 |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <direct.h>
#include <XSYSctl.hpp>
#include   <fuzzy.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
void MdlConnecttoFMS(int *statusPtr)
  {
    int     i,cwditems,maxParts=8;
    char   *outputfn,*inputfn;
    char    wrkBuff[80],cwdBuff[_MAX_DIR];
    char   *cwdParts[8];
    FILE   *outfp,*infp;

    *statusPtr=0;
//--Blank out the model and environment identification
//--slots. These will be set as the system starts.
    memset(XSYSctl.XSYSmodel,   '\0',IDENLEN+1);
    memset(XSYSctl.XSYSpolicy,  '\0',IDENLEN+1);
    memset(XSYSctl.XSYSstart,   '\0',IDENLEN+1);
    memset(XSYSctl.XSYSpath,    '\0',PATHMAX+1);
    memset(XSYSctl.XSYSpath,    '\0',PATHMAX+1);
    memset(XSYSctl.XSYSconfig,  '\0',PATHMAX+1);
    memset(XSYSctl.XSYSowner,   '\0',IDENLEN+1);
    memset(XSYSctl.XSYSpassword,'\0',WORDLEN+1);
    XSYSctl.XSYSpolldcnt=0;
//--Turn off tracing for the model
    for(i=0;i<TRACEMAX;i++) XSYSctl.XSYStrace[i]=0;
    XSYSctl.XSYSdebug=0;
//--Set all the control, integer, and boolean switches
//--to their default values.
    XSYSctl.XSYSmdltype=    SEGMENT;
    XSYSctl.XSYSmdlprotect= FALSE;
    XSYSctl.XSYSmdlprivate= FALSE;
    XSYSctl.XSYSlogsession= TRUE;
    XSYSctl.XSYSerrmsgs=    TRUE;
    XSYSctl.XSYScasesense=  TRUE;
    XSYSctl.XSYSmdlrunning= FALSE;
//--Inialize the statistic counters
    XSYSctl.XSYSrulecnt=  0;
    XSYSctl.XSYSvarcnt=   0;
    XSYSctl.XSYSpolcnt=   0;
    XSYSctl.XSYSiocnt=    0;
    XSYSctl.XSYSlinecnt=  0;
//--Initialize the global alfa cut level
    XSYSctl.XSYSalfacut=  0.0;
//--Initialize the basic file pointers. We open the error
//--diagnostic file to the default path+file. The output files,
//--for the model and system log are also assigned default files.
    inputfn="fmssys.edf";
    if((infp=fopen(inputfn,"rb"))==NULL)
      {
       perror(inputfn);
       *statusPtr=5;
       return;
      }
    XSYSctl.XSYSfpErrors=infp;
    inputfn="client.edf";
    if((infp=fopen(inputfn,"rb"))==NULL)
      {
       perror(inputfn);
       *statusPtr=5;
       return;
      }
    XSYSctl.XSYSfpClientErrors=infp;
    outputfn="B:\\syslog.fil";
    if((outfp=fopen(outputfn,"w"))==NULL)
      {
       perror(outputfn);
       *statusPtr=5;
       return;
      }
    XSYSctl.XSYSfpSyslog=outfp;
    outputfn="B:\\mdllog.fil";

    if((outfp=fopen(outputfn,"w"))==NULL)
      {
       perror(outputfn);
       *statusPtr=7;
       return;
      }
    XSYSctl.XSYSfpModellog=outfp;
//--Initialize the current model and policy pointers
    XSYSctl.XSYScurrMDBptr=NULL;
    XSYSctl.XSYScurrPDBptr=NULL;
//--Initialize global explanation chain head
    XSYSctl.XSYSexplainptr=NULL;
//--Clear the policy dictionary for the current model.
    for(i=0;i<PDBmax;i++) XSYSctl.XSYSpolicies[i]=  NULL;
//
//--We now set up the default operating environment. The 'getcwd'
//--function returns the current working directly along with
//--the drive prefix. We break this down and extract
//--the drive and directory path
    getcwd(cwdBuff,80);
    MtsEntoken(cwdBuff,cwdParts,maxParts,&cwditems,statusPtr);
    strcpy(XSYSctl.XSYSdrive,cwdParts[0]);
    strcpy(XSYSctl.XSYSpath,cwdParts[1]);
    sprintf(wrkBuff,"%s%s%s%s",
       "FMSConnect(1): Working Directory is '",
          cwdParts[0],cwdParts[1],"'");
    MtsWritetoLog(SYSLOGFILE,wrkBuff,statusPtr);
//
    sprintf(wrkBuff,"%s","FMSConnect(2): Connected to FMS.");
    MtsWritetoLog(SYSLOGFILE,wrkBuff,statusPtr);
    return;
  }
