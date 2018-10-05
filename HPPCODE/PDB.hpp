//--PDB.hpp [EDC Rev 1/0 04/01/93]
//--------------------------------------------------------------

//--------------------------------------------------------------
//
//--The Policy Description Block. A model can be decomposed into
//--any number of functional policies. A policy in the fuzzy modelling
//--sense is a structure that holds the dictionaries for the segment's
//--knowledge and processing objects.
#ifndef __pdb
#define __pdb
#include "VDB.hpp"
#include "fdb.hpp"
#include "HDB.hpp"
#include "NDB.hpp"
#include "mtypes.hpp"
struct PDB
 {
  char       PDBid[IDENLEN+1],        // Policy Identifier
             PDBdesc[DESCLEN+1];      // Description
  int        PDBvdbcnt,               // Count of variables
             PDBfdbcnt,               // Count of fuzzy sets
             PDBhdbcnt,               // Count of hedges
             PDBndbcnt;               // Count of noise words
  VDB       *PDBvariables[VDBmax];    // Variable dictionary for policy
  fdb       *PDBfuzzysets[FDBmax];    // Fuzzyset dictionary
  HDB       *PDBhedges[HDBmax];       // Hedge dictionary
  NDB       *PDBnoise[NDBmax];        // Noise words for this policy
  PDB       *PDBnext;                 // Pointer to next policy
 };
#endif
