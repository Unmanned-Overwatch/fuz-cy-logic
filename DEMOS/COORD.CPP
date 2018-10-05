/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| coord.cpp   Earl Cox  04/01/93 Test coordinate extraction   |
| This procedure takes a character string holding coordinate  |
| data in the form "value@mem value@mem value@mem ..." and    |
| returns an array holding the values and the membership      |
| values.                                                     |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stdio.h>
#include "SSYSctl.hpp"
#include "mtsptype.hpp"
void main(void)
 {
   char  coords[128];
   double   values[16];
   float    members[16];
   int     i,vcnt,status;
   
  MdlConnecttoFMS(&status); 

  printf("Enter the coordindate string\n");
  gets(coords);
  fprintf(stdout,"%s%s\n","Echo: ",coords);
  FzyGetCoordinates(coords,values,members,&vcnt,&status);
  fprintf(stdout,"%s%d\n","vcnt     =  ",vcnt);
  fprintf(stdout,"%s%d\n","status   =  ",status);
  for(i=0;i<vcnt;i++)
   fprintf(stdout,"%d%s  %10.2f  %10.2f\n",
     i,". ",values[i],members[i]);
  return;
 }
