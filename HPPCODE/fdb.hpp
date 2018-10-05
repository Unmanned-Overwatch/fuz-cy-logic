//--fdb.hpp [EDC Rev 1.0 04/01/93]
//--------------------------------------------------------------

//--------------------------------------------------------------
//
//--The Fuzzyset Descriptor Block. Each fuzzy set in the system
//--is defined through one FSD. These fuzzy sets are stored as
//--truth vectors with their associated bounding domains.
#ifndef __fdb
#define __fdb
#include "mtypes.hpp"

struct FDB
  {
    char        FDBid[IDENLEN+1],    /* Identifier name of Fuzzyset  */
                FDBdesc[DESCLEN+1];  /* Description of Fuzzyset      */
    Ctlswitch   FDBgentype;          /* Generator Set type   CPP        */
    bool        FDBempty;            /* Is this a populated Fuzzyset?*/
    int         FDBorder;            /* Order of fuzzy set           */
    domainval   FDBdomain[2],        /* Lo and Hi edges of the set   */
                FDBparms[4];         /* Generation parameters        */
    float       FDBalfacut;          /* AlfaCut for this fuzzy set   */
    truthfunc   FDBvector;           /* The fuzzy set truth vector   */
    FDB        *FDBnext;             /* Pointer to next fuzzyset     */
  };
#endif
