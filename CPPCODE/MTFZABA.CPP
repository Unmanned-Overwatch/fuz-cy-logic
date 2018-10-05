/*------------------------------------------------------------*
*--------------------Procedure Description--------------------*
| mtfzaba.cpp   Earl Cox  04/01/93  See if a value is above   |
| the Alfa threshold [the alpha cut level]. We can check for  |
| either a strong or weak alpha cut.                          |
*-------------------------------------------------------------*/
#include   <fuzzy.hpp>
#include   <mtypes.hpp>
bool FzyAboveAlfa(float memval,float Alfa,int AlfaType)
  {
   switch(AlfaType)
    {
     case STRONG:
      if(memval>Alfa)  return(TRUE);
        else           return(FALSE);
     case WEAK:
      if(memval>=Alfa) return(TRUE);
        else           return(FALSE);
     default:
      return(FAILED);
    }
  }