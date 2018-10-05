//--HDB.hpp [EDC Rev 1.0 04/01/93]
//--------------------------------------------------------------

//--------------------------------------------------------------
//
//--The Hedge Descriptor Block. Each built-in and user hedge
//--is defined through one of these nodes. A hedge modifies
//--the shape of a fuzzy set.
#ifndef __hdb
#define __hdb
#include "mtypes.hpp"
struct HDB
  {
    char        HDBid[IDENLEN+1],    /* Identifier name of Hedge     */
                HDBdesc[DESCLEN+1];  /* Description of Hedge         */
    int         HDBmode,             /* n=builtin; 0=user hedge      */
                HDBop;               /* Type of transformer operation*/
    double      HDBvalue;            /* Transformer value of hedge   */
    HDB        *HDBnext;             /* Pointer to next hedge        */
  };
#endif
