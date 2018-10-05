/*------------------------------------------------------------*



/*-------------------Procedure Description--------------------*
| fshpol4.cpp   Earl Cox  04/01/93  The Pricing Model         |
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
#include "mtsptype.hpp"  // Function prototypes
//
double fshpr4policy(const char **Rules,
   double MfgCosts,double CompPrice,float *CompIdxptr,int *statusPtr)
 {
  PDB     *prcPDBptr;
  FDB     *HiFDBptr,
          *LoFDBptr,
          *amFDBptr,
          *ncFDBptr,
          *PriceFDBptr,
          *FDBarray[8],
          *wkFDBptr;
  HDB     *veryHDBptr;
  VDB     *VDBptr;
  FSV     *FSVptr;
  char    *PgmId="fshpol4";
  int      i,
           FDBcnt,
           status,
           Index,
           Idxpos,
           Rulecnt,
           thisCorrMethod,
           thisDefuzzMethod;
  float    fsetheight;
  double   Price,
           NoPrice=0,
           PremiseTruth;
  FILE    *mdlout;

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
//-----------B E G I N    M O D E L    P R O C E S S I N G-------------
//
  Rulecnt=0;
  fprintf(mdlout,"%s\n","Rule Execution....");
//--Rule 1. If the Competition.price is not very high,
//             then our price should be near the competition.price
  fprintf(mdlout,"%s\n",Rules[Rulecnt]);
  fprintf(mdlout,"%s\n",Rules[Rulecnt+1]);
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
  FDBcnt=2;
  FDBarray[0]=wkFDBptr;
  FDBarray[1]=ncFDBptr;
  FzyPlotVar("",FDBarray,FDBcnt,SYSMODFILE,&status);
  FzyCondProposition(
     ncFDBptr,FSVptr,thisCorrMethod,PremiseTruth,statusPtr);
  FDBcnt=2;
  FDBarray[0]=wkFDBptr;
  FDBarray[1]=PriceFDBptr;
  FzyDrawSet(PriceFDBptr,SYSMODFILE,statusPtr);
//
//--Rule 2. Our Price must be High
  fprintf(mdlout,"%s\n",Rules[Rulecnt]);
  FDBcnt=2;
  FDBarray[0]=HiFDBptr;
  FDBarray[1]=PriceFDBptr;
  FzyPlotVar("",FDBarray,FDBcnt,SYSMODFILE,&status);
  FzyUnCondProposition(HiFDBptr,FSVptr);
  FzyPlotVar("",FDBarray,FDBcnt,SYSMODFILE,&status);
  FzyDrawSet(PriceFDBptr,SYSMODFILE,statusPtr);
  Rulecnt++;
//
//--Rule 3. Our Price must be Low
  fprintf(mdlout,"%s\n",Rules[Rulecnt]);
  FDBcnt=2;
  FDBarray[0]=LoFDBptr;
  FDBarray[1]=PriceFDBptr;
  FzyPlotVar("",FDBarray,FDBcnt,SYSMODFILE,&status);
  FzyUnCondProposition(LoFDBptr,FSVptr);
  FzyPlotVar("",FDBarray,FDBcnt,SYSMODFILE,&status);
  FzyDrawSet(PriceFDBptr,SYSMODFILE,statusPtr);
  Rulecnt++;
//
//--Rule 4. Our Price must be around 2*MfgCosts
  fprintf(mdlout,"%s\n",Rules[Rulecnt]);
  FDBcnt=2;
  FDBarray[0]=amFDBptr;
  FDBarray[1]=PriceFDBptr;
  FzyPlotVar("",FDBarray,FDBcnt,SYSMODFILE,&status);
  FzyUnCondProposition(amFDBptr,FSVptr);
  FzyPlotVar("",FDBarray,FDBcnt,SYSMODFILE,&status);
  FzyDrawSet(PriceFDBptr,SYSMODFILE,statusPtr);
  Rulecnt++;
//
//
//--Defuzzify to find expected value for price
//
  Price=FzyDefuzzify(PriceFDBptr,thisDefuzzMethod,CompIdxptr,statusPtr);
  fsetheight=FzyGetHeight(PriceFDBptr);
  fprintf(mdlout,"%s\n","Model Solution:");
  fprintf(mdlout,"%s%10.2f\n","  Price       = ",Price       );
  fprintf(mdlout,"%s%10.2f\n","  CompIdx     = ",*CompIdxptr );
  fprintf(mdlout,"%s%10.2f\n","  SurfaceHght = ",fsetheight  );
//
  FzyCloseFZYctl(statusPtr);
  return(Price);
 }
