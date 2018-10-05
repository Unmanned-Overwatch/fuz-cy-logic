//--mtsptype.hpp [EDC Rev 1.0 04/01/93]
//--------------------------------------------------------------

//--------------------------------------------------------------
//
//--The system Prototypes Header contains all the prototype definitions
//--for the system. This is included in any file that calls any of the
//--external procedures used in the system.
#ifndef __mtsptype
#define __mtsptype
#include <stdio.h>
//----Major control blocks and structures
#include "CIX.hpp"
#include "fdb.hpp"
#include "FSV.hpp"
#include "HDB.hpp"
#include "MDB.hpp"
#include "NDB.hpp"
#include "RXB.hpp"
#include "PDB.hpp"
#include "VDB.hpp"
//----Minor control blocks and structures
#include "toknode.hpp"
#include   <mtypes.hpp>
//
//-----------F U Z Z Y   L O G I C   S E R V I C E S------------filename
//
bool    FzyAboveAlfa(truthval,truthval,int);                    //mtfzaba
bool    FzyAddFZYctl(VDB*,fdb**,FSV**,int*);                    //mtfzxfa
float   FzyAND(float,float);                                    //mtfzzda
void    FzyApplyAlfa(fdb*,const truthval,const int);            //mtfzapa
fdb    *FzyApplyAND(fdb*,fdb*,int,double,int*);                 //mtfzfsa
void    FzyApplyHedge(const fdb*,const HDB*,fdb*,int *);        //mtfzaph
void    FzyApplyNOT(int,float,fdb*,int*);                       //mtfzapn
fdb    *FzyApplyOR(fdb*,fdb*,int,double,int*);                  //mtfzfso
float   FzyAutoScale(double,double);                            //mtfzasc
void    FzyBetaCurve(fdb*,double,double,int*);                  //mtfzbts
void    FzyCloseFZYctl(int *);                                  //mtfzxfc
void    FzyResetFZYctl(int *);                                  //mtfzxfr
float   FzyCompAND(int,double,float,float,int*);                //mtfzcpa
float   FzyCompOR(int,double,float,float,int*);                 //mtfzcpo
void    FzyCondProposition(fdb*,FSV*,int,float,int*);           //mtfzcfp
void    FzyCoordSeries(fdb*,double[],float[],const int,int*);   //mtfzcds
void    FzyCopySet(const fdb*,fdb*,int*);                       //mtfzcpy
void    FzyCopyVector(float[],float[],int);                     //mtfzctv
void    FzyCorrAverage(float[],const truthval,int*);            //mtfzcor
void    FzyCorrMinimum(float[],const truthval,int*);            //mtfzcor
void    FzyCorrProduct(float[],const truthval,int*);            //mtfzcor
fdb    *FzyCreateSet(char*,int,double[],double[],int,int*);     //mtfzscr
HDB    *FzyCreateHedge(char*,int,double,int*);                  //mtfzhcr
double  FzyDefuzzify(fdb*,const int,float*,int*);               //mtfzdfz
bool    FzyDeleteSet(fdb*);                                     //mtfzdel
void    FzyDisplayFSV(FSV*,char*);                              //mtfzdfa
void    FzyDisplayMemVector(fdb*,float,int*);                   //mtfzdtv
void    FzyDisplayRule(char**,int,int[],int[],int,int*);        //mtfzdrl
void    FzyDrawSet(fdb*,int,int*);                              //mtfzdrw
double  FzyEquivalentScalar(fdb*,float,int*);                   //mtfzeqs
void    FzyExamineSet(fdb*,int*);                               //mtfzexa
void    FzyExtractSetdata(fdb*,int,double[],float[],int*,int*); //mtfzesd
FSV    *FzyFindFzyctl(char*,VDB**);                             //mtfzxff
void    FzyFindPlateau(fdb*,int[],int*,int*);                   //mtfzfpl
fdb    *FzyFuzzyScalar(char*,double,int,int*);                  //mtfzfsc
void    FzyGaussianCurve(fdb*,double,double,int*);              //mtfzgas
void    FzyGetCoordinates(char*,double[],float[],int*,int*);    //mtfzgcd
float   FzyGetHeight(fdb*);                                     //mtfzhgt
int     FzyGetHighPoint(fdb*,float*);                           //mtfzfhp
float   FzyGetMembership(fdb*,double,int*,int*);                //mtfzgtm
double  FzyGetScalar(const fdb*,const int,int*);                //mtfzgts
void    FzyImplMatrix(fdb*,fdb*,double[],int,int*);             //mtfzimm
void    FzyInitCIX(CIX*);                                       //mtfzcxi
void    FzyInitFZYctl(int *);                                   //mtfzxfi
void    FzyInitHDB(HDB*);                                       //mtfzhdi
void    FzyInitFDB(fdb*);                                       //mtfzins
void    FzyInitVector(float[],int,float);                       //mtfzinv
void    FzyInsertHedges(HDB**,int*,int*);                       //mtfzihd
void    FzyInterpVec(float[],int *);                            //mtfzipv
bool    FzyIsMemberof(fdb*,double,float*,int*);                 //mtfziss
bool    FzyIsNormal(fdb*);                                      //mtfzisn
bool    FzyIsNormalType(fdb*,int);                              //mtfznrm
void    FzyIsolatePDR(fdb*);                                    //mtfzipd
bool    FzyIsUndecidable(fdb*);                                 //mtfzudp
void    FzyLinearCurve(fdb*,double,double,int,int*);            //mtfzlns
void    FzyMemSeries(fdb*,float[],const int,int*);              //mtfzmss
double  FzyMonotonicLogic(fdb*,fdb*,double,float*,int*);        //mtfzmlg
void    FzyNormalizeSet(fdb*);                                  //mtfznml
float   FzyOR(float,float);                                     //mtfzzdo
void    FzyPiCurve(fdb*,double,double,int*);                    //mtfzpis
int     FzyPlateauCnt(fdb*,float,int*);                         //mtfzplc
void    FzyPlotSets(char*,fdb*[],int,int,int*);                  //mtfzpls
void    FzyPlotVar(char*,fdb*[],int,int,int*);                   //mtfzplv
void    FzySCurve(fdb*,double,double,double,int,int*);          //mtfzscs
void    FzyShoulderedCurve(fdb*,int,double,double,int*);        //mtfzsfs
bool    FzyStatCompIndex(fdb*,float,CIX*);                      //mtfzscx
void    FzySupportSet(fdb*,double[],int[],int*);                //mtfzspt
void    FzyTriangleCurve(fdb*,double,double,double,int*);       //mtfztrs
void    FzyTrueSet(fdb*);                                       //mtfztru
void    FzyUnCondProposition(fdb*,FSV*);                        //mtfzufp
bool    FzyUnitCompIndex(fdb*,float,float,float*,float*);       //mtfzucx
void    FzyWgtdBetaCurve(fdb*,double,double,double,int*);       //mtfzwbt
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
char   *FzySetId(const fdb*);                                   //mtfzutl
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
float   FzySetAlfaCut(const fdb*);                              //mtfzutl
char   *FzySetDesc(const fdb*);                                 //mtfzutl
char   *FzySetGenDesc(const fdb*);                              //mtfzutl
int     FzySetGentype(const fdb*);                              //mtfzutl
bool    FzySetIsEmpty(const fdb*);                              //mtfzutl
double  FzySetLeftEdge(const fdb*);                             //mtfzutl
int     FzySetOrder(const fdb*);                                //mtfzutl
double  FzySetRightEdge(const fdb*);                            //mtfzutl
float   FzySetTruth(const fdb*,const int,int*);                 //mtfzutl
char   *MtsLicense(void);                                       //mtmtutl
char   *MtsOwner(void);                                         //mtfzutl
char   *MtsVersion(void);                                       //mtmtutl
//
//-------------------M O D E L L I N G   S E R V I C E S--------filename
//
void    MdlAddNoiseWord(char*,PDB*,int*);                       //mtmdanw
void    MdlClosePolicy(PDB*,long*,int*);                        //mtmdclp
void    MdlConnecttoFMS(int*);                                  //mtmdctf
MDB    *MdlCreateModel(char*,int,int*);                         //mtmdmcr
PDB    *MdlCreatePolicy(char*,int,int*);                        //mtmdpcr
void    MdlFindFzyDomain(char*,double*,double*,int*);           //mtmdfzd
fdb    *MdlFindFDB(char*,PDB*,int*);                            //mtmdfdf
HDB    *MdlFindHDB(char*,PDB*,int*);                            //mtmdfdh
NDB    *MdlFindNDB(char*,PDB*,int*);                            //mtmdfdn
PDB    *MdlFindPDB(char*,int*);                                 //mtmdfdp
VDB    *MdlFindVDB(char*,PDB*,int*);                            //mtmdfdv
void    MdlGetcurrentEnvironment(MDB**,PDB**,int*);             //mtmdcen
void    MdlInitMDB(MDB*);                                       //mtmdmdi
void    MdlInitPDB(PDB*);                                       //mtmdpdi
void    MdlInitXSYSctl(int*);                                   //mtmdxsi
void    MdlInsertHedges(PDB*,int*,int*);                        //mtmdihd
void    MdlInsertNWords(PDB*,int*,int*);                        //mtmdinw
void    MdlLinkFDB(fdb*,PDB*,int*);                             //mtmdlkf
void    MdlLinkHDB(HDB*,PDB*,int*);                             //mtmdlkh
void    MdlLinkMDB(MDB*,bool,int*);                             //mtmdlkm
void    MdlLinkPDB(PDB*,int*);                                  //mtmdlkp
void    MdlLinkVDB(VDB*,PDB*,int*);                             //mtmdlkv
MDB    *MdlMakeVirtualModel(char*,char*,char*,PDB**,int*);      //mtmdmvm
PDB    *MdlMakeVirtualPolicy(char*,char*,int*);                 //mtmdmvp
void    MdlRemoveFDB(char*,PDB*,int*);                          //mtmdrmf
void    MdlRemoveHDB(char*,PDB*,int*);                          //mtmdrmh
void    MdlRemoveNDB(char*,PDB*,int*);                          //mtmdrmn
void    MdlRemoveVDB(char*,PDB*,int*);                          //mtmdrmv
void    MdlSetcurrentEnvironment(MDB*,PDB*,int*);               //mtmdcen
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
void    VarAttachFDB(fdb*,VDB*,int*);                           //mtvrafd
void    VarInitVDB(VDB*,int*);                                  //mtvrvri
VDB    *VarCreateScalar(char*,int,double[],char*,int*);         //mtvrcrs
//
//------------------End of Prototype Definitions----------------
#endif
