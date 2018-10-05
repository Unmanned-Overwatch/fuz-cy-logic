//--VDB.hpp [EDC Rev 1.0 04/01/93]
//--------------------------------------------------------------  

//--------------------------------------------------------------
//
//--The Variable Description Block. each simple variable
//--in the system is described by its own VDB allocated
//--into either the 'xsysctl' dictionary or the dictionary
//--associated with the PDB (Policy Descriptor Block)
#ifndef __vdb
#define __vdb
#include "FDB.hpp"
#include "mtypes.hpp"
struct VDB
 {
  char       VDBid[IDENLEN+1],   /* Variable identifier                */
             VDBdesc[DESCLEN+1]; /* Description (for prompt/explain)   */
  char      *VDBvalue,           /* Pointer to current value           */
            *VDBdefault,         /* Pointer to default string          */
            *VDBprompt;          /* Pointer to prompt string           */
  int        VDBvalcnt,          /* Element count for vector variables */
             VDBfsetcnt,         /* Count of associated fuzzy sets     */
             VDBdefuzzmethod,    /* How variable is defuzzified        */
             VDBfzygeometry,     /* Geometry of output fuzzy region    */
             VDBfzycorrmethod,   /* Correlation method for variable    */
             VDBfzyimplmethod,   /* Implication Method for fuzzy logic */
             VDBfsvslot;         /* Index of the FSV in the work area  */
  float      VDBalfacut;         /* Alfacut associated with variable   */
  double     VDBdomain[2];       /* Domain of the variable             */
  Ctlswitch  VDBdatatype,        /* Type of data for variable          */
             VDBorgtype,         /* Organization of the variable       */
             VDBtrace[8];        /* Autotrace switches                 */
  bool       VDBAlwaysask;       /* Always Ask (no Backward Chaining)  */
  float      VDBtruth;           /* Resolved truth of the variable     */
  FDB       *VDBfuzzysets[16];   /* Associated fuzzy sets              */
  void      *VDBowner;           /* Policy that owns this variable     */
  VDB       *VDBnext;            /* Pointer to next VDB in hash bucket */
 };
#endif
