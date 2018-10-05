//--fuzzy.hpp [EDC Rev 1.0 04/01/93]
//--------------------------------------------------------------

//--This is the general fuzzy header area where we define the
//--constants, macros, and working storage controls for the
//--approximates reasoning facilities.
#ifndef __fuzzy
#define __fuzzy
//---Types of Alpha Cut and Compatibility Thresholds
#define STRONG        1
#define WEAK          2
#define RULEBELOWALFA 88
//---Standard builtin Fuzzyset surfaces
#define EMPTYSET      0
#define INCREASE      1
#define DECREASE      2
#define DECLINE       3
#define GROWTH        4
#define PI            5
#define BETA          6
#define MEMSERIES     7
#define COORDINATES   8
#define TRANSFORM     9
#define LEFTSHOULDER 10
#define RITESHOULDER 11
#define GAUSS        12
#define TRIANGLE     13
#define WGTDBETA     14
//--Ways of approximating a scalar
#define FZYPOINT      1
#define FZYPI         2
#define FZYBETA       3
#define FZYTRIANGLE   4
//---Population Fuzzyset surfaces
#define ERLANG        9
#define POISSON      10
#define GEOMETRIC    11
#define WEIBULL      12
//---Types of Fuzzy Set Theoretic Operations
#define UNION         1
#define INTERSECTION  2
#define COMPLEMENT    3
#define INTENSIFY     4
#define MEANAND       5
#define PRODUCTAND    6
#define BOUNDEDAND    7
#define YAGERAND      8
#define ZADEHAND      9
#define MEANOR       10
#define PRODUCTOR    11
#define BOUNDEDOR    12
#define YAGEROR      13
#define ZADEHOR      14
#define ZADEHNOT     15
#define YAGERNOT     16
#define SUGENONOT    17
#define THRESHOLDNOT 18
#define COSINENOT    19
//--Types of correlation controls
#define CORRMINIMUM   1
#define CORRPRODUCT   2
#define CORRAVERAGE   3
#define CORRDEFAULT   4
//--Types of Implication methods
#define PRODUCTSUM    1
#define MINMAX        2
#define AVGSPACE      3
#define BOUNDEDADD    4
#define BOUNDEDMEAN   5
//--Types of Membeship functions
#define MEMFXNORM     1
#define MEMFXLOG      2
#define MEMFXNUMS     3
//--Types of Consequent Geometries
#define FZYSPACE      1
#define SINGELTON     2
#define VOTEBOUNDED   3
//--Types of Defuzziication Methods
#define CENTROID      1
#define MAXPLATEAU    2
#define MAXIMUM       3
#define AVGSUPPORT    4
#define AVGMAXIMUM    4
#define BESTEVIDENCE  5
#define LEASTENTROPY  6
#define NEAREDGE      7
#define FAREDGE       8
//--Normalization types
#define NormMINIMUM   1
#define NormMAXIMUM   2
//---The built-in Hedge identifiers
#define  ABOUT        1
#define  AROUND       1
#define  ABOVE        2
#define  POSITIVE     3
#define  BELOW        4
#define  VICINITY     5
#define  GENERALLY    6
#define  CLOSE        7
#define  NOT          8
#define  SOMEWHAT     9
#define  VERY        10
#define  EXTREMELY   11
#define  SLIGHTLY    12
#define  AFTER       13
#define  BEFORE      14
//--User Hedge operations
#define ADD           1
#define SUBTRACT      2
#define MULTIPLY      3
#define DIVIDE        4
#define POWER         5
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
//--Character plot types [Unused]
#define WIDEPLOT      1
#define SMALLPLOT     2
#define CRTPLOT       3
#define LARGEPLOT     4
//---END OF DEFINITIONS
#endif
