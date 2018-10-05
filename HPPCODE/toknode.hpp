//--TOKNODE.hpp [EDC Rev 1.0 04/01/93]
//--------------------------------------------------------------

//--------------------------------------------------------------
//
//--The Token descriptor node. Each token in the lexical parse
//--is contains a word in the input string. These nodes define
//--each individual token.
#ifndef __toknode
#define __toknode
struct TokenNode
  {
    char      *token;
    int        toklen,
               toksym,
               toktype;
    TokenNode *toknext;
   };
#endif
