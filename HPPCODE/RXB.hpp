//--RXB.hpp [EDC Rev 1.0 04/01/93]
//--------------------------------------------------------------

//--------------------------------------------------------------
//
//--This is the Rule Explanation Block andis used to
//--hold information abnout how a rule was fired so that we
//--can later invoke the explanatory facilty.
#ifndef __rxb
#define __rxb
#include "FuzzysetDescriptor.hpp"
//
struct RXC
 {
  char   *RXCvarID,       // Name of Variable
         *RXCFuzzysetDescriptorID,       // Name of Fuzzy Set
         *RXChedgeID;     // Name of Hedge(s)
  float   RXCpropTV;      // Truth of this fuzzy proposition
  RXC    *RXCnext;
 };
//
struct RXB                 // Rule Explanation Block
 {
  int     RXBruleno,       // The rule number
          RXBpvarcnt;      // Count of variables in premise
  float   RXBpremiseTV;    // Truth of rule premise
  RXC    *RXBpredhd,       // Head of predicate expressions
         *RXBpredend,      // current end of predicate chain
         *RXBconsptr;      // Pointer to consequent
  RXB    *RXBnext;
 };
#endif
