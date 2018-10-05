//--mdltypes.hpp [EDC Rev 1.0 04/01/93]
//--------------------------------------------------------------

//--------------------------------------------------------------
//
//--This is the standard header for all the policies and context
//--blocks in the fuzzy modelling system and contains the definitions
//--used to support the explanatory facility and multiple solution
//--defuzzification.
#ifndef __mdltypes
#define __mdltypes
#include "fuzzy.hpp"
#include "mtypes.hpp"
//
//---------------------------------INCLUDES
//
#include <fdb.hpp>
#include "RXB.hpp"
#include "PDB.hpp"
//
//---------------------------------TABLES
//
static char   *   CorrTypes[] =
  {
    "Minimum",
    "Product",
    "Default"
  };
static char   *   ImplTypes[] =
  {
    "Product Sum",
    "Minimum/Maximum",
    "Average Weighted Space",
    "Bounded Add"
  };
static char   *   DfuzTypes[] =
  {
    "Centroid",
    "Maximum Plateau",
    "Maximum Height",
    "Average of Space",
    "Best Evidence",
    "Least Entropy",
    "Near Edge",
    "  Edge"
  };
static int     DefuzzMethods[]=
   {CENTROID,MAXPLATEAU,MAXIMUM,AVGMAXIMUM,NEAREDGE};
static char   *   DefuzzNames[] =
   {
     "Centroid",
     "Maximum Plateau",
     "Maximum Height",
     "Average of Maximums",
     "Near Edge"
   };
static int MaxDefuzz=5;
//
//---------------------------------EXPANATORY GRAPH
//
static RXB   *RXBhead,*RXBplastptr;
static RXB   *RXBptr;
static RXC   *RXCptr;
static char  *VarDict[32];
static int    VDictCnt,
              VDmax=32,
              pRXBcnt,
              pRXBvaridx[16];
static fdb   *pRXBfdb[16];
static float  pRXBvart[16];
//
//---------------------------------DATA ELEMENTS
//
static PDB       *PDBptr;
static char       wrkBuff[180];
static bool       rulefired[32];
static float      ruletruth[32],
                  predtruth[8],
                  PremiseTruth,
                  fsetheight,
                  sumTruth,
                  avgTruth;
static double     Domain[2],
                  Parms[6];
static int        FDBcnt,
                  Idxpos,
                  dfuzzIX,
                  Firedcnt,
                  Linecnt,
                  thisCorrMethod,
                  thisImplMethod,
                  thisDefuzzMethod;
static const int  FzySetMax=8;
static FILE      *mdlout;
static fdb       *WrkFDBptr,
                 *FDBarray[FzySetMax];
static FSV       *FSVptr;
static HDB       *HDBptr;
static VDB       *VDBptr;
//
//---------------------------------PROTOTYPES
//
void ConcludeRule(fdb*,int*);
void ImplicitELSE(fdb*);
void DisplayRule(int);
//
#endif
