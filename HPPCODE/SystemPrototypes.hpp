//--mtsptype.hpp [EDC Rev 1.0 04/01/93]
//--------------------------------------------------------------

//--------------------------------------------------------------
//
//--The system Prototypes Header contains all the prototype definitions
//--for the system. This is included in any file that calls any of the
//--external procedures used in the system.
#ifndef __SystemPrototypes
#define __SystemPrototypes
#include <stdio.h>
//----Major control blocks and structures
#include "CompatibilityIndex.hpp"
#include "FuzzysetDescriptor.hpp"
#include "FSV.hpp"
#include "HDB.hpp"
#include "MDB.hpp"
#include "NDB.hpp"
#include "RXB.hpp"
#include "PDB.hpp"
#include "VariableDescriptor.hpp"
//----Minor control blocks and structures
#include "toknode.hpp"
#include  "SystemTypes.hpp"
//
//-----------F U Z Z Y   L O G I C   S E R V I C E S------------filename
//
bool    FzyAboveAlfa(truthval,truthval,int);                    //mtfzaba
bool    FzyAddFZYctl(VariableDescriptor*,FuzzysetDescriptor*,FSV**,int*);                    //mtfzxfa
float   FzyAND(float,float);                                    //mtfzzda
void    FzyApplyAlfa(FuzzysetDescriptor* FuzzysetDescriptorptr,const float Alfa,const int AlfaType);            //mtfzapa
FuzzysetDescriptor    *FzyApplyAND(FuzzysetDescriptor*,FuzzysetDescriptor*,int,double,int*);                 //mtfzfsa
void    FzyApplyHedge(const FuzzysetDescriptor*,const HDB*,FuzzysetDescriptor*,int *);        //mtfzaph
void    FzyApplyNOT(int,float,FuzzysetDescriptor*,int*);                       //mtfzapn
FuzzysetDescriptor    *FzyApplyOR(FuzzysetDescriptor*,FuzzysetDescriptor*,int,double,int*);                  //mtfzfso
float   FzyAutoScale(double,double);                            //mtfzasc
void    FzyBetaCurve(FuzzysetDescriptor*,double,double,int*);                  //mtfzbts
void    FzyCloseFZYctl(int *);                                  //mtfzxfc
void    FzyResetFZYctl(int *);                                  //mtfzxfr
float   FzyCompAND(int,double,float,float,int*);                //mtfzcpa
float   FzyCompOR(int,double,float,float,int*);                 //mtfzcpo
void    FzyCondProposition(FuzzysetDescriptor*,FSV*,int,float,int*);           //mtfzcfp
void    FzyCoordSeries(FuzzysetDescriptor*,double[],float[],const int,int*);   //mtfzcds
void    FzyCopySet(const FuzzysetDescriptor*,FuzzysetDescriptor*,int*);                       //mtfzcpy
void    FzyCopyVector(float[],float[],int);                     //mtfzctv
void    FzyCorrAverage(float[],const truthval,int*);            //mtfzcor
void    FzyCorrMinimum(float[],const truthval,int*);            //mtfzcor
void    FzyCorrProduct(float[],const truthval,int*);            //mtfzcor
FuzzysetDescriptor    *FzyCreateSet(char*,int,double[],double[],int,int*);     //mtfzscr
HDB    *FzyCreateHedge(char*,int,double,int*);                  //mtfzhcr
double  FzyDefuzzify(FuzzysetDescriptor*,const int,float*,int*);               //mtfzdfz
bool    FzyDeleteSet(FuzzysetDescriptor*);                                     //mtfzdel
void    FzyDisplayFSV(FSV*,char*);                              //mtfzdfa
void    FzyDisplayMemVector(FuzzysetDescriptor*,float,int*);                   //mtfzdtv
void    FzyDisplayRule(char**,int,int[],int[],int,int*);        //mtfzdrl
void    FzyDrawSet(FuzzysetDescriptor*,int,int*);                              //mtfzdrw
double  FzyEquivalentScalar(FuzzysetDescriptor*,float,int*);                   //mtfzeqs
void    FzyExamineSet(FuzzysetDescriptor*,int*);                               //mtfzexa
void    FzyExtractSetdata(FuzzysetDescriptor*,int,double[],float[],int*,int*); //mtfzesd
FSV    *FzyFindFzyctl(char*,VariableDescriptor**);                             //mtfzxff
void    FzyFindPlateau(FuzzysetDescriptor*,int[],int*,int*);                   //mtfzfpl
FuzzysetDescriptor    *FzyFuzzyScalar(char*,double,int,int*);                  //mtfzfsc
void    FzyGaussianCurve(FuzzysetDescriptor*,double,double,int*);              //mtfzgas
void    FzyGetCoordinates(char*,double[],float[],int*,int*);    //mtfzgcd
float   FzyGetHeight(FuzzysetDescriptor*);                                     //mtfzhgt
int     FzyGetHighPoint(FuzzysetDescriptor*,float*);                           //mtfzfhp
float   FzyGetMembership(FuzzysetDescriptor*,double,int*,int*);                //mtfzgtm
double  FzyGetScalar(const FuzzysetDescriptor*,const int,int*);                //mtfzgts
void    FzyImplMatrix(FuzzysetDescriptor*,FuzzysetDescriptor*,double[],int,int*);             //mtfzimm
void    FzyInitCIX(CompatibilityIndex*);                                       //mtfzcxi
void    FzyInitFZYctl(int *);                                   //mtfzxfi
void    FzyInitHDB(HDB*);                                       //mtfzhdi
void    FzyInitFuzzysetDescriptor(FuzzysetDescriptor*);                                       //mtfzins
void    FzyInitVector(float[],int,float);                       //mtfzinv
void    FzyInsertHedges(HDB**,int*,int*);                       //mtfzihd
void    FzyInterpVec(float[],int *);                            //mtfzipv
bool    FzyIsMemberof(FuzzysetDescriptor*,double,float*,int*);                 //mtfziss
bool    FzyIsNormal(FuzzysetDescriptor*);                                      //mtfzisn
bool    FzyIsNormalType(FuzzysetDescriptor*,int);                              //mtfznrm
void    FzyIsolatePDR(FuzzysetDescriptor*);                                    //mtfzipd
bool    FzyIsUndecidable(FuzzysetDescriptor*);                                 //mtfzudp
void    FzyLinearCurve(FuzzysetDescriptor*,double,double,int,int*);            //mtfzlns
void    FzyMemSeries(FuzzysetDescriptor*,float[],const int,int*);              //mtfzmss
double  FzyMonotonicLogic(FuzzysetDescriptor*,FuzzysetDescriptor*,double,float*,int*);        //mtfzmlg
void    FzyNormalizeSet(FuzzysetDescriptor*);                                  //mtfznml
float   FzyOR(float,float);                                     //mtfzzdo
void    FzyPiCurve(FuzzysetDescriptor*,double,double,int*);                    //mtfzpis
int     FzyPlateauCnt(FuzzysetDescriptor*,float,int*);                         //mtfzplc
void    FzyPlotSets(char*,FuzzysetDescriptor*[],int,int,int*);                  //mtfzpls
void    FzyPlotVar(char*,FuzzysetDescriptor*[],int,int,int*);                   //mtfzplv
void    FzySCurve(FuzzysetDescriptor*,double,double,double,int,int*);          //mtfzscs
void    FzyShoulderedCurve(FuzzysetDescriptor*,int,double,double,int*);        //mtfzsfs
bool    FzyStatCompIndex(FuzzysetDescriptor*,float,CompatibilityIndex*);                      //mtfzscx
void    FzySupportSet(FuzzysetDescriptor*,double[],int[],int*);                //mtfzspt
void    FzyTriangleCurve(FuzzysetDescriptor*,double,double,double,int*);       //mtfztrs
void    FzyTrueSet(FuzzysetDescriptor*);                                       //mtfztru
void    FzyUnCondProposition(FuzzysetDescriptor*,FSV*);                        //mtfzufp
bool    FzyUnitCompIndex(FuzzysetDescriptor*,float,float,float*,float*);       //mtfzucx
void    FzyWgtdBetaCurve(FuzzysetDescriptor*,double,double,double,int*);       //mtfzwbt
char   *FzyXPSacctext(int);                                     //mtfzexs
void    FzyXPSaddRXC(RXB*,RXC*,int,int*);                       //mtfzexs
char   *FzyXPSandtext(void);                                    //mtfzexs
void    FzyXPSconclusion(RXC*,double,double[],float);           //mtfzexs
RXB    *FzyXPScreateRXB(int,int,float);                         //mtfzexs
RXC    *FzyXPScreateRXC(char*,char*,char*,float);               //mtfzexs
char   *FzyXPSdegtext(void);                                    //mtfzexs
void    FzyXPSexplain(RXB*);                                    //mtfzexs
void    FzyXPSInitRXB(RXB*);                                    //mtfzexs
void    FzyXPSInitRXC(RXC*);                                    //mtfzexs
int     FzyXPSinset(float);                                     //mtfzexs
char   *FzyXPSmemtext(float);                                   //mtfzexs
char   *FzyXPSpostext(double);                                  //mtfzexs
char   *FzyXPSprftext(float);                                   //mtfzexs
void    FzyXPSshowrules(RXB*);                                  //mtfzexs
char   *FzyXPSthentext(void);                                   //mtfzexs
//
//----S E L F - R E F E R E N C I N G   F A C I L I T I E S-----filename
//
int     FzyCntANDClass(void);                                   //mtfzcls
int     FzyCntDefuzzMeth(void);                                 //mtfzcls
int     FzyCntHdgs(void);                                       //mtfzcls
int     FzyCntImpMeth(void);                                    //mtfzcls
int     FzyCntORClass(void);                                    //mtfzcls
char   *FzySetId(const FuzzysetDescriptor*);                                   //mtfzutl
char   *FzyIdOfANDClass(int);                                   //mtfzcls
char   *FzyIdOfDfuzzMeth(int);                                  //mtfzcls
char   *FzyIdOfHdgs(int);                                       //mtfzcls
char   *FzyIdOfImpMeth(int);                                    //mtfzcls
char   *FzyIfOfORClass(int);                                    //mtfzcls
void    FzyListANDClass(int[]);                                 //mtfzcls
void    FzyListDefuzzMeth(int[]);                               //mtfzcls
void    FzyListHdgs(int[]);                                     //mtfzcls
void    FzyListImplMeth(int[]);                                 //mtfzcls
void    FzyListORClass(int[]);                                  //mtfzcls
float   FzySetAlfaCut(const FuzzysetDescriptor*);                              //mtfzutl
char   *FzySetDesc(const FuzzysetDescriptor*);                                 //mtfzutl
char   *FzySetGenDesc(const FuzzysetDescriptor*);                              //mtfzutl
int     FzySetGentype(const FuzzysetDescriptor*);                              //mtfzutl
bool    FzySetIsEmpty(const FuzzysetDescriptor*);                              //mtfzutl
double  FzySetLeftEdge(const FuzzysetDescriptor*);                             //mtfzutl
int     FzySetOrder(const FuzzysetDescriptor*);                                //mtfzutl
double  FzySetRightEdge(const FuzzysetDescriptor*);                            //mtfzutl
float   FzySetTruth(const FuzzysetDescriptor*,const int,int*);                 //mtfzutl
char   *MtsLicense(void);                                       //mtmtutl
char   *MtsOwner(void);                                         //mtfzutl
char   *MtsVersion(void);                                       //mtmtutl
//
//-------------------M O D E L L I N G   S E R V I C E S--------filename
//
void    MdlAddNoiseWord(char*,PDB*,int*);                       //mtmdanw
void    MdlClosePolicy(PDB*,long*,int*);                        //mtmdclp
void    MdlConnecttoFMS(int*);                                  //mtmdctf
ModelDescription    *MdlCreateModel(char*,int,int*);                         //mtmdmcr
PDB    *MdlCreatePolicy(char*,int,int*);                        //mtmdpcr
void    MdlFindFzyDomain(char*,double*,double*,int*);           //mtmdfzd
FuzzysetDescriptor    *MdlFindFuzzysetDescriptor(char*,PDB*,int*);                            //mtmdfdf
HDB    *MdlFindHDB(char*,PDB*,int*);                            //mtmdfdh
NDB    *MdlFindNDB(char*,PDB*,int*);                            //mtmdfdn
PDB    *MdlFindPDB(char*,int*);                                 //mtmdfdp
VariableDescriptor    *MdlFindVariableDescriptor(char*,PDB*,int*);                            //mtmdfdv
void    MdlGetcurrentEnvironment(ModelDescription**,PDB**,int*);             //mtmdcen
void    MdlInitMDB(ModelDescription*);                                       //mtmdmdi
void    MdlInitPDB(PDB*);                                       //mtmdpdi
void    MdlInitXSYSctl(int*);                                   //mtmdxsi
void    MdlInsertHedges(PDB*,int*,int*);                        //mtmdihd
void    MdlInsertNWords(PDB*,int*,int*);                        //mtmdinw
void    MdlLinkFuzzysetDescriptor(FuzzysetDescriptor*,PDB*,int*);                             //mtmdlkf
void    MdlLinkHDB(HDB*,PDB*,int*);                             //mtmdlkh
void    MdlLinkMDB(ModelDescription*,bool,int*);                             //mtmdlkm
void    MdlLinkPDB(PDB*,int*);                                  //mtmdlkp
void    MdlLinkVariableDescriptor(VariableDescriptor*,PDB*,int*);                             //mtmdlkv
ModelDescription    *MdlMakeVirtualModel(char*,char*,char*,PDB**,int*);      //mtmdmvm
PDB    *MdlMakeVirtualPolicy(char*,char*,int*);                 //mtmdmvp
void    MdlRemoveFuzzysetDescriptor(char*,PDB*,int*);                          //mtmdrmf
void    MdlRemoveHDB(char*,PDB*,int*);                          //mtmdrmh
void    MdlRemoveNDB(char*,PDB*,int*);                          //mtmdrmn
void    MdlRemoveVariableDescriptor(char*,PDB*,int*);                          //mtmdrmv
void    MdlSetcurrentEnvironment(ModelDescription*,PDB*,int*);               //mtmdcen
void    MdlSetTrace(int,int,int*);                              //mtmdsts
//
//-------------T O O L S   A N D   U T I L I T I E S------------filename
//
void    MtsAppendErrorText(int,const char*);                    //mttlart
bool    MtsAskforBOOL(char*,char*,int[],int*);                  //mttlpmt
double  MtsAskforDBL(char*,char*,double[],int[],int*);          //mttlpmt
long    MtsAskforINT(char*,char*,double[],int[],int*);          //mttlpmt
char   *MtsAskforSTR(char*,char*,int,int[],int*);               //mttlpmt
char   *MtsAskforVAL(char*,char*,char**,int,int,int*,int[],int*);//mttlpmt
void    MtsCenterString(char*,int);                             //mttlcls
unsigned long MtsDisplayCoreLeft(char*,int*);                   //mttldrm
void    MtsDisplayTokens(TokenNode*,char*);                     //mttldtc
void    MtsEntoken(char*,char**,int,int*,int*);                 //mttlprs
double  MtsFactorial(double);                                   //mttlfac
void    MtsFillString(char*,char);                              //mttlfls
int     MtsFindsubstr(char*,char*,int);                         //mttlfss
char   *MtsFormatDate(char*,int,int*);                          //mttlfda
char   *MtsFormatDbl(double,int);                               //mttlfdo
char   *MtsFormatFlt(float,int);                                //mttlffl
char   *MtsFormatLong(long);                                    //mttlfln
char   *MtsFormatInt(int);                                      //mttlfin
char   *MtsFormatTime(char*,int,int*);                          //mttlfti
char   *MtsGetDate(char*,int*);                                 //mttlgtd
char   *MtsGetErrorMsg(int);                                    //mttlgem
char   *MtsGetsubstr(char*,int,int);                            //mttlgss
char   *MtsGetdata(char*,int,int);                              //mttlgda
char   *MtsGetTime(int*);                                       //mttlgtt
FILE   *MtsGetSystemFile(int);                                  //mttlgtf
long    MtsHashString(char*,long);                              //mttlhsh
bool    MtsIsBoolean(char*,int*);                               //mttlisb
bool    MtsIsNumeric(char*,int*);                               //mttlisn
bool    MtsIsPrime(long);                                       //mttlipn
void    MtsLeftJustify(char *);                                 //mttlljf
char   *MtsLogFileName(int);                                    //mttllfn
void    MtsNormalizeKey(char*);                                 //mttlnmk
void    Mtspause(void);                                         //mttlpau
void    MtsPutsubstr(char*,char*,int,int);                      //mttlpss
void    MtsPutdata(char*,char*,int,int);                        //mttlpda
void    Mtsprimes(int,int[],int*,int*);                         //mttlpns
double  MtsRandomNumber(void);                                  //mttlrnd
void    MtsReduceLine(char*,int*);                              //mttlrdl
double  MtsRound(double,int,int*);                              //mttlrou
int     MtsSearchTable(char*,char**,int,int*);                  //mttlgts
void    MtsSendError(int,const char*,const char*);              //mttlerd
void    MtsSendClientError(int,const char*,const char*);        //mttlsce
void    MtsSendWarning(char*,char,char*,int*);                  //mttlswm
int     MtsSerialSearch(char*,const char**,int,int);            //mttlsqs
bool    MtsStartTrace(int,int);                                 //mttltrc
int     MtsStrIndex(char*,char);                                //mttlsix
void    MtsWritetoFile(char*,int,char*,char*,int*);             //mttlwtf
void    MtsWritetoLog(int,char*,int*);                          //mttlwtl
//
//-------------------V A R I A B L E    M A N A G E M E N T-----filename
//
void    VarAttachFuzzysetDescriptor(FuzzysetDescriptor*,VariableDescriptor*,int*);                           //mtvrafd
void    VarInitVariableDescriptor(VariableDescriptor*,int*);                                  //mtvrvri
FuzzysetDescriptor    *VarCreateScalar(char*,int,double[],char*,int*);         //mtvrcrs
//
//------------------End of Prototype Definitions----------------
#endif
