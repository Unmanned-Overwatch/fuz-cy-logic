/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| generrdf.cpp  Earl Cox  04/01/93 FMS Error Compiler         |
| This procedure is used to generate the working system error |
| diagnostic file (fmssys.edf) from the source (fmssys.sel)   |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mtsptype.hpp"
#define RECSIZE 80
static char inrec[RECSIZE+1],outrec[RECSIZE+1];
static char fpPath  [_MAX_PATH];
static char fpDrive [_MAX_DRIVE];
static char fpDir   [_MAX_DIR];
static char fpFName [_MAX_FNAME];
static char fpExt   [_MAX_EXT];

void main(int argc,char **argv)
 {
  int     i,j,status,errClass[100],errIDX,maxclass=100;
  char    thisClass[3],numBuff[4];
  FILE   *infp,*outfp,*logfp;
  char   *inputfn,*outputfn;
  char   *theDate,*theTime,*fmtDate,*fmtTime;
  char    wrkBuff[16];
  int     dhow=5,thow=3;
  long    currDate,currTime;

//
//--Get and format the current data and time.
  theDate=MtsGetDate(wrkBuff,&status);
  theTime=MtsGetTime(&status);
  fmtDate=MtsFormatDate(theDate,dhow,&status);
  fmtTime=MtsFormatTime(theTime,thow,&status);
  currDate=atoi(theDate);
  currTime=atoi(theTime);
//
  switch(argc)
   {
     case 1:
      inputfn="fmssys.sel";
      outputfn="fmssys.edf";
      break;
     case 2:
      _splitpath(argv[1],fpDrive,fpDir,fpFName,fpExt);
      if(stricmp(fpExt,".edf")==0)
        {
         outputfn=argv[1];
         _makepath(fpPath,fpDrive,fpDir,fpFName,".sel");
         inputfn=&fpPath[0];
        }
      else
        {
         inputfn=argv[1];
         _makepath(fpPath,fpDrive,fpDir,fpFName,".edf");
         outputfn=&fpPath[0];
        }
      break;
     case 3:
      inputfn=argv[1];
      outputfn=argv[2];
      break;
     default:
      fprintf(stderr, "%s: extraneous argument\n", argv[3]);
      exit(1);
   }
  if((infp=fopen(inputfn,"r"))==NULL)
    {
      perror(inputfn);
      exit(3);
    }
  if((outfp=fopen(outputfn,"wb"))==NULL)
    {
      perror(outputfn);
      exit(5);
    }
  if((logfp=fopen("fmssys.cel","w"))==NULL)
    {
      perror("fmssys.cel");
      exit(5);
    }
  int reccnt=0;
  for(i=0;i<maxclass;i++) errClass[i]=0;
  fprintf(logfp,"%s%s%s\n",fmtDate," ",fmtTime);
  fprintf(logfp,"%s\n","FMS: Compiled Error Diagnostic File");
  fprintf(logfp,"%s\n",
      "seq# CLnum                    M  E  S  S  A  G  E               ");
  fprintf(logfp,"%s\n",
      "---- ----- -----------------------------------------------------");
  while(fgets(inrec,RECSIZE,infp))
   {
//
//--This section serially numbers each error message within
//--its error class. We can have any class between 0 and 99
    reccnt++;
    memset(thisClass,'\0',3);
    thisClass[0]=inrec[5];
    thisClass[1]=inrec[6];
    errIDX=atoi(thisClass);
    (errClass[errIDX])++;
    sprintf(numBuff,"%03d",errClass[errIDX]);
    inrec[7]=numBuff[0];
    inrec[8]=numBuff[1];
    inrec[9]=numBuff[2];
//
//--Now fix up the current error diagnostic and move it into
//--the output record buffer. We write it out and check for
//--any file I/O error conditions.
    j=strlen(inrec);
    inrec[j-1]='\0';
    strncpy(outrec,inrec,RECSIZE+1);
    fwrite(outrec,RECSIZE,1,outfp);
    if(ferror(outfp))
      {
       perror(outputfn);
       exit(7);
      }
//
//--We also write the updated error diagnostic message to a text
//--log file so that it can be read and used.
    fprintf(logfp,"%s\n",outrec);
   }
  if(ferror(infp))
    {
     perror(inputfn);
     exit(9);
    }
  exit(0);
 }
