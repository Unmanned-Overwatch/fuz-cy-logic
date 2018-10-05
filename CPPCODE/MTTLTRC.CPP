/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttltrc.cpp  Earl Cox  04/01/93 Trace Control               |
| This procedure checks to see if a specified trace type has  |
| been specified and if the proper trace level has been       |
| satisfied.                                                  |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <XSYSctl.hpp>
#include   <mtypes.hpp>
bool MtsStartTrace(int TraceType,int Tracedepth)
 {

  if(!XSYSctl.XSYSdebug) return(FALSE);
  if(XSYSctl.XSYStrace[TraceType]>=Tracedepth) return(TRUE);
  return(FALSE);
 }
