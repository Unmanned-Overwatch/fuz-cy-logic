//--SSYSctl [EDC Rev 1.0 04/01/93]
//--------------------------------------------------------------

//--------------------------------------------------------------
//
//--The External System Control Area. When a model is opened
//--this external control block holds the internal representation
//--of its high level control, functon, and data structure. It is
//--essential and 'anchor" that allows us to gain addressability
//--into the model and the model's current running status.
//--extents must be prime numbers.)
#include <stdio.h>
#include <stdlib.h>
#include "MDB.hpp"
#include "PDB.hpp"
#include "RXB.hpp"
#include "SystemTypes.hpp"
struct
  {
   char       XSYSmodel[IDENLEN+1],    /* Current model identifier    */
              XSYSpolicy[IDENLEN+1],   /* Currently focused policy    */
              XSYSstart[IDENLEN+1],    /* Model start specification   */
              XSYSdrive[_MAX_DRIVE],   /* Drive for this model        */
              XSYSpath[PATHMAX+1],     /* Path to this model          */
              XSYSconfig[PATHMAX+1],   /* Configuration file name     */
              XSYSowner[IDENLEN+1],    /* Name of model owner         */
              XSYSpassword[WORDLEN+1]; /* Model password              */
   int        XSYSpolldcnt;            /* Count of loaded segments    */
   Ctlswitch  XSYStrace[16],           /* Interactive trace switches  */
              XSYSdebug,               /* Determines depth of debug   */
              XSYSmdltype;             /* How to interpret XSYSstart  */
   bool       XSYSmdlprotect,          /* If YES, makes model readonly*/
              XSYSmdlprivate,          /* A private model             */
              XSYSlogsession,          /* Write to the audit log      */
              XSYSerrmsgs,             /* Display errors at terminal  */
              XSYScasesense,           /* Is model case sensitive     */
              XSYSmdlrunning;          /* Is this model running?      */
   long       XSYSrulecnt,             /* Total fired rules           */
              XSYSvarcnt,              /* Total instantiated variables*/
              XSYSpolcnt,              /* Total performed policies    */
              XSYSiocnt,               /* Total I/O operations        */
              XSYSlinecnt;             /* Total lines executed        */
   float      XSYSalfacut;             /* The global system alfacut   */
   FILE      *XSYSfpErrors,            /* Error diagnostic files      */
             *XSYSfpClientErrors,      /* Client error diagnostics    */
             *XSYSfpSyslog,            /* System log                  */
             *XSYSfpModellog;          /* Model log                   */
   ModelDescription       *XSYScurrMDBptr;          /* Pointer to current Model    */
   PDB       *XSYScurrPDBptr;          /* Pointer to current Policy   */
   RXB       *XSYSexplainptr;          /* Pointer to explanations     */
   PDB       *XSYSpolicies[PDBmax];    /* The policy  dictionary      */
  } XSYSctl;
