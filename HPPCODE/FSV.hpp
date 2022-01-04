//--FSV.hpp [EDC Rev 1.0 04/01/93]
//--------------------------------------------------------------

//--------------------------------------------------------------
//
//--The Fuzzy Solution Variable description block. For each
//--output variable in a fuzzy model, we allocate an entry in
//--the fuzzy control block and link in one of these FSV structures.
#ifndef __fsv
#define __fsv
#include "FuzzysetDescriptor.hpp"
#include "VariableDescriptor.hpp"
#include "SystemTypes.hpp"
//--This is the entry node for each solution variable
struct  FSV
  {
   char   FzySVvarid[IDENLEN+1]; /* Name of the Consequent variable   */
   VDB   *FzySVvarptr;           /* Pointer to variable's vdb         */
   long   FzySVupdcnt;           /* Count of fuzzy region updates     */
   int    FzySVdefuzzMethod,     /* Method of defuzzification for vdb */
          FzySVgeometry,         /* Nature of output geometry         */
          FzySVcorrMethod,       /* Correlation Method                */
          FzySVimplMethod;       /* Implication Method                */
   double FzySVresult;           /* Defuzzified result [also in VDB]  */
   float  FzySValfacut;          /* Output space alfa cut (def=0.0)   */
   fdb   *FzySVfdbptr;           /* Pointer to consequent fuzzy set   */
   long   FzySVcntarray[VECMAX]; /* Possibility Density count array   */
  };
#endif
