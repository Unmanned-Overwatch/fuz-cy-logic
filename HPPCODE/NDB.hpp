//--NDB.hpp [EDC Rev 1/0 04/01/93]
//--------------------------------------------------------------

//--------------------------------------------------------------
//
//--The Noise Word Descriptor Block. This structure is chained into
//--the segment's noise dictionary and holds the words that are
//--ignored by the rule processor.
#ifndef __ndb
#define __ndb
#include "mtypes.hpp"
struct NDB
 {
  char    NDBid[WORDLEN+1];       /* Noise Word identifier           */
  NDB    *NDBnext;                /* Pointer to next noise word      */
 };
#endif
