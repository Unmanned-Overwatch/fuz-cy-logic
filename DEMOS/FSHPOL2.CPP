/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| fshpol2.cpp   Earl Cox  04/01/93  The Pricing Model         |
|                                                             |
|--------T H E   F U Z Z Y   P R I C I N G   M O D E L--------|
| See AI Expert, October 1992, "Problem Solving with Fuzzy    |
| Logic" by Earl Cox. This model develops a recommended price |
| for a new product based on such factors as the average high |
| and low price in the market place, the manufacturing costs, |
| and the competiton price. See the Rules[] array for the     |
| logical rules.                                              |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "PDB.hpp"       // The Policy descriptor
#include "FDB.hpp"       // The Fuzzy Set descriptor
#include "HDB.hpp"       // The Hedge descriptor
#include "VDB.hpp"       // A Variable descriptor
#include "XFZYctl.hpp"   // The fuzzy parallel processor work area
#include "XSYSctl.hpp"   // The System control region
#include "mtypes.hpp"    // System constants and symbolics
#include "fuzzy.hpp"     // Fuzzy Logic constants and symbolics
#include "mdltypes.hpp"  // Definitons for the modelling system
#include "mtsptype.hpp"  // Function prototypes
//
//--------static variables used in the policy procedures----------
//
//--These are the "logical" rules. In the high level fuzzy modelling
//--system we would enter these rules exactly as shown.
static const char *Rules[]=
 {
  "R1   our price must be high",
  "R2   our price must be low",
  "R3   our price must be around 2*mfgcosts",
  "R4   if the competition.price is not very high",
  "        then our price must be around the competition.price"
 };
static int Rulecnt=0;
static int Rulemax=4;
//                         R1   R2  R3  R4
static int far RuleIDX[4]={ 0,   1,  2,  3  };
static int far RuleSLN[4]={ 1,   1,  1,  2  };
static char  *PgmId="fshpol2";
//
//
double fshpr2policy(
   double MfgCosts,double CompPrice,float *CIXptr,int *statusPtr)
 {
  PDB     *prcPDBptr;
  FDB     *HiFDBptr,
          *LoFDBptr,
          *amFDBptr,
          *ncFDBptr,
          *PriceFDBptr,
          *wkFDBptr;
  HDB     *veryHDBptr;
  VDB     *VDBptr;
  FSV     *FSVptr;
  int      i,
           status;
  long     Memory;
  float    PriceCIX[8];
  double   Price,
           PriceEXV[8],
           NoPrice=0;

  *statusPtr=0;
  prcPDBptr=XSYSctl.XSYScurrPDBptr;
  mdlout=MtsGetSystemFile(SYSMODFILE);
  fprintf(mdlout,"%s\n","Price Estimation Policy Begins....");
  VDBptr=MdlFindVDB("PRICE",prcPDBptr,statusPtr);
  FzyInitFZYctl(statusPtr);
  if(!(FzyAddFZYctl(VDBptr,&PriceFDBptr,&FSVptr,statusPtr)))
    {
     *statusPtr=1;
     MtsSendError(12,PgmId,"PRICE");
     return(NoPrice);
    }
  thisCorrMethod  =FSVptr->FzySVimplMethod;
  thisDefuzzMethod=FSVptr->FzySVdefuzzMethod;
  fprintf(mdlout,"%s\n","The Rules:");
  for(i=0;i<Rulemax;i++) fprintf(mdlout,"%s\n",Rules[i]);
  fputc('\n',mdlout);
//
//--Find the fuzzy sets in the policy dictionary
//
  HiFDBptr=MdlFindFDB("HIGH",           prcPDBptr,statusPtr);
  LoFDBptr=MdlFindFDB("LOW",            prcPDBptr,statusPtr);
  amFDBptr=MdlFindFDB("Near.2*MfgCosts",prcPDBptr,statusPtr);
  ncFDBptr=MdlFindFDB("Near.CompPrice" ,prcPDBptr,statusPtr);
  wkFDBptr=MdlFindFDB("NULL",           prcPDBptr,statusPtr);
//
//--Find the hedge very in the poilcy dictionary
//
  veryHDBptr=MdlFindHDB("very",prcPDBptr,statusPtr);
//
//--Set up explanatory controls
//
  RXBhead    =NULL;
  RXBplastptr=NULL;
//
//-----------B E G I N    M O D E L    P R O C E S S I N G-------------
//
  Rulecnt     =0;
  Firedcnt    =0;
  PremiseTruth=1.0;
  fprintf(mdlout,"%s\n","Rule Execution....");
//--Rule 1. Our Price must be High
  DisplayRule(Rulecnt);
  FzyUnCondProposition(HiFDBptr,FSVptr);
  ConcludeRule(PriceFDBptr,statusPtr);
  RXCptr=FzyXPScreateRXC("Price","High","",1.0);
  FzyXPSaddRXC(RXBptr,RXCptr,RXCconstype,statusPtr);
  FzyDrawSet(PriceFDBptr,SYSMODFILE,statusPtr);
  Rulecnt++;
//
//--Rule 2. Our Price must be Low
  DisplayRule(Rulecnt);
  FzyUnCondProposition(LoFDBptr,FSVptr);
  ConcludeRule(PriceFDBptr,statusPtr);
  RXCptr=FzyXPScreateRXC("Price","Low","",1.0);
  FzyXPSaddRXC(RXBptr,RXCptr,RXCconstype,statusPtr);
  FzyDrawSet(PriceFDBptr,SYSMODFILE,statusPtr);
  Rulecnt++;
//
//--Rule 3. Our Price must be around 2*MfgCosts
  DisplayRule(Rulecnt);
  FzyUnCondProposition(amFDBptr,FSVptr);
  ConcludeRule(PriceFDBptr,statusPtr);
  RXCptr=FzyXPScreateRXC("Price","Around 2*MfgCosts","",1.0);
  FzyXPSaddRXC(RXBptr,RXCptr,RXCconstype,statusPtr);
  FzyDrawSet(PriceFDBptr,SYSMODFILE,statusPtr);
  Rulecnt++;
//
//--Rule 4. If the Competition.price is not very high,
//             then our price should be near the competition.price
  DisplayRule(Rulecnt);
  FzyInitFDB(wkFDBptr);
//
//--------------Evaluate Predicate of rule-------------------------
//
//--Apply the hedge VERY to the High fuzzy set
  FzyApplyHedge(HiFDBptr,veryHDBptr,wkFDBptr,statusPtr);
  FzyDrawSet(wkFDBptr,SYSMODFILE,statusPtr);
//--Apply the operator NOT to the hedged fuzzy set
  FzyApplyNOT(ZADEHNOT,0,wkFDBptr,statusPtr);
  FzyDrawSet(wkFDBptr,SYSMODFILE,statusPtr);
//--computed membership of competiton price in this fuzzy region
  PremiseTruth=FzyGetMembership(wkFDBptr,CompPrice,&Idxpos,statusPtr);
  fprintf(mdlout,"%s%10.2f\n","PremiseTruth= ",PremiseTruth);
//
//--------------Perform consequent proposition---------------------
//
  FzyCondProposition(
     ncFDBptr,FSVptr,thisCorrMethod,PremiseTruth,statusPtr);
  ConcludeRule(PriceFDBptr,statusPtr);
  RXCptr=FzyXPScreateRXC(
     "CompetitionPrice","High","not very",PremiseTruth);
  FzyXPSaddRXC(RXBptr,RXCptr,RXCpredtype,statusPtr);
  RXCptr=FzyXPScreateRXC(
     "Price","CompetitionPrice","near",PremiseTruth);
  FzyXPSaddRXC(RXBptr,RXCptr,RXCconstype,statusPtr);
  FzyDrawSet(PriceFDBptr,SYSMODFILE,statusPtr);
//
//-----------S O L V E    F O R    M O D E L    S O L U T I O N--------
//
  if(Firedcnt==0)
    {
     *statusPtr=88;
     fprintf(stdout,"%s\n",
      "CFRT Context is UNDECIDED. No Rules Fired!");
     *CIXptr=0.0;
     FzyCloseFZYctl(statusPtr);
     return(0);
    }
//
//--Defuzzify to find expected value for price
//
  printf("..Defuzzifying Result:\n");
  strcpy(PriceFDBptr->FDBdesc,"FINAL Price Estimate");
  FzyDrawSet(PriceFDBptr,SYSMODFILE,statusPtr);
  printf("....Applying Defuzzification Strategies\n");
  dfuzzIX=0;
  for(i=0;i<MaxDefuzz;i++)
   {
    PriceEXV[i]=FzyDefuzzify(
       PriceFDBptr,DefuzzMethods[i],CIXptr,statusPtr);
    PriceCIX[i]=*CIXptr;
    if(thisDefuzzMethod==DefuzzMethods[i]) dfuzzIX=i;
   }
  Rulecnt--;
  fprintf(mdlout,"%s\n","The Rules:");
  sumTruth=0;
  for(i=0;i<Rulemax;i++)
    if(rulefired[i]==TRUE)
      {
       fprintf(mdlout,"%4d%s%7.4f%s%s\n",
          i+1,". ",ruletruth[i]," ",Rules[RuleIDX[i]]);
       sumTruth+=ruletruth[i];
      }
  avgTruth=sumTruth/Firedcnt;
  fprintf(mdlout,"%s\n",     "       ------");
  fprintf(mdlout,"%s%7.4f\n","      ",avgTruth);
  fputc('\n',mdlout);
  fsetheight=FzyGetHeight(PriceFDBptr);
  fprintf(mdlout,"%s\n","-----------------------------------------");
  fprintf(mdlout,"%s\n","Model Solution:");
  for(i=0;i<MaxDefuzz;i++)
   {
    fprintf(mdlout,"%s\n",DefuzzNames[i]);
    fprintf(mdlout,"%s%10.2f\n","  Price      : ",PriceEXV[i]  );
    fprintf(mdlout,"%s%10.2f\n","  CIX        : ",PriceCIX[i]  );
   }
  fprintf(mdlout,"%s\n","-----------------------------------------");
  fprintf(mdlout,"%s%10.2f\n",  "SurfaceHght  : ",fsetheight  );
//
  fprintf(mdlout,"\f\n\n%s\n","EXPLANATIONS:");
  FzyXPSshowrules(RXBhead);
  FzyXPSconclusion(
    RXBhead->RXBconsptr,
    PriceEXV[dfuzzIX],PriceFDBptr->FDBdomain,PriceCIX[dfuzzIX]);
  FzyCloseFZYctl(statusPtr);
  MdlClosePolicy(prcPDBptr,&Memory,statusPtr);
  printf("....Selecting Stated Defuzzification Strategy\n");
  *CIXptr=PriceCIX[dfuzzIX];
  return(PriceEXV[dfuzzIX]);
 }
//
static void ConcludeRule(FDB *PriceFDBptr,int *CondPropstatus)
  {
   char   wrkBuff[128];
   int    status;

   ruletruth[Rulecnt]=PremiseTruth;
   sprintf(wrkBuff,"%s%6.4f","Premise Truth= ",PremiseTruth);
   MtsWritetoLog(SYSMODFILE,wrkBuff,&status);
   if(*CondPropstatus!=RULEBELOWALFA)
     {
      rulefired[Rulecnt]=TRUE;
      FzyDrawSet(PriceFDBptr,SYSMODFILE,&status);
      ++Firedcnt;
     }
   if((RXBptr=FzyXPScreateRXB(Rulecnt+1,0,PremiseTruth))==NULL)
      {
       sprintf(wrkBuff,"%s%4d","RXB for Rule ",Rulecnt);
       MtsSendError(2,PgmId,wrkBuff);
       return;
      }
   if(RXBhead==NULL) RXBhead=RXBptr;
     else            RXBplastptr->RXBnext=RXBptr;
   RXBplastptr=RXBptr;
  }
//
static void DisplayRule(int WhichRule)
 {
  int i,j,k;

  j=RuleIDX[WhichRule];
  k=RuleSLN[WhichRule];
  i=0;
  fprintf(mdlout,"%s\n",
      "   -------------------------------------------------------------");
  for(i=0;i<k;i++,j++)  fprintf(mdlout,"%s\n",Rules[j]);
  return;
 }
