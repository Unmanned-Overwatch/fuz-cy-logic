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
#include <fdb.hpp>       // The Fuzzy Set descriptor
#include "VDB.hpp"       // A Variable descriptor
#include "XFZYctl.hpp"   // The fuzzy parallel processor work area
#include <XSYSctl.hpp>   // The System control region
#include   <mtypes.hpp>    // System constants and symbolics
#include   <fuzzy.hpp>     // Fuzzy Logic constants and symbolics
#include "mdltypes.hpp"
#include <mtsptype.hpp>  // Function prototypes
//
static const char *Rules[]=
 {
  "R1   BackorderAmt must be near ERP            ",
  "R2   if orders are high then backorderAmt must be large"
 };
static const Rulemax=2;
//
double InvModel1(double Orders,float *CompIdxptr,int *statusPtr)
 {
  FDB     *HiFDBptr,
          *LgFDBptr,
          *aeFDBptr,
          *BOAFDBptr;
  VDB     *VDBptr;
  FSV     *FSVptr;
  char    *PgmId="invpol1";
  int      i,
           status,
           Index,
           Idxpos,
           Rulecnt,
           thisCorrMethod,
           thisDefuzzMethod;
  float    fsetheight;
  double   BOAmt,
           Domain[2],
           Parms[6],
           NoBOAmt=0,
           ERP=150;
           PremiseTruth;
  FILE    *mdlout;

  mdlout=MtsGetSystemFile(SYSMODFILE);    // Get default model log file
//--Describe the Model Parameters
//
fprintf(mdlout,"%s\n",
  "Fuzzy WIDGET Inventory Model. (c) 1992  Systems Group.");
fprintf(mdlout,"%s%10.2f\n",
  "[Mean] Quarterly Orders : ",Orders   );
fprintf(mdlout,"%s%10.2f\n",
  "Economic Reorder Point  : ",ERP      );
fprintf(mdlout,"%s\n","The Rules:");
for(i=0;i<Rulemax;i++) fprintf(mdlout,"%s\n",Rules[i]);
fputc('\n',mdlout);
//
//--Initialize the fuzzy modeling environment. We set up the
//--model external control space, create the output fuzzy variable,
//--and add it to the fuzzy control region.
  Domain[0]=0;
  Domain[1]=300;
  VDBptr=VarCreateScalar("BOAmt",REAL,Domain,"0",statusPtr);
  FzyInitFZYctl(statusPtr);
  if(!(FzyAddFZYctl(VDBptr,&BOAFDBptr,&FSVptr,statusPtr)))
    {
     *statusPtr=1;
     MtsSendError(12,PgmId,"BOAmt");
     return(NoBOAmt);
    }
  thisCorrMethod  =FSVptr->FzySVimplMethod;
  thisDefuzzMethod=FSVptr->FzySVdefuzzMethod;
//
//--Hi Orders Fuzzy set
  Domain[0]=90;
  Domain[1]=350;
  HiFDBptr=FzyCreateSet("HIGH.ORDERS",INCREASE,Domain,Parms,0,statusPtr);
//FzyDrawSet(HiFDBptr,SYSMODFILE,statusPtr);
//--Large BOAmt fuzzy set
  Domain[0]=0;
  Domain[1]=300;
  LgFDBptr=FzyCreateSet("LARGE.BOAmt", GROWTH,Domain,Parms,0,statusPtr);
//FzyDrawSet(LgFDBptr,SYSMODFILE,statusPtr);
//--Around the ERP
  Parms[0]=ERP;
  Parms[1]=ERP*.30;
  aeFDBptr=FzyCreateSet("AROUND.ERP", PI    ,Domain,Parms,2,statusPtr);
//FzyDrawSet(aeFDBptr,SYSMODFILE,statusPtr);
//
//-----------B E G I N    M O D E L    P R O C E S S I N G-------------
//
  Rulecnt=0;

// Rule 1--BackorderAmt must be near ERP
  fprintf(mdlout,"%s\n",Rules[Rulecnt]);
  FzyUnCondProposition(aeFDBptr,FSVptr);
  FzyDrawSet(BOAFDBptr,SYSMODFILE,statusPtr);
  Rulecnt++;
// Rule 2--if orders are high then backorderAmt must be large
  fprintf(mdlout,"%s\n",Rules[Rulecnt]);
  PremiseTruth=FzyGetMembership(HiFDBptr,Orders,&Idxpos,statusPtr);
  fprintf(mdlout,"%s%10.2f\n","PremiseTruth= ",PremiseTruth);
  FzyCondProposition(
       LgFDBptr,FSVptr,thisCorrMethod,PremiseTruth,statusPtr);
  FzyDrawSet(BOAFDBptr,SYSMODFILE,statusPtr);
  Rulecnt++;
//
  BOAmt=FzyDefuzzify(BOAFDBptr,thisDefuzzMethod,CompIdxptr,statusPtr);
  fsetheight=FzyGetHeight(BOAFDBptr);
  fprintf(mdlout,"%s\n","Model Solution:");
  fprintf(mdlout,"%s%10.2f\n","  BackOrderAmt= ",BOAmt       );
  fprintf(mdlout,"%s%10.2f\n","  CompIdx     = ",*CompIdxptr );
  fprintf(mdlout,"%s%10.2f\n","  surface hght= ",fsetheight  );
  delete  HiFDBptr,LgFDBptr,aeFDBptr,BOAFDBptr;
  return(BOAmt);
 }
