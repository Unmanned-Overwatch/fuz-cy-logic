/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtfzcls.cpp   Earl Cox  04/01/93  Count and List Procedures |
| These are the service routines that return counts of        |
| basic elements in the fuzzy logic system and the routines   |
| that return the lists of these elements.                    |
*-------------------------------------------------------------*/
#include   <fuzzy.hpp>
#include   <mtypes.hpp>
//--Counting procedures--These procedures are the gateway for DLLs
//--into the fundamental static units of the fuzzy system. The
//--counts do NOT (currently) return information about items stored
//--in the object repository.
int FzyCntANDClass(void)    {return(5);}
int FzyCntORClass(void)     {return(5);}
int FzyCntDefuzzMeth(void)  {return(7);}
int FzyCntHdgs(void)        {return(12);}
int FzyCntImpMeth(void)     {return(3);}
//--Listing and Identification procedures--These procedures return
//--lists of these static elements. The "IdOf" procedures return the
//--character string identification of the item.
void FzyListANDClass(int AndClasses[])
  {
   int i;
   const int AndMax=5;
   int BuiltinAND[] =
    {
        MEANAND,
        PRODUCTAND,
        BOUNDEDAND,
        YAGERAND,
        ZADEHAND
    };
   for(i=0;i<AndMax;i++) AndClasses[i]=BuiltinAND[i];
   return;
  }
char* FzyIdOfANDClass(int AndClass)
  {
   const int AndMax=5;
   char* BuiltinAND[] =
    {
        "MeanAnd",
        "ProductAnd",
        "BoundedAnd",
        "YagerAnd",
        "ZadehAnd"
    };
   if(AndClass<1||AndClass>AndMax) return(" ");
   return(BuiltinAND[AndClass]);
  }
//
//
void FzyListORClass(int OrClasses[])
  {
   int i;
   const int OrMax=5;
   int BuiltinOR[] =
    {
        MEANOR,
        PRODUCTOR,
        BOUNDEDOR,
        YAGEROR,
        ZADEHOR
    };
   for(i=0;i<OrMax;i++) OrClasses[i]=BuiltinOR[i];
   return;
  }
char* FzyIdOfORClass(int OrClass)
  {
   const int OrMax=5;
   char* BuiltinOR[] =
    {
        "MeanOr",
        "ProductOr",
        "BoundedOr",
        "YagerOr",
        "ZadehOr"
    };
   if(OrClass<1||OrClass>OrMax) return(" ");
   return(BuiltinOR[OrClass]);
  }
//
//
void FzyListDefuzzMeth(int DefuzzTypes[])
  {
   int i;
   const int DefuzzMax=7;
   int BuiltinDEFUZZ[] =
    {
        CENTROID,
        MAXIMUM,
        AVGSUPPORT,
        BESTEVIDENCE,
        LEASTENTROPY,
        NEAREDGE,
        FAREDGE
    };
   for(i=0;i<DefuzzMax;i++) DefuzzTypes[i]=BuiltinDEFUZZ[i];
   return;
  }
char* FzyIdOfDefuzzMeth(int DefuzzType)
  {
   const int DefuzzMax=7;
   char* BuiltinDEFUZZ[] =
    {
        "Centroid",
        "Maximum",
        "Average Max",
        "Best Evidence",
        "Least Entropy",
        "Near Edge",
        "  Edge"
    };
   if(DefuzzType<1||DefuzzType>DefuzzMax) return(" ");
   return(BuiltinDEFUZZ[DefuzzType]);
  }
//
//
void FzyListHdgs(int Hedges[])
  {
   int i;
   const int HedgeMax=12;
   int BuiltinHEDGES[] =
    {
         ABOUT,
         ABOVE,
         POSITIVE,
         BELOW,
         VICINITY,
         GENERALLY,
         CLOSE,
         NOT,
         SOMEWHAT,
         VERY,
         EXTREMELY,
         SLIGHTLY
    };
   for(i=0;i<HedgeMax;i++) Hedges[i]=BuiltinHEDGES[i];
   return;
  }
char* FzyIdOfHdgs(int Hedge)
  {
   const int HedgeMax=12;
   char* BuiltinHEDGES[] =
    {
         "About",
         "Above",
         "Positively",
         "Below",
         "Vicinity",
         "Generally",
         "Close",
         "Not",
         "Somewhat",
         "Very",
         "Extremely",
         "Slightly"
    };
   if(Hedge<1||Hedge>HedgeMax) return(" ");
   return(BuiltinHEDGES[Hedge]);
  }
//
//
void FzyListImpMeth(int Methods[])
  {
   int i;
   const int MethodMax=3;
   int BuiltinMETHODS[] =
    {
        PRODUCTSUM,
        MINMAX,
        AVGSPACE
    };
   for(i=0;i<MethodMax;i++) Methods[i]=BuiltinMETHODS[i];
   return;
  }
char* FzyIdOfImpMeth(int Method)
  {
   const int MethodMax=3;
   char* BuiltinMETHODS[] =
    {
        "ProductSum",
        "MinMax",
        "AverageSpace"
    };
   if(Method<1||Method>MethodMax) return(" ");
   return(BuiltinMETHODS[Method]);
  }
