//--XFZYctl [EDC Rev 1.0 04/01/93]
//--------------------------------------------------------------  

//--------------------------------------------------------------
//
//--The External Fuzzy Logic Control Area. This control area
//--manages the approximate reasoning facilities. We
//--maintain an array of output fuzzy set areas (one is allocated
//--and used for each solution variable.) This block also holds
//--specific information about such controls as defuzzification,
//--geometries, alpha-cuts, and so forth.)
#include "FSV.hpp"
//--This is the actual workarea for the approximate reasoning
//--logic. Each solution variable is allocated a slot.
extern struct
  {
   int        XFZYvarcnt,        /* How many fuzzy output variables   */
              XFZYthisvar;       /* Currently active output variable  */
   FSV       *XFZYoutvars[32];   /* The array of generation variables */
  } XFZYctl;
