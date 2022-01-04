/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtfzutl.cpp   Earl Cox  04/01/93  This files contains the   |
| general utility methods associated with the FzySet class.   |
| These are grouped here instead of in their own files for    |
| management and maintainability.                             |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <FuzzysetDescriptor.hpp>
#include <HDB.hpp>
#include   <SystemTypes.hpp>
#include   <fuzzy.hpp>
//
//--Access routines for the Fuzzy set Class structure
//
char*  FzySetId(const FuzzysetDescriptor* FuzzysetDescriptorptr)        {return((char*)FuzzysetDescriptorptr->FuzzysetDescriptorid);}
char*  FzySetDesc(const FuzzysetDescriptor* FuzzysetDescriptorptr)      {return((char*)FuzzysetDescriptorptr->FuzzysetDescriptordesc);}
char*  FzySetGenDesc(const FuzzysetDescriptor *FuzzysetDescriptorptr)
  {
   char *Curves[]=
    {
     "empty set",
     "linear increasing",
     "linear decreasing",
     "declining S-curve",
     "growth S-curve",
     "PI curve",
     "beta curve",
     "truth membership series",
     "coordinate series",
     "production transformation",
     "left shoulder trapezoid",
     "right sholder trapazoid",
     "gaussian curve",
     "triangle curve"
    };
   return(Curves[FuzzysetDescriptorptr->FuzzysetDescriptorgentype]);
  }
int    FzySetGentype(const FuzzysetDescriptor* FuzzysetDescriptorptr)   {return(FuzzysetDescriptorptr->FuzzysetDescriptorgentype);}
bool   FzySetIsEmpty(const FuzzysetDescriptor* FuzzysetDescriptorptr)   {return(FuzzysetDescriptorptr->FuzzysetDescriptorempty);}
int    FzySetOrder(const FuzzysetDescriptor* FuzzysetDescriptorptr)     {return(FuzzysetDescriptorptr->FuzzysetDescriptororder);}
double FzySetLeftEdge(const FuzzysetDescriptor* FuzzysetDescriptorptr)  {return(FuzzysetDescriptorptr->FuzzysetDescriptordomain[0]);}
double FzySetRightEdge(const FuzzysetDescriptor* FuzzysetDescriptorptr) {return(FuzzysetDescriptorptr->FuzzysetDescriptordomain[1]);}
float  FzySetAlfaCut(const FuzzysetDescriptor* FuzzysetDescriptorptr)   {return(FuzzysetDescriptorptr->FuzzysetDescriptoralfacut);}
float  FzySetTruth(const FuzzysetDescriptor* FuzzysetDescriptorptr,const int i,int *status)
  {
   *status=0;
   if(i<0||i>VECMAX) {*status=1;return((float)0);}
   return(FuzzysetDescriptorptr->FuzzysetDescriptorvector[i]);
  }
void   FzySetGetTruthVec(const FuzzysetDescriptor *FuzzysetDescriptorptr,double TruthVec[])
  {
    for(int i=0;i<VECMAX;i++) TruthVec[i]=FuzzysetDescriptorptr->FuzzysetDescriptorvector[i];
    return;
  }
//
//--Access routines for the Hedge Class structure
//
char*  FzyHdgId(const HDB* HDBptr)        {return((char*)HDBptr->HDBid);}
char*  FzyHdgDesc(const HDB* HDBptr)      {return((char*)HDBptr->HDBdesc);}
int    FzyHdgmode(const HDB* HDBptr)      {return(HDBptr->HDBmode);}
int    FzyHdgop(const HDB* HDBptr)        {return(HDBptr->HDBop);}
double FzyHdgvalue(const HDB* HDBptr)     {return(HDBptr->HDBvalue);}
