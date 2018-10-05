/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtvrvri.cpp   Earl Cox  04/01/93 Initialize a VDB block     |
| This routine is called to initialize the variable block     |
| at the indicated address.                                   |
*-------------------------------------------------------------*/
#include <string.h>
#include "VDB.hpp"
#include "XSYSctl.hpp"
#include "mtypes.hpp"
#include "fuzzy.hpp"
#define TraceMax  8
#define FsetMax  16
#define MethMax   4
void VarInitVDB(VDB *VDBptr,int *statusPtr)
 {
  int i;
  *statusPtr=NULL;
  memset(VDBptr->VDBid,  '\0',IDENLEN+1);
  memset(VDBptr->VDBdesc,'\0',DESCLEN+1);
  VDBptr->VDBvalue        =NULL;
  VDBptr->VDBdefault      =NULL;
  VDBptr->VDBprompt       =NULL;
  VDBptr->VDBvalcnt       =0;
  VDBptr->VDBalfacut      =XSYSctl.XSYSalfacut;
  VDBptr->VDBdatatype     =REAL;
  VDBptr->VDBorgtype      =SCALAR;
  for(i=0;i<TraceMax;i++)  VDBptr->VDBtrace[i]=0;
  VDBptr->VDBAlwaysask    =FALSE;
  VDBptr->VDBtruth        =0;
//-------------------------------------------------------------
//--For variables in fuzzy models the following VDB slots
//--control the associated fuzzy sets and how the model will
//--process inferencing and defuzzification/
  VDBptr->VDBfsetcnt        =0;
  VDBptr->VDBdomain[0]      =0.0;
  VDBptr->VDBdomain[1]      =0.0;
  VDBptr->VDBdefuzzmethod   =CENTROID;
  VDBptr->VDBfzygeometry    =FZYSPACE;
  VDBptr->VDBfzycorrmethod  =CORRMINIMUM;
  VDBptr->VDBfzyimplmethod  =MINMAX;
  for(i=0;i<FsetMax;i++)     VDBptr->VDBfuzzysets[i]=NULL;
  VDBptr->VDBowner          =NULL;
  VDBptr->VDBnext           =NULL;
  return;
 }
