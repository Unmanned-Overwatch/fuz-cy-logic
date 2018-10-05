/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| fshpra1.cpp   Earl Cox  04/01/93  Project Risk Assessment   |
| This is the main model program that calls the policy to     |
| evaluate project risk assessment based on various factors.  |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <fdb.hpp>
#include "SFZYctl.hpp"
#include "SSYSctl.hpp"
#include   <fuzzy.hpp>
#include   <mtypes.hpp>
#include <mtsptype.hpp>
//
//--These are the "logical" rules. In the high level fuzzy modelling
//--system we would enter these rules exactly as shown.
static const char *Rules[]=
 {
  "R1   if project.duration is Long then risk is increased;",
  "R2   if project.staffing is Large then risk is increased;",
  "R3   if project.funding is Low then risk is increased;",
  "R4   if project.priority is High then risk is increased;"
 };
static const Rulemax=4;
extern unsigned _stklen=50000;
double fshpj1policy(const char**,double,double,float*,int*);
void main(void)
 {
  FDB     *ldFDBptr,
          *lsFDBptr,
          *lfFDBptr,
          *hpFDBptr,
          *irFDBptr,
          *hrFDBptr;
  int      i,
           status,
           Idxpos,
           TryCtl[2];
  float    totgrade,
           memgrade,
           totDofRisk;
  double   prjDUR,
           prjSLL,
           prjFUN,
           prjPRI,
           durRisk,
           sllRisk,
           funRisk,
           priRisk,
           cumRisk;

  double   Domain[2],Parms[4];
  FILE    *mdlout;

  MdlConnecttoFMS(&status);
  mdlout=MtsGetSystemFile(SYSMODFILE);
//
//--Create the basic fuzzy sets
//
  Domain[0]=0;Domain[1]=30;
  ldFDBptr=FzyCreateSet("LONG.DURATION",GROWTH  ,Domain,Parms,0,&status);
  strcpy(ldFDBptr->FDBdesc,"Long Duration (in weeks)");
  FzyDrawSet(ldFDBptr,SYSMODFILE,&status);

  Domain[0]=0;Domain[1]=24;
  lsFDBptr=FzyCreateSet("LARGE.STAFFING",INCREASE,Domain,Parms,0,&status);
  strcpy(lsFDBptr->FDBdesc,"Large Staffing");
  FzyDrawSet(lsFDBptr,SYSMODFILE,&status);

  Domain[0]=0;Domain[1]=100;
  lfFDBptr=FzyCreateSet("LOW.FUNDING",DECREASE,Domain,Parms,0,&status);
  strcpy(lfFDBptr->FDBdesc,"Low for Funding");
  FzyDrawSet(lfFDBptr,SYSMODFILE,&status);

  Domain[0]=0;Domain[1]=10;
  hpFDBptr=FzyCreateSet("HIGH.PRIORITY",DECREASE,Domain,Parms,0,&status);
  strcpy(hpFDBptr->FDBdesc,"High for Priority");
  FzyDrawSet(hpFDBptr,SYSMODFILE,&status);

  Domain[0]=0;Domain[1]=1000;
  irFDBptr=FzyCreateSet("INCREASED",GROWTH,Domain,Parms,0,&status);
  for(i=0;i<VECMAX;i++)
     irFDBptr->FDBvector[i]=(float)(pow(irFDBptr->FDBvector[i],1.1));
  strcpy(irFDBptr->FDBdesc,"Increased Risk");
  FzyDrawSet(irFDBptr,SYSMODFILE,&status);

  Domain[0]=0;Domain[1]=5000;
  hrFDBptr=FzyCreateSet("HIGH.RISK",GROWTH,Domain,Parms,0,&status);
  strcpy(hrFDBptr->FDBdesc,"Increased Risk");
  FzyDrawSet(hrFDBptr,SYSMODFILE,&status);

//
//--Prompt for the model Data
//
  TryCtl[0]=8;
  TryCtl[1]=0;

  Domain[0]=0;Domain[1]=30;
  prjDUR=MtsAskforDBL(
    "duration",
    "Enter the duration (in weeks):",
    Domain,TryCtl,&status);
  if(status!=0) return;

  Domain[0]=0;Domain[1]=24;
  prjSLL=MtsAskforDBL(
    "staffing",
    "Enter the staffing load level:",
    Domain,TryCtl,&status);
  if(status!=0) return;

  Domain[0]=0;Domain[1]=100;
  prjFUN=MtsAskforDBL(
    "funding",
    "Enter the funding commitment :",
    Domain,TryCtl,&status);
  if(status!=0) return;

  Domain[0]=0;Domain[1]=10;
  prjPRI=MtsAskforDBL(
    "priority",
    "Enter the project priority   :",
    Domain,TryCtl,&status);
  if(status!=0) return;
//
  fprintf(mdlout,"%s\n%s\n",
    "Fuzzy Project Risk Assessment Model.",
    "      (c) 1992 Metus Systems Group.");
  fprintf(mdlout,"%s%10.2f\n",
    "Duration                : ",prjDUR   );
  fprintf(mdlout,"%s%10.2f\n",
    "Staff Load Level        : ",prjSLL   );
  fprintf(mdlout,"%s%10.2f\n",
    "Funding Commitment      : ",prjFUN   );
  fprintf(mdlout,"%s%10.2f\n",
    "Prioritization          : ",prjPRI   );
//
  fprintf(mdlout,"%s\n","The Rules:");
  for(i=0;i<Rulemax;i++) fprintf(mdlout,"%s\n",Rules[i]);
  fputc('\n',mdlout);

  totgrade=0;
  durRisk=FzyMonotonicLogic(
   ldFDBptr,irFDBptr,prjDUR,&memgrade,&status);
  fprintf(mdlout,"%s%7.2f%s%5.3f%s\n",
    "Duration Risk           : ",durRisk," [",memgrade,"]");
  totgrade+=memgrade;

  sllRisk=FzyMonotonicLogic(
   lsFDBptr,irFDBptr,prjSLL,&memgrade,&status);
  fprintf(mdlout,"%s%7.2f%s%5.3f%s\n",
    "Staffing Risk           : ",sllRisk," [",memgrade,"]");
  totgrade+=memgrade;

  funRisk=FzyMonotonicLogic(
   lfFDBptr,irFDBptr,prjFUN,&memgrade,&status);
  fprintf(mdlout,"%s%7.2f%s%5.3f%s\n",
    "Funding  Risk           : ",funRisk," [",memgrade,"]");
  totgrade+=memgrade;

  priRisk=FzyMonotonicLogic(
   hpFDBptr,irFDBptr,prjPRI,&memgrade,&status);
  fprintf(mdlout,"%s%7.2f%s%5.3f%s\n",
    "Priority Risk           : ",priRisk," [",memgrade,"]");
  totgrade+=memgrade;

  cumRisk=(durRisk+sllRisk+funRisk+priRisk);
  fprintf(mdlout,"%s%7.2f%s%5.3f%s\n",
    "CUMULATIVE Risk         : ",cumRisk," [",totgrade/4,"]");

  totDofRisk=FzyGetMembership(hrFDBptr,cumRisk,&Idxpos,&status);
  fprintf(mdlout,"%s%7.2f\n",
    "Project Risk Assessment : ",totDofRisk*1000);
  return;
 }
//for(i=0;i<VECMAX;i++)
//   ldFDBptr->FDBvector[i]=(float)(pow(ldFDBptr->FDBvector[i],1.8));
