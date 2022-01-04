/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtfzgtm.cpp   Earl Cox  04/01/93 Get Membership Value       |
| Given a scalar value, this routine returns its membership   |
| in the fuzzy set as well as its location in the vector.     |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <FuzzysetDescriptor.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
float FzyGetMembership(
   FuzzysetDescriptor *FuzzysetDescriptorptr,double Scalar,int *VecPosptr,int *statusPtr)
 {
   double  Lo,Hi,Range;
   float   Alfacut,memgrade;

   *statusPtr=0;
   Alfacut=FuzzysetDescriptorptr->FuzzysetDescriptoralfacut;
   Lo=FuzzysetDescriptorptr->FuzzysetDescriptordomain[0];
   Hi=FuzzysetDescriptorptr->FuzzysetDescriptordomain[1];
//--Now check that the scalar values is within the computational
//--domain of the fuzzy set. If it lies before or after the domain
//--boundaries we return the truth at these extremis points.
   if(Scalar<Lo)
     {
      *VecPosptr=0;
      memgrade=(float)(fabs(FuzzysetDescriptorptr->FuzzysetDescriptorvector[0]));
      if(memgrade<Alfacut) memgrade=0;
      return(memgrade);
     }
   if(Scalar>Hi)
     {
      *VecPosptr=VECMAX-1;
      memgrade=FuzzysetDescriptorptr->FuzzysetDescriptorvector[VECMAX-1];
      if(memgrade<Alfacut) memgrade=0;
      return(memgrade);
     }
   Range=Hi-Lo;
   if(Range==0)
     {
      *statusPtr=1;
      return(0);
     }
   *VecPosptr=(int)(((Scalar-Lo)/Range)*(VECMAX-1));
   memgrade=(float)(fabs(FuzzysetDescriptorptr->FuzzysetDescriptorvector[*VecPosptr]));
   if(memgrade<Alfacut) memgrade=0;
   return(memgrade);
 }
