/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| wgt1mod.cpp   Earl Cox  04/01/93  The Monotonic Weight Model|
| (single rule)       This model develops an estimated weight |
| fopr an individual based on a single factor: the person's   |
| height. This shows the flexibility of a single rule fuzzy   |
| model using monotonic (proportional) reasoning.             |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <fdb.hpp>       // The Fuzzy Set descriptor
#include "XFZYctl.hpp"   // The fuzzy parallel processor work area
#include <XSYSctl.hpp>   // The System control region
#include   <mtypes.hpp>    // System constants and symbolics
#include   <fuzzy.hpp>     // Fuzzy Logic constants and symbolics
#include <mtsptype.hpp>  // Function prototypes
//
//--These are the "logical" rules. In the high level fuzzy modelling
//--system we would enter these rules exactly as shown.
static const char *Rules[]=
 {
  "R1   if height is tall then weight is heavy"
 };
static const Rulemax=1;
//
double Weight1Model(double Height,float *PremiseTruth,int *statusPtr)
 {
  FDB     *TallFDBptr,
          *WeightFDBptr,
          *HeavyFDBptr;
  char    *PgmId="Weight1";
  int      i,
           status,
           Index,
           Idxpos,
           Rulecnt;
  double   Weight,
           Domain[2],
           Parms[6];
  FILE    *mdlout;

  mdlout=MtsGetSystemFile(SYSMODFILE);    // Get default model log file
//--Describe the Model Parameters
//
fprintf(mdlout,"%s\n",
  "Fuzzy Weight Estimation Model. (c) 1992 Metus Systems Group.");
fprintf(mdlout,"%s%10.2f\n",
  "Individual Height (feet): ",Height   );
fprintf(mdlout,"%s\n","The Rules:");
for(i=0;i<Rulemax;i++) fprintf(mdlout,"%s\n",Rules[i]);
fputc('\n',mdlout);
//
//--Create the basic fuzzy sets (Hi and Low for Weight)
  Domain[0]=5.0;
  Domain[1]=6.5;
  TallFDBptr=FzyCreateSet("TALL",INCREASE,Domain,Parms,0,statusPtr);
  FzyDrawSet(TallFDBptr,SYSMODFILE,statusPtr);
  Domain[0]=150;
  Domain[1]=240;
  HeavyFDBptr=FzyCreateSet("HEAVY",GROWTH,Domain,Parms,0,statusPtr);
  FzyDrawSet(HeavyFDBptr,SYSMODFILE,statusPtr);
//
//-----------B E G I N    M O D E L    P R O C E S S I N G-------------
//
  Rulecnt=0;
//--Rule 1. If Height is TALL then Weight is HEAVY;
  fprintf(mdlout,"%s\n",Rules[Rulecnt]);
  Weight=FzyMonotonicLogic(
     TallFDBptr,HeavyFDBptr,Height,PremiseTruth,statusPtr);
  fprintf(mdlout,"%s\n","Model Solution:");
  fprintf(mdlout,"%s%10.2f\n","  Height       = ",Height       );
  fprintf(mdlout,"%s%10.2f\n","  Weight       = ",Weight       );
  fprintf(mdlout,"%s%10.6f\n","  Truth Grade = ",*PremiseTruth );
  for(i=0;i<VECMAX;i++)
   if(HeavyFDBptr->FDBvector[i]>*PremiseTruth)
         HeavyFDBptr->FDBvector[i]=*PremiseTruth;
  FzyDrawSet(HeavyFDBptr,SYSMODFILE,statusPtr);
  return(Weight);
 }
