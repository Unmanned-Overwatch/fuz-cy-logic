//--ASSERT.hpp [EDC Rev 1.0 04/01/93]
//--------------------------------------------------------------

//--------------------------------------------------------------
//
#ifdef __DEBUG
  void _MtsAssert(char*,char*,unsigned);
  #define ASSERT(m,f)        \
     if(f)                   \
        NULL;                \
     else                    \
      _MtsAssert(m,__FILE__,__LINE__)
#else
  #define ASSERT(m,f)  NULL
#endif
