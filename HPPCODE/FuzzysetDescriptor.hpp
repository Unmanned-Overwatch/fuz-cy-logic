//--FuzzysetDescriptor.hpp [EDC Rev 1.0 04/01/93]
//--------------------------------------------------------------

//--------------------------------------------------------------
//
//--The Fuzzyset Descriptor Block. Each fuzzy set in the system
//--is defined through one FSD. These fuzzy sets are stored as
//--truth vectors with their associated bounding domains.
#ifndef __FuzzysetDescriptor
#define __FuzzysetDescriptor
#include "SystemTypes.hpp"

struct FuzzysetDescriptor
  {
    char        FuzzysetDescriptorid[IDENLEN+1],    /* Identifier name of Fuzzyset  */
                FuzzysetDescriptordesc[DESCLEN+1];  /* Description of Fuzzyset      */
    Ctlswitch   FuzzysetDescriptorgentype;          /* Generator Set type   CPP        */
    bool        FuzzysetDescriptorempty;            /* Is this a populated Fuzzyset?*/
    int         FuzzysetDescriptororder;            /* Order of fuzzy set           */
    domainval   FuzzysetDescriptordomain[2],        /* Lo and Hi edges of the set   */
                FuzzysetDescriptorparms[4];         /* Generation parameters        */
    float       FuzzysetDescriptoralfacut;          /* AlfaCut for this fuzzy set   */
    truthfunc   FuzzysetDescriptorvector;           /* The fuzzy set truth vector   */
    FuzzysetDescriptor        *FuzzysetDescriptornext;             /* Pointer to next fuzzyset     */
  };
#endif
