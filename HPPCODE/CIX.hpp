//--CIX.hpp [EDC Rev 1.0 04/01/93]
//--------------------------------------------------------------
//--------------------------------------------------------------
//
//--The Compatibility Index statistics block. We use this
//--block to maintain compatibility information for a series of
//--model runs against the same rule set.
#ifndef __cix
#define __cix
#include "mtypes.hpp"

struct CIX
 {
  char      *CIXmodelid,        /* Name of the active model         */
            *CIXsegmentid,      /* Name of the active segment       */
            *CIXvarid;          /* Name of the output variable      */
  long       CIXruncount;       /* Running count of observations    */
  Ctlswitch  CIXcompType;       /* Type of index generated          */
//--Working storage variables for the compatibility function.
//--For very long runs we must check that double precision floating
//--point overflow does not occur.
  double     CIXCummaxTruth,    /* Cumulative maximum Truth         */
             CIXCumminTruth,    /* Cumulative minimum Truth         */
             CIXCumdeltaTruth,  /* Cumulative delta Truth           */
             CIXCumexpvTruth;   /* Cumulative expected value  Truth */
//--The actual compatibility profile variables. The Average slots
//--are calculated by the FzyStatCompIndex function one each run.
  float      CIXMinTruth,       /* Minimum for Compatibility        */
             CIXMaxTruth,       /* Maximum for Compatibility        */
             CIXAvgmaxTruth,    /* Average maximum Truth            */
             CIXAvgminTruth,    /* Average minimum Truth            */
             CIXAvgdeltaTruth,  /* Average delta Truth              */
             CIXAvgexpvTruth;   /* Average expected value Truth     */
 };
#endif
