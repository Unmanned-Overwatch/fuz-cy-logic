/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdsts.cpp   Earl Cox  04/01/92 Set A Trace Switch         |
| The integrated tracing facility of is controlled by         |
| XSYStrace[*] in the control block. Each switch position can |
| assumed four positions: 0 (off), 1 (low), 2 (medium), and   |
| 3 (high). Each setting determines the amount of output.     |
| Currently, the following trace options are supported,       |
|                                                             |
|       [0]  Execution                                        |
|       [1]  Variables                                        |
|       [2]  Rules                                            |
|       [3]  Fuzzy Sets                                       |
|                                                             |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <XSYSctl.hpp>
#include   <mtypes.hpp>
void MdlSetTraceSwitch(int TraceOption,int TraceLevel,int *statusPtr)
 {
  if(TraceOption<0||TraceOption>8)
    {
      *statusPtr=1;
      return;
    }
  if(TraceLevel<0||TraceLevel>3)
    {
      *statusPtr=3;
      return;
    }
  XSYSctl.XSYStrace[TraceOption]=TraceLevel;
 }
