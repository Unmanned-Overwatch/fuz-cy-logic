//--VariableDescriptor.hpp [EDC Rev 1.0 04/01/93]
//--------------------------------------------------------------

//--------------------------------------------------------------
//
//--The Variable Description Block. each simple variable
//--in the system is described by its own VariableDescriptor allocated
//--into either the 'xsysctl' dictionary or the dictionary
//--associated with the PDB (Policy Descriptor Block)
#ifndef __VariableDescriptor
#define __VariableDescriptor
#include "FuzzysetDescriptor.hpp"
#include "SystemTypes.hpp"
struct VariableDescriptor
 {
  char       VariableDescriptorid[IDENLEN+1],   /* Variable identifier                */
             VariableDescriptordesc[DESCLEN+1]; /* Description (for prompt/explain)   */
  char      *VariableDescriptorvalue,           /* Pointer to current value           */
            *VariableDescriptordefault,         /* Pointer to default string          */
            *VariableDescriptorprompt;          /* Pointer to prompt string           */
  int        VariableDescriptorvalcnt,          /* Element count for vector variables */
             VariableDescriptorfsetcnt,         /* Count of associated fuzzy sets     */
             VariableDescriptordefuzzmethod,    /* How variable is defuzzified        */
             VariableDescriptorfzygeometry,     /* Geometry of output fuzzy region    */
             VariableDescriptorfzycorrmethod,   /* Correlation method for variable    */
             VariableDescriptorfzyimplmethod,   /* Implication Method for fuzzy logic */
             VariableDescriptorfsvslot;         /* Index of the FSV in the work area  */
  float      VariableDescriptoralfacut;         /* Alfacut associated with variable   */
  double     VariableDescriptordomain[2];       /* Domain of the variable             */
  Ctlswitch  VariableDescriptordatatype,        /* Type of data for variable          */
             VariableDescriptororgtype,         /* Organization of the variable       */
             VariableDescriptortrace[8];        /* Autotrace switches                 */
  bool       VariableDescriptorAlwaysask;       /* Always Ask (no Backward Chaining)  */
  float      VariableDescriptortruth;           /* Resolved truth of the variable     */
  FuzzysetDescriptor       *VariableDescriptorfuzzysets[16];   /* Associated fuzzy sets              */
  void      *VariableDescriptorowner;           /* Policy that owns this variable     */
  VariableDescriptor       *VariableDescriptornext;            /* Pointer to next VariableDescriptor in hash bucket */
 };
#endif
