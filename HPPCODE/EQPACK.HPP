//--eqpack.hpp [EDC Rev 1.0 04/01/93]
//--------------------------------------------------------------

//--------------------------------------------------------------
//
//--The Expression support package contains all the constants and
//--controls used in formulating expressions. Provided as a
//--development tool. This package also contains the default noise
//--words used in the policy management routines.
#ifndef __eqpack
#define __eqpack
#include "mtypes.hpp"
//--The basic operators as string for rapid indexing
const char far EQBasicDelimiters[]=" \t,;+-*/=<>!()[]{}~|\0";
//--Table of all the valid  operators
static const char far * far EQoperators[] =
  {
    "and",   "or",    "=",     "!",   "!=",  ",",   "->",
    ">",     ">=",    "<",     "<=",  "cn",  "om",  "has",
    "(",     ")",     "{",     "}",   "[",   "]",   "|",
    "||",    ";",     "+",     "-",   "*",   "**",  "/"
  };
static const int far EQopSymbolics[] =
  {
     1,       2,       3,       4,     5,     6,     7,
     8,       9,      10,      11,    12,    13,    14,
    15,      16,      17,      18,    19,    20,    21,
    22,      23,      24,      25,    26,    27,    28
  };
static const int EQOPERmax=28;
//--Alternate source operators
static const char far * far EQaltOperators[] =
  {
   "eq",           "are",           "was",
   "lt",           "gt",            "not",
   "ne",           "le",            "ge",
   "and",          "or",            "but",
   "yet",          "be",            "is",
   "cn",           "om",            "has",
   "contains",     "omits",         "excludes",
   "before",       "after",         "equal",
   "equals"
  };
static const char far * far EQaltMappings[] =
  {
   "=",            "=",             "=",
   "<",            ">",             "!",
   "!=",           "<=",            ">=",
   "and",          "or",            "and",
   "and",          "=",             "=",
   "cn",           "om",            "has",
   "cn",           "om",            "om",
   "<",            ">",             "=",
   "="
  };
static const int EQALTOPmax=25;
static const char far * far EQNoiseWords[] =
  {
   " ",
   "a",
   "an",
   "could",
   "may",
   "might",
   "must",
   "ought",
   "our",
   "should",
   "than",
   "that",
   "the",
   "their",
   "these",
   "this",
   "those",
   "will",
   "would",
  };
static const int EQNWRDmax=19;
static const char far * far EQBuiltinFncs[] =
 {
   "abs",
   "ceil",
   "cos",
   "cosh",
   "delta",
   "floor",
   "fuzzymem",
   "fuzzyval",
   "int",
   "leftstr",
   "log",
   "log10",
   "log2",
   "max",
   "mean",
   "memberof",
   "min",
   "mod",
   "movingavg",
   "numcvt",
   "pctdiff",
   "randnorm",
   "randunif",
   "randweib",
   "rightstr",
   "round",
   "sin",
   "sinh",
   "sqrt",
   "strlen",
   "substr",
   "tan",
   "tanh",
   "time",
   "trunc"
 };
static const int far EQfncsSymbolics[]=
 {
   1005,   /* abs      */
   1010,   /* ceil     */
   1015,   /* cos      */
   1020,   /* cosh     */
   1025,   /* delta    */
   1030,   /* floor    */
   1035,   /* fuzzymem */
   1040,   /* fuzzyval */
   1045,   /* int      */
   1050,   /* leftstr  */
   1055,   /* log      */
   1060,   /* log10    */
   1065,   /* log2     */
   1070,   /* max      */
   1075,   /* mean     */
   1080,   /* memberof */
   1085,   /* min      */
   1090,   /* mod      */
   1095,   /* movingavg*/
   1100,   /* numcvt   */
   1105,   /* pctdiff  */
   1110,   /* randnorm */
   1115,   /* randunif */
   1120,   /* randweib */
   1125,   /* rightstr */
   1130,   /* round    */
   1135,   /* sin      */
   1140,   /* sinh     */
   1145,   /* sqrt     */
   1150,   /* strlen   */
   1155,   /* substr   */
   1160,   /* tan      */
   1165,   /* tanh     */
   1170,   /* time     */
   1175    /* trunc    */
 };
static const int EQbiFNCmax=36;
#endif
