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
#include "VariableDescriptor.hpp"
#include "FuzzysetDescriptor.hpp"
#include "HDB.hpp"
#include "NDB.hpp"
#include "SystemTypes.hpp"
struct PDB
 {
  char       PDBid[IDENLEN+1],        // Policy Identifier
             PDBdesc[DESCLEN+1];      // Description
  int        PDBVariableDescriptorcnt,               // Count of variables
             PDBFuzzysetDescriptorcnt,               // Count of fuzzy sets
             PDBhdbcnt,               // Count of hedges
             PDBndbcnt;               // Count of noise words
  VariableDescriptor       *PDBvariables[VariableDescriptormax];    // Variable dictionary for policy
  FuzzysetDescriptor       *PDBfuzzysets[FuzzysetDescriptormax];    // Fuzzyset dictionary
  HDB       *PDBhedges[HDBmax];       // Hedge dictionary
  NDB       *PDBnoise[NDBmax];        // Noise words for this policy
  PDB       *PDBnext;                 // Pointer to next policy
 };
#endif
