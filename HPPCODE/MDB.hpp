//--MDB  [EDC Rev 1.0 04/01/93]
//--------------------------------------------------------------

//--------------------------------------------------------------
//
//--The Model Description Block. Each model in the system
//--is described by an MDB. The currently active MDB is linked
//--into the 'xsysctl' control area.
#ifndef __ModelDescription
#define __ModelDescription
#include "SystemTypes.hpp"

struct ModelDescription
  {
   char        MDBid[IDENLEN+1],      /* Name of the model        */
               MDBdesc[DESCLEN+1],    /* Description of model     */
               MDBpolicy[IDENLEN+1],  /* Initial policy name      */
               MDBpsw[IDENLEN+1];     /* Model password           */
   Ctlswitch   MDBmdltype;            /* Type of model            */
   bool        MDBprivate,            /* Is this a private model? */
               MDBdynvars;            /* Allow dynamic variables  */
   ModelDescription        *MDBnext;               /* Pointer to next model    */
  };
#endif
