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
#include <fdb.hpp>
#include <HDB.hpp>
#include   <mtypes.hpp>
#include   <fuzzy.hpp>
//
//--Access routines for the Fuzzy set Class structure
//
char*  FzySetId(const FDB* FDBptr)        {return((char*)FDBptr->FDBid);}
char*  FzySetDesc(const FDB* FDBptr)      {return((char*)FDBptr->FDBdesc);}
char*  FzySetGenDesc(const FDB *FDBptr)
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
   return(Curves[FDBptr->FDBgentype]);
  }
int    FzySetGentype(const FDB* FDBptr)   {return(FDBptr->FDBgentype);}
bool   FzySetIsEmpty(const FDB* FDBptr)   {return(FDBptr->FDBempty);}
int    FzySetOrder(const FDB* FDBptr)     {return(FDBptr->FDBorder);}
double FzySetLeftEdge(const FDB* FDBptr)  {return(FDBptr->FDBdomain[0]);}
double FzySetRightEdge(const FDB* FDBptr) {return(FDBptr->FDBdomain[1]);}
float  FzySetAlfaCut(const FDB* FDBptr)   {return(FDBptr->FDBalfacut);}
float  FzySetTruth(const FDB* FDBptr,const int i,int *status)
  {
   *status=0;
   if(i<0||i>VECMAX) {*status=1;return((float)0);}
   return(FDBptr->FDBvector[i]);
  }
void   FzySetGetTruthVec(const FDB *FDBptr,double TruthVec[])
  {
    for(int i=0;i<VECMAX;i++) TruthVec[i]=FDBptr->FDBvector[i];
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
