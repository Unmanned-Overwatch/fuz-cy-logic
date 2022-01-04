/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtvrcrs.cpp   Earl Cox  04/01/93 Create a Scalar Variable   |
| A "scalar" is a single valued variable with any allowable   |
| datatype. This procedure allocates and initializes the VariableDescriptor  |
| but does not hash it into any dictionary.                   |
*-------------------------------------------------------------*/
#include <string.h>
#include "VariableDescriptor.hpp"
#include <SystemPrototypes.hpp>
VariableDescriptor *VarCreateScalar(
   char *Varid,int VarType,double Domain[],char *Varvalue,int *statusPtr)
 {
   VariableDescriptor  *VariableDescriptorptr;
   *statusPtr=0;
   if(!(VariableDescriptorptr=new VariableDescriptor))
     {
      *statusPtr=1;
      return(VariableDescriptorptr);
     }
   VarInitVariableDescriptor(VariableDescriptorptr,statusPtr);
   strcpy(VariableDescriptorptr->VariableDescriptorid,  Varid);
   VariableDescriptorptr->VariableDescriptordatatype   =VarType;
   VariableDescriptorptr->VariableDescriptorvalue      =Varvalue;
   VariableDescriptorptr->VariableDescriptordomain[0]  =Domain[0];
   VariableDescriptorptr->VariableDescriptordomain[1]  =Domain[1];
   return(VariableDescriptorptr);
 }
