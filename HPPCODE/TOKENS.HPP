//--TOKENS.hpp [EDC Rev 1.0 04/01/93]
//--------------------------------------------------------------

//--------------------------------------------------------------
//
//--The Token descriptor table. Each token in the lexical parse
//--is contains a word in the input string. These slots define
//--each individual token.
#ifndef __tokens
#define __tokens
struct TokenTable
  {
   int tokencnt;
   char tokens[64][16];
  };
const int MaxTokcnt=64;
const int MaxToklen=16;
#endif
