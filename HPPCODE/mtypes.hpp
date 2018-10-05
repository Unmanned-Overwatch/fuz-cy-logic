//--mtypes.hpp [EDC Rev 1.0 04/01/93]
//--------------------------------------------------------------

//--------------------------------------------------------------
//
//--The system Types header contains all the special typedefs,
//--constants, and macro definitions used throughout the system.
//--[see the fuzzy.hpp] file for data directly associated with
//--fuzzy logic and approximate reasoning.
#ifndef __mtypes
#define __mtypes
#ifndef __DEBUG
#define __DEBUG       1
#endif
#define IDENLEN       16
#define DESCLEN       60
#define WORDLEN       80
#define TOKENLEN     255
#define CHECKALL      99
#define PARMMAX        4
#define PATHMAX       81
#define TRACEMAX      16
#define FDnameLEN      9
#define FDextLEN       4
#define FDpathLEN     81
#define LINEmax     2047
#define VECMAX       257
#define VDBmax       191
#define PDBmax        31
#define FDBmax        31
#define HDBmax        31
#define NDBmax        31
#define MDBmax         4
//--Max extents for arrays of model types
#define FDBvecmax      8
#define HDBvecmax      8
#define VDBvecmax      8
//---Type definitions for basic system
typedef int             Ctlswitch;
typedef unsigned char   byte;
typedef long            fullword;
typedef float           truthfunc[VECMAX];
typedef float           truthval;
typedef double          domainval;
//--Token Types
#define STRING        0
#define QUOTEDSTRING  1
#define OPERATOR      2
#define FUNCTION      3
#define INTEGER       4
#define REAL          5
#define FUZZYSET      6
#define HEDGE         7
#define VARIABLE      8
#define HEDGEDSET     9
#define UNARYMINUS   10
//--Extended data types
#define BOOLEAN      11
#define DATE         12
#define TIME         13
//--Varable types
#define SCALAR        1
#define LIST          2
#define VECTOR        3
#define TIMESERIES    4
//--Explanatory facility node types
#define RXCpredtype   1
#define RXCconstype   2
//---Enumeration of the Boolean constants
#define SUCCESS       1
#define FAILED        0
#define TRUE          1
#define FALSE         0
#define ON            1
#define OFF           0
#define YES           1
#define NO            0
#define OPEN          1
#define CLOSED        0
#define FOREVER       1
#define ACTIVE        1
#define INACTIVE      0
//--file activities
#define systemEOF     9999
#define systemEOP     9999
#define DBnotfound   -1
#define SysNOMemory   777
#define DBfound       0
#define DBrwmode      "rb+"
//--Miscellaneous constants
#define SEGMENT       1
#define POLICY        2
#define OPTIONAL      2
#define MEMBUFF       8
//---Constants of specific data types
static const float  EPSILON     =  0.00001;
static const float  E           =  2.718281828;
static const float  MINUSONE    = -1.0;
static const float  ZERO        =  0.0;
static const float  POINTFIVE   =  0.5;
static const float  POINTTHREE  =  0.3;
static const float  TWO         =  2.0;
static const float  THREE       =  3.0;
#define             NUDGE          .009999
#define             BUMP           .9999
//--Special character definitions
#define  SINGLEQUOTE     '\''
#define  DOUBLEQUOTE     '\"'
#define  BLANK           ' '
#define  ASTERISK        '*'
#define  SLASH           '/'
#define  TAB             '\t'
#define  NEWLINE         '\n'
#define  END_OF_BUFFER   '\0'
#define  NOTFOUND        -1
//--Tracing controls
#define TRACEVARS     0
#define TRACEFUZZY    1
#define TRACEPOLICY   2
//--System files
#define SYSMODFILE    0
#define SYSLOGFILE    1
#define SYSERRFILE    2
#define SYSOUT        3
//--Search control parameters (Used in serial, binary, and
//--hash-based searches)
#define  FULL             1
#define  PARTIAL          2
#define  ANY              3
//--Fuzzy Model symbolic constants
//
#define  MODELADD         1
#define  MODELHOLD        2
#define  NORMAL           0
//
//--Special macros no longer supported by C++ or required by FMS
//--including the simple min/max operators that Borland decided
//--to drop from C++ in favor of making every programmer define
//--their own in-line operator-based version!
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif
