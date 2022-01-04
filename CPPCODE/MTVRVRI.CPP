/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtvrvri.cpp   Earl Cox  04/01/93 Initialize a VariableDescriptor block     |
| This routine is called to initialize the variable block     |
| at the indicated address.                                   |
*-------------------------------------------------------------*/
#include <string.h>
#include "VariableDescriptor.hpp"
#include <XSYSctl.hpp>
#include   <SystemTypes.hpp>
#include   <fuzzy.hpp>
#define TraceMax  8
#define FsetMax  16
#define MethMax   4
void VarInitVariableDescriptor(VariableDescriptor *VariableDescriptorptr,int *statusPtr)
 {
  int i;
  *statusPtr=NULL;
  memset(VariableDescriptorptr->VariableDescriptorid,  '\0',IDENLEN+1);
  memset(VariableDescriptorptr->VariableDescriptordesc,'\0',DESCLEN+1);
  VariableDescriptorptr->VariableDescriptorvalue        =NULL;
  VariableDescriptorptr->VariableDescriptordefault      =NULL;
  VariableDescriptorptr->VariableDescriptorprompt       =NULL;
  VariableDescriptorptr->VariableDescriptorvalcnt       =0;
  VariableDescriptorptr->VariableDescriptoralfacut      =XSYSctl.XSYSalfacut;
  VariableDescriptorptr->VariableDescriptordatatype     =REAL;
  VariableDescriptorptr->VariableDescriptororgtype      =SCALAR;
  for(i=0;i<TraceMax;i++)  VariableDescriptorptr->VariableDescriptortrace[i]=0;
  VariableDescriptorptr->VariableDescriptorAlwaysask    =FALSE;
  VariableDescriptorptr->VariableDescriptortruth        =0;
//-------------------------------------------------------------
//--For variables in fuzzy models the following VariableDescriptor slots
//--control the associated fuzzy sets and how the model will
//--process inferencing and defuzzification/
  VariableDescriptorptr->VariableDescriptorfsetcnt        =0;
  VariableDescriptorptr->VariableDescriptordomain[0]      =0.0;
  VariableDescriptorptr->VariableDescriptordomain[1]      =0.0;
  VariableDescriptorptr->VariableDescriptordefuzzmethod   =CENTROID;
  VariableDescriptorptr->VariableDescriptorfzygeometry    =FZYSPACE;
  VariableDescriptorptr->VariableDescriptorfzycorrmethod  =CORRMINIMUM;
  VariableDescriptorptr->VariableDescriptorfzyimplmethod  =MINMAX;
  for(i=0;i<FsetMax;i++)     VariableDescriptorptr->VariableDescriptorfuzzysets[i]=NULL;
  VariableDescriptorptr->VariableDescriptorowner          =NULL;
  VariableDescriptorptr->VariableDescriptornext           =NULL;
  return;
 }
