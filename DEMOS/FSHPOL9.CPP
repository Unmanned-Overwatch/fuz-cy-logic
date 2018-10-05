/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| fshpol9.cpp   Earl Cox  04/01/93  The Pricing Model         |
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
#include <fdb.hpp>       // The Fuzzy Set descriptor
#include "HDB.hpp"       // The Hedge descriptor
#include "VDB.hpp"       // A Variable descriptor
#include "XFZYctl.hpp"   // The fuzzy parallel processor work area
#include <XSYSctl.hpp>   // The System control region
#include   <mtypes.hpp>    // System constants and symbolics
#include   <fuzzy.hpp>     // Fuzzy Logic constants and symbolics
#include <mtsptype.hpp>  // Function prototypes
//
float  fshpr9policy(const char **Rules,
   double CompPrice,double Price[],float CIX[],int thisidx,int *statusPtr)
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
  char    *PgmId="fshpol1";
  int      i,
           status,
           Index,
           Idxpos,
           Rulecnt,
           thisCorrMethod,
           thisDefuzzMethod;
  float    fsetheight,CompIdxptr,PremiseTruth,DoM;
  double   NoPrice=0,
           Domain[2],
           Parms[4],
           MfgCosts=12,
           TwiceMfgCosts;
  FILE    *mdlout,*sysout;

  *statusPtr=0;
  prcPDBptr=XSYSctl.XSYScurrPDBptr;
  mdlout=MtsGetSystemFile(SYSMODFILE);
  sysout=MtsGetSystemFile(SYSLOGFILE);
  fprintf(mdlout,"%s\n","Price Estimation Policy Begins....");
  VDBptr=MdlFindVDB("PRICE",prcPDBptr,statusPtr);
  FzyInitFZYctl(statusPtr);
  if(!(FzyAddFZYctl(VDBptr,&PriceFDBptr,&FSVptr,statusPtr)))
    {
     *statusPtr=1;
     MtsSendError(12,PgmId,"PRICE");
     return(0);
    }
  thisCorrMethod  =FSVptr->FzySVimplMethod;
  thisDefuzzMethod=FSVptr->FzySVdefuzzMethod;
//
//--Find the fuzzy sets in the policy dictionary
//
  HiFDBptr=MdlFindFDB("HIGH",           prcPDBptr,statusPtr);
  LoFDBptr=MdlFindFDB("LOW",            prcPDBptr,statusPtr);
//
//--Now create the fuzzy number for around 2*mfgcosts
//
     Domain[0]=16;Domain[1]=36;
     TwiceMfgCosts=2*MfgCosts;
     Parms[0]=TwiceMfgCosts;
     Parms[1]=TwiceMfgCosts*.25;
     amFDBptr=FzyCreateSet("Near.2*MfgCosts",PI,Domain,Parms,2,&status);
     strcpy(amFDBptr->FDBdesc,"Near (Around) Twice MfgCosts");
     // FzyDrawSet(amFDBptr,SYSMODFILE,&status);
//--Now create the fuzzy number for around compprice
     Parms[0]=CompPrice;
     Parms[1]=CompPrice*.15;
     ncFDBptr=FzyCreateSet("Near.CompPrice",PI,Domain,Parms,2,&status);
     strcpy(ncFDBptr->FDBdesc,"Near (Around) Competition Price");
     // FzyDrawSet(ncFDBptr,SYSMODFILE,&status);
//
     wkFDBptr=FzyCreateSet("NULL",EMPTYSET,Domain,Parms,2,&status);
//
//--Find the hedge very in the poilcy dictionary
//
  veryHDBptr=MdlFindHDB("very",prcPDBptr,statusPtr);
  if(veryHDBptr==NULL) printf("very hedge     not found\n");
//
//-----------B E G I N    M O D E L    P R O C E S S I N G-------------
//
  Rulecnt=0;
  fprintf(mdlout,"%s\n","Rule Execution....");
//--Rule 1. Our Price must be High
  fprintf(mdlout,"%s\n",Rules[Rulecnt]);
  FzyUnCondProposition(HiFDBptr,FSVptr);
  // FzyDrawSet(PriceFDBptr,SYSMODFILE,statusPtr);
  Rulecnt++;
//
//--Rule 2. Our Price must be Low
  fprintf(mdlout,"%s\n",Rules[Rulecnt]);
  FzyUnCondProposition(LoFDBptr,FSVptr);
  // FzyDrawSet(PriceFDBptr,SYSMODFILE,statusPtr);
  Rulecnt++;
//
//--Rule 3. Our Price must be around 2*MfgCosts
  fprintf(mdlout,"%s\n",Rules[Rulecnt]);
  FzyUnCondProposition(amFDBptr,FSVptr);
  // FzyDrawSet(PriceFDBptr,SYSMODFILE,statusPtr);
  Rulecnt++;
//
//--Rule 4. If the Competition.price is not very high,
//             then our price should be near the competition.price
//fprintf(mdlout,"%s\n",Rules[Rulecnt]);
//fprintf(mdlout,"%s\n",Rules[Rulecnt+1]);
  FzyInitFDB(wkFDBptr);
//
//--------------Evaluate Predicate of rule-------------------------
//
//--Apply the hedge VERY to the High fuzzy set
  FzyApplyHedge(HiFDBptr,veryHDBptr,wkFDBptr,statusPtr);
  // FzyDrawSet(wkFDBptr,SYSMODFILE,statusPtr);
//--Apply the operator NOT to the hedged fuzzy set
  FzyApplyNOT(ZADEHNOT,0,wkFDBptr,statusPtr);
  // FzyDrawSet(wkFDBptr,SYSMODFILE,statusPtr);
//--computed membership of competiton price in this fuzzy region
  PremiseTruth=FzyGetMembership(wkFDBptr,CompPrice,&Idxpos,statusPtr);
//fprintf(mdlout,"%s%10.2f\n","PremiseTruth= ",PremiseTruth);
//
//--------------Perform consequent proposition---------------------
//
  FzyCondProposition(
     ncFDBptr,FSVptr,thisCorrMethod,PremiseTruth,statusPtr);
  // FzyDrawSet(PriceFDBptr,SYSMODFILE,statusPtr);
//
//--Defuzzify to find expected value for price
//
  FzyCopySet(PriceFDBptr,wkFDBptr,statusPtr);
  Price[0]=FzyDefuzzify(PriceFDBptr,CENTROID,&CompIdxptr,statusPtr);
  CIX[0]  =CompIdxptr;
  FzyCopySet(wkFDBptr,PriceFDBptr,statusPtr);
  Price[1]=FzyDefuzzify(PriceFDBptr,MAXPLATEAU,&CompIdxptr,statusPtr);
  CIX[1]  =CompIdxptr;
//
  fsetheight=FzyGetHeight(PriceFDBptr);
  fprintf(sysout,"\n\n%s%10.2f%s%5.3f%s\n",
  "  CompPrice   = ",CompPrice," [DoM: ",PremiseTruth,"]");
  FzyDrawSet(PriceFDBptr,SYSLOGFILE,statusPtr);
  fprintf(sysout,"%s\n","Model Solution:");
  fprintf(sysout,"%s\n","CENTROID:      ");
  fprintf(sysout,"%s%10.2f\n","  Price       = ",Price[0]    );
  fprintf(sysout,"%s%10.2f\n","  CIX         = ",CIX[0]      );
  fprintf(sysout,"%s\n","MAXIMUM:       ");
  fprintf(sysout,"%s%10.2f\n","  Price       = ",Price[1]    );
  fprintf(sysout,"%s%10.2f\n","  CIX         = ",CIX[1]      );
  fprintf(sysout,"%s%10.2f\n","  SurfaceHght = ",fsetheight  );
//
  FzyCloseFZYctl(statusPtr);
  delete amFDBptr,ncFDBptr,wkFDBptr;
  return(PremiseTruth);
 }
