/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| invpol1.cpp   Earl Cox  04/01/93  The Inventory Reorder     |
| Policy (showing use of unconditional fuzzy proposition.)    |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <FuzzysetDescriptor.hpp>       // The Fuzzy Set descriptor
#include "VariableDescriptor.hpp"       // A Variable descriptor
#include "XFZYctl.hpp"   // The fuzzy parallel processor work area
#include <XSYSctl.hpp>   // The System control region
#include   <SystemTypes.hpp>    // System constants and symbolics
#include   <fuzzy.hpp>     // Fuzzy Logic constants and symbolics
#include "mdltypes.hpp"
#include <SystemPrototypes.hpp>  // Function prototypes
//
static const char *Rules[]=
 {
  "R1   BackorderAmt must be near ERP            ",
  "R2   if orders are high then BOAmt must be large",
  "R3   if orders[t]-orders[t-1] is low then BOAmt should be small"
 };
static const Rulemax=2;

double InvModel2(
  double Orders,double prevOrders,float *CIXval,int *statusPtr)
 {
  FuzzysetDescriptor     *HiFuzzysetDescriptorptr,
          *SmFuzzysetDescriptorptr,
          *LgFuzzysetDescriptorptr,
          *CgFuzzysetDescriptorptr,
          *aeFuzzysetDescriptorptr,
          *BOAmtFuzzysetDescriptorptr;
  VariableDescriptor     *VariableDescriptorptr;
  FSV     *FSVptr;
  char    *PgmId="invpol1";
  int      i,
           status,
           Index,
           Idxpos,
           Rulecnt,
           thisCorrMethod,
           thisDefuzzMethod;
  float    fsetheight,BOAmtCIX[8];
  double   BOAmt[8],
           Domain[2],
           Parms[6],
           NoBOAmt=0,
           ERP=150,
           DeltaOrders,
           PremiseTruth;
  FILE    *mdlout;

  mdlout=MtsGetSystemFile(SYSMODFILE);    // Get default model log file
//--Describe the Model Parameters
//
DeltaOrders=Orders-prevOrders;
fprintf(mdlout,"%s\n",
  "Fuzzy WIDGET Inventory Model. (c) 1992  Systems Group.");
fprintf(mdlout,"%s%10.2f\n",
  "[Mean] Quarterly Orders : ",Orders       );
fprintf(mdlout,"%s%10.2f\n",
  "[Mean] Previous  Orders : ",prevOrders   );
fprintf(mdlout,"%s%10.2f\n",
  "[Mean] Change in Orders : ",DeltaOrders  );
fprintf(mdlout,"%s%10.2f\n",
  "Economic Reorder Point  : ",ERP          );
fprintf(mdlout,"%s\n","The Rules:");
for(i=0;i<Rulemax;i++) fprintf(mdlout,"%s\n",Rules[i]);
fputc('\n',mdlout);
//
//--Initialize the fuzzy modeling environment. We set up the
//--model external control space, create the output fuzzy variable,
//--and add it to the fuzzy control region.
  Domain[0]=0;
  Domain[1]=300;
  VariableDescriptorptr=VarCreateScalar("BOAmt",REAL,Domain,"0",statusPtr);
  FzyInitFZYctl(statusPtr);
  if(!(FzyAddFZYctl(VariableDescriptorptr,&BOAmtFuzzysetDescriptorptr,&FSVptr,statusPtr)))
    {
     *statusPtr=1;
     MtsSendError(12,PgmId,"BOAmt");
     return(NoBOAmt);
    }
  strcpy(BOAmtFuzzysetDescriptorptr->FuzzysetDescriptordesc,"Under-Generation Fuzzy Region");
  thisCorrMethod  =FSVptr->FzySVimplMethod;
  thisDefuzzMethod=FSVptr->FzySVdefuzzMethod;
//
//--Hi Orders Fuzzy set
  Domain[0]=90;
  Domain[1]=350;
  HiFuzzysetDescriptorptr=FzyCreateSet("HIGH.ORDERS",INCREASE,Domain,Parms,0,statusPtr);
  FzyDrawSet(HiFuzzysetDescriptorptr,SYSMODFILE,statusPtr);
//--Large BOAmt fuzzy set
  Domain[0]=0;
  Domain[1]=300;
  LgFuzzysetDescriptorptr=FzyCreateSet("LARGE.BOAmt",  GROWTH,Domain,Parms,0,statusPtr);
  SmFuzzysetDescriptorptr=FzyCreateSet("SMALL.ORDERS", DECLINE,Domain,Parms,0,statusPtr);
  FzyDrawSet(LgFuzzysetDescriptorptr,SYSMODFILE,statusPtr);
//--Small Change in Orders
  Domain[0]=prevOrders;
  Domain[1]=Orders*2;
  CgFuzzysetDescriptorptr=FzyCreateSet("LOW.CHANGE", INCREASE,Domain,Parms,0,statusPtr);
  FzyDrawSet(LgFuzzysetDescriptorptr,SYSMODFILE,statusPtr);
//--Around the ERP
  Domain[0]=0;
  Domain[1]=300;
  Parms[0]=ERP;
  Parms[1]=ERP*.30;
  aeFuzzysetDescriptorptr=FzyCreateSet("AROUND.ERP", PI    ,Domain,Parms,2,statusPtr);
  FzyDrawSet(aeFuzzysetDescriptorptr,SYSMODFILE,statusPtr);
//
//-----------B E G I N    M O D E L    P R O C E S S I N G-------------
//
  Rulecnt=0;

// Rule 1--BackorderAmt must be near ERP
  fprintf(mdlout,"%s\n",Rules[Rulecnt]);
  FzyUnCondProposition(aeFuzzysetDescriptorptr,FSVptr);
  ruletruth[Rulecnt]=1.00;
  FzyDrawSet(BOAmtFuzzysetDescriptorptr,SYSMODFILE,statusPtr);
  Rulecnt++;
// Rule 2--if orders are high then backorderAmt must be large
  fprintf(mdlout,"%s\n",Rules[Rulecnt]);
  PremiseTruth=FzyGetMembership(HiFuzzysetDescriptorptr,Orders,&Idxpos,statusPtr);
  fprintf(mdlout,"%s%10.2f\n","PremiseTruth= ",PremiseTruth);
  FzyCondProposition(
       LgFuzzysetDescriptorptr,FSVptr,thisCorrMethod,PremiseTruth,statusPtr);
  ruletruth[Rulecnt]=PremiseTruth;
  FzyDrawSet(BOAmtFuzzysetDescriptorptr,SYSMODFILE,statusPtr);
  Rulecnt++;
// R3--if orders[t]-orders[t-1] are small then BOAmt should be low
  fprintf(mdlout,"%s\n",Rules[Rulecnt]);
  PremiseTruth=FzyGetMembership(CgFuzzysetDescriptorptr,DeltaOrders,&Idxpos,statusPtr);
  fprintf(mdlout,"%s%10.2f\n","PremiseTruth= ",PremiseTruth);
  FzyCondProposition(
       SmFuzzysetDescriptorptr,FSVptr,thisCorrMethod,PremiseTruth,statusPtr);
  ruletruth[Rulecnt]=PremiseTruth;
  FzyDrawSet(BOAmtFuzzysetDescriptorptr,SYSMODFILE,statusPtr);
  Rulecnt++;
//

  printf("..Defuzzifying Result:\n");
  strcpy(BOAmtFuzzysetDescriptorptr->FuzzysetDescriptordesc,"FINAL Financial Risk Tolerance");
  printf("....Examining Defuzzification Strategies\n");
  dfuzzIX=0;
  for(i=0;i<MaxDefuzz;i++)
   {
    BOAmt[i]=FzyDefuzzify(
       BOAmtFuzzysetDescriptorptr,DefuzzMethods[i],CIXval,statusPtr);
    BOAmtCIX[i]=*CIXval;
    if(thisDefuzzMethod==DefuzzMethods[i]) dfuzzIX=i;
   }
  Rulecnt--;
  fprintf(mdlout,"%s\n","The Rules:");
  sumTruth=0;
  for(i=0;i<Rulemax;i++)
    if(rulefired[i]==TRUE)
      {
       fprintf(mdlout,"%4d%s%7.4f%s%s\n",
          i+1,". ",ruletruth[i]," ",Rules[i]);
       sumTruth+=ruletruth[i];
      }
  avgTruth=sumTruth/Firedcnt;
  fprintf(mdlout,"%s\n",     "       ------");
  fprintf(mdlout,"%s%7.4f\n","      ",avgTruth);
  fputc('\n',mdlout);
  fsetheight=FzyGetHeight(BOAmtFuzzysetDescriptorptr);
  fprintf(mdlout,"%s\n","-----------------------------------------");
  fprintf(mdlout,"%s\n","Model Solution:");
  for(i=0;i<MaxDefuzz;i++)
   {
    fprintf(mdlout,"%s\n",DefuzzNames[i]);
    fprintf(mdlout,"%s%10.2f\n","  BOAmt      : ",BOAmt[i]     );
    fprintf(mdlout,"%s%10.2f\n","  CIX        : ",BOAmtCIX[i]  );
   }
  fprintf(mdlout,"%s\n","-----------------------------------------");
  fprintf(mdlout,"%s%10.2f\n",  "SurfaceHght  : ",fsetheight  );
//
  FzyCloseFZYctl(statusPtr);
  delete  HiFuzzysetDescriptorptr,LgFuzzysetDescriptorptr,aeFuzzysetDescriptorptr,BOAmtFuzzysetDescriptorptr;
  printf("....Selecting BEST Defuzzification Strategy\n");
  *CIXval=BOAmtCIX[dfuzzIX];
  return(BOAmt[dfuzzIX]);
 }
