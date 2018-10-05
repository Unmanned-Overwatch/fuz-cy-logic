/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtvrcrs.cpp   Earl Cox  04/01/93 Create a Scalar Variable   |
| A "scalar" is a single valued variable with any allowable   |
| datatype. This procedure allocates and initializes the VDB  |
| but does not hash it into any dictionary.                   |
*-------------------------------------------------------------*/
#include <string.h>
#include "VDB.hpp"
#include <mtsptype.hpp>
VDB *VarCreateScalar(
   char *Varid,int VarType,double Domain[],char *Varvalue,int *statusPtr)
 {
   VDB  *VDBptr;
   *statusPtr=0;
   if(!(VDBptr=new VDB))
     {
      *statusPtr=1;
      return(VDBptr);
     }
   VarInitVDB(VDBptr,statusPtr);
   strcpy(VDBptr->VDBid,  Varid);
   VDBptr->VDBdatatype   =VarType;
   VDBptr->VDBvalue      =Varvalue;
   VDBptr->VDBdomain[0]  =Domain[0];
   VDBptr->VDBdomain[1]  =Domain[1];
   return(VDBptr);
 }
