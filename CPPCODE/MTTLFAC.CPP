/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mttlfac.cpp  Earl Cox  01/13/93 Compute Factorial of X      |
| Yes, I know this can be done with recursion! Every computer |
| science text book in the known universe uses either x! or   |
| the Towers of Hanoi to illustrate recusion. But it is a very|
| poor way of do it...                                        |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
double MtsFactorial(double X)
 {
  int i;
  double facval=1;
  if(X==0) return(facval);
  for(i=2;i<X;i++) facval=facval*i;
  return(facval);
 }
