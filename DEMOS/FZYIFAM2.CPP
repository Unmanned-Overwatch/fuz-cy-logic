/*------------------------------------------------------------*
| (c) 1993 Metus Systems.      Proprietary software product.  |
| Reproduction or unauthorized use is prohibited. Unauthorized|
| use is illegal. Violators will be prosecuted. This software |
| contains proprietary trade and business secrets.            |
/*-------------------Procedure Description--------------------*
| fzyifam2.cpp Earl Cox  07/12/93 The Inventory FAM           |
|                                                             |
| This is a simple fuzzy inventory model based on a supply    |
| and demand model. We have ules that adjust the inventory    |
| base on the product demand and the current quantity in      |
| stock. The model  is cast in  the form a FAM.               |
|                                                             |
|                        product demand volume                |
| qoh      FALLING   REDUCED   STEADY   INCREASED   RISING    |
|         +--------+---------+--------+-----------+--------+  |
| MINIMAL |   ZR   |   SP    |   MP   |    MP     |   LP   |  |
|         +--------+---------+--------+-----------+--------+  |
| LOW     |   ZR   |   ZR    |   SP   |    MP     |   LP   |  |
|         +--------+---------+--------+-----------+--------+  |
| NEAR.ERP|   MN   |   SN    |   ZR   |    SP     |   MP   |  |
|         +--------+---------+--------+-----------+--------+  |
| HIGH    |   MN   |   MN    |   SN   |    ZR     |   SP   |  |
|         +--------+---------+--------+-----------+--------+  |
| EXCESS  |   LN   |   MN    |   MN   |    ZR     |   ZR   |  |
|         +--------+---------+--------+-----------+--------+  |
|                                                             |
|  As we execute each inventory action, this changes the      |
|  current quantity on-hand which leads to a change in the    |
|  system state for the next interation of the rule analysis. |
|                                                             |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                Metus                               |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <FuzzysetDescriptor.hpp>
#include "FSV.hpp"
#include "VariableDescriptor.hpp"
#include "SSYSctl.hpp"
#include "SFZYctl.hpp"
#include   <fuzzy.hpp>
#include   <SystemTypes.hpp>
#include <SystemPrototypes.hpp>
char   *   dmdFuzzysetDescriptornames[]=
  {
   "FALLING",
   "REDUCED",
   "STEADY",
   "INCREASED",
   "RISING"
  };
char   *   dmdFuzzysetDescriptordesc[]=
  {
   "Significant decrease in product demand",
   "Moderate decrease in product demand",
   "More or less steady demand for product",
   "Moderate increase in product demand",
   "Significant increase in product demand"
  };
char   *   qtyFuzzysetDescriptornames[]=
  {
   "MINIMAL",
   "LOW",
   "NEAR.ERP",
   "HIGH",
   "EXCESSIVE"
  };
char   *   qtyFuzzysetDescriptordesc[]=
  {
   "Quantity on hand is near depletion levels",
   "Quantity on hand is below the reorder point",
   "Quantity on hand is around the economic reorder point [ERP]",
   "Quantity on hand is above the reorder point",
   "Quantity on hand is well above required stockage"
  };
char   *   invFuzzysetDescriptornames[]=
  {
   "LN",
   "MN",
   "SN",
   "ZR",
   "SP",
   "MP",
   "LP"
  };
char   *   invFuzzysetDescriptordesc[]=
  {
   "Make large decrease in surplus inventory",
   "Make moderate decrease in surplus inventory",
   "Make small decrease in surplus inventory",
   "Keep inventory at current stockage level",
   "Make small increase in current inventory",
   "Make moderate increase in current inventory",
   "Make large increase in current inventory"
  };
const int FzyTermMax=9;
//                 FALLING   REDUCED   STEADY  INCREASED  RISING
double dmdPoint[]={-30, -10,  -20, 0, -10, 10,   0, 20,   10, 30};
double invPoint[]=
//  ---LN---  ---MN---  ---SN---  ---ZR---  ---SP---  ---MP---  ---LP---
   {-45, -30, -45, -15, -30,   0, -15,  15,  0,   30, 15,   45, 30,   45};
void main(void)
 {
  FuzzysetDescriptor   *dmdFuzzysetDescriptorptr[FzyTermMax],
        *qtyFuzzysetDescriptorptr[FzyTermMax],
        *invFuzzysetDescriptorptr[FzyTermMax];
  int    dmdFuzzysetDescriptorcnt=5,
         qtyFuzzysetDescriptorcnt=5,
         invFuzzysetDescriptorcnt=7;
  char  *PgmId="fzyifam";
  int    i,j,k,status,FuzzysetDescriptorcnt;
  double ERP,
         ERPwidth,
         PIcenter,
         SCstart,
         SCmidpt,
         SCend;

  status=0;
  printf("%s\n","The Fuzzy Inventory Supply and Demand Model");
  printf("%s\n","(c) 1993 The Metus Systems Group           ");
  MdlConnecttoFMS(&status);
  XSYSctl.XSYSalfacut=0.1;
//
//
/*------------------------------------------------------------*
|             QUARTERLY PRODUCT DEMAND VOLUMES                |
|  These fuzzy sets (for the QtrlyDemand variable) define the |
|  meaning for positive, negative or steady sakes orders/     |
*-------------------------------------------------------------*/
  printf("%s\n","---Creating quarterly demand volume fuzzy sets");
  k=0;
  for(i=0;i<dmdFuzzysetDescriptorcnt;i++)
    {
     dmdFuzzysetDescriptorptr[i]=new FuzzysetDescriptor;
     FzyInitFuzzysetDescriptor(dmdFuzzysetDescriptorptr[i]);
     strcpy(dmdFuzzysetDescriptorptr[i]->FuzzysetDescriptorid,  dmdFuzzysetDescriptornames[i]);
     strcpy(dmdFuzzysetDescriptorptr[i]->FuzzysetDescriptordesc,dmdFuzzysetDescriptordesc[i]);
     dmdFuzzysetDescriptorptr[i]->FuzzysetDescriptordomain[0]=dmdPoint[k];
     dmdFuzzysetDescriptorptr[i]->FuzzysetDescriptordomain[1]=dmdPoint[k+1];
     k+=2;
    }
  FzySCurve (dmdFuzzysetDescriptorptr[0],-30,-20,-10,DECLINE,&status); //FALLING
  FzyPiCurve(dmdFuzzysetDescriptorptr[1],-10, 10            ,&status); //REDUCED
  FzyPiCurve(dmdFuzzysetDescriptorptr[2],  0, 10            ,&status); //STEADY
  FzyPiCurve(dmdFuzzysetDescriptorptr[3], 10, 10            ,&status); //INCREASED
  FzySCurve (dmdFuzzysetDescriptorptr[4], 10, 20, 30,GROWTH ,&status); //RISING
  FzyPlotVar("ITEM.DEMAND",dmdFuzzysetDescriptorptr,dmdFuzzysetDescriptorcnt,SYSMODFILE,&status);
//
//
/*------------------------------------------------------------*
|             CURRENT WAREHOUSE ON-HAND QUANTITIES            |
|  These fuzzy sets (for the QntyOnHand variable) define the  |
|  meaning  for stoackage levels that are above or below the  |
|  current economic reorder point for the product.            |
*-------------------------------------------------------------*/
  printf("%s\n","---Creating on-hand quantities fuzzy sets");
  ERP=160;
  ERPwidth    =ERP*.10;
  for(i=0;i<qtyFuzzysetDescriptorcnt;i++)
    {
     qtyFuzzysetDescriptorptr[i]=new FuzzysetDescriptor;
     FzyInitFuzzysetDescriptor(qtyFuzzysetDescriptorptr[i]);
     strcpy(qtyFuzzysetDescriptorptr[i]->FuzzysetDescriptorid,  qtyFuzzysetDescriptornames[i]);
     strcpy(qtyFuzzysetDescriptorptr[i]->FuzzysetDescriptordesc,qtyFuzzysetDescriptordesc[i]);
    }
//--Define the center of the fuzzy region.
     qtyFuzzysetDescriptorptr[2]->FuzzysetDescriptordomain[0]=ERP-ERPwidth;
     qtyFuzzysetDescriptorptr[2]->FuzzysetDescriptordomain[1]=ERP+ERPwidth;
  FzyPiCurve(qtyFuzzysetDescriptorptr[2],ERP,    ERPwidth,             &status);
//
//--Define the right pi region
     qtyFuzzysetDescriptorptr[3]->FuzzysetDescriptordomain[0]=ERP;
     qtyFuzzysetDescriptorptr[3]->FuzzysetDescriptordomain[1]=ERP+(2*ERPwidth);
  PIcenter=ERP+ERPwidth;
  FzyPiCurve(qtyFuzzysetDescriptorptr[3],PIcenter,ERPwidth,            &status);
//
//--Define the right S-curve region
  SCstart=PIcenter; SCend=PIcenter+(2*ERPwidth);
  SCmidpt=SCstart+((SCend-SCstart)/2);
     qtyFuzzysetDescriptorptr[4]->FuzzysetDescriptordomain[0]=SCstart;
     qtyFuzzysetDescriptorptr[4]->FuzzysetDescriptordomain[1]=SCend;
  FzySCurve (qtyFuzzysetDescriptorptr[4],SCstart,SCmidpt,SCend,GROWTH ,&status);
//
//--Define the left pi region
     qtyFuzzysetDescriptorptr[1]->FuzzysetDescriptordomain[1]=ERP;
     qtyFuzzysetDescriptorptr[1]->FuzzysetDescriptordomain[0]=ERP-(2*ERPwidth);
  PIcenter=ERP-ERPwidth;
  FzyPiCurve(qtyFuzzysetDescriptorptr[1],PIcenter,ERPwidth,            &status);
//
//--Define the left S-curve region
  SCstart=PIcenter-(2*ERPwidth); SCend=PIcenter;
  SCmidpt=SCstart+((SCend-SCstart)/2);
     qtyFuzzysetDescriptorptr[0]->FuzzysetDescriptordomain[0]=SCstart;
     qtyFuzzysetDescriptorptr[0]->FuzzysetDescriptordomain[1]=SCend;
  FzySCurve (qtyFuzzysetDescriptorptr[0],SCstart,SCmidpt,SCend,DECLINE,&status);
  FzyPlotVar("QTY.ON-HAND",qtyFuzzysetDescriptorptr,qtyFuzzysetDescriptorcnt,SYSMODFILE,&status);
//
//
/*------------------------------------------------------------*
|             SURPLUS OR SHORTAGE INVENTORY ACTIONS           |
|  These fuzzy sets (for the TakeInvAction variable) define   |
|  the action we should take for combinations of quarterly    |
|  demand and on-hand stockage. The action specifies a percent|
|  change in the current inventory stockage level.            |
*-------------------------------------------------------------*/
  printf("%s\n","---Creating inventory action fuzzy sets");
  k=0;
  for(i=0;i<invFuzzysetDescriptorcnt;i++)
    {
     invFuzzysetDescriptorptr[i]=new FuzzysetDescriptor;
     FzyInitFuzzysetDescriptor(invFuzzysetDescriptorptr[i]);
     strcpy(invFuzzysetDescriptorptr[i]->FuzzysetDescriptorid,invFuzzysetDescriptornames[i]);
     strcpy(invFuzzysetDescriptorptr[i]->FuzzysetDescriptordesc,invFuzzysetDescriptordesc[i]);
     invFuzzysetDescriptorptr[i]->FuzzysetDescriptordomain[0]= -45;
     invFuzzysetDescriptorptr[i]->FuzzysetDescriptordomain[1]=  45;
     k+=2;
    }
  FzySCurve (invFuzzysetDescriptorptr[0],-45,-37.5,-30,DECLINE,&status); //LN
  FzyPiCurve(invFuzzysetDescriptorptr[1],-30,   15,            &status); //MN
  FzyPiCurve(invFuzzysetDescriptorptr[2],-15,   15,            &status); //SN
  FzyPiCurve(invFuzzysetDescriptorptr[3],  0,   15,            &status); //ZR
  FzyPiCurve(invFuzzysetDescriptorptr[4], 15,   15,            &status); //SP
  FzyPiCurve(invFuzzysetDescriptorptr[5], 30,   15,            &status); //MP
  FzySCurve (invFuzzysetDescriptorptr[6], 30, 37.5, 45,GROWTH ,&status); //LP
  FzyPlotVar("INV.ACTION",invFuzzysetDescriptorptr,invFuzzysetDescriptorcnt,SYSMODFILE,&status);

/*------------------------------------------------------------*
|      EXECUTE THE FAM-BASED FUZZY INVENTORY MODEL            |
|                                                             |
| In this mdoel we start at a base quantity on-hand [QOH] and |
| an economic reprder point [ERP]. Eadh cycle of the model    |
| reads a new product demand value and calculates a new QOH   |
| from the inventory action.                                  |
*-------------------------------------------------------------*/
  FuzzysetDescriptor    *ivaFuzzysetDescriptorptr,*rsltFuzzysetDescriptorptr;
  FSV    *FSVptr;
  VariableDescriptor    *invVariableDescriptorptr;
//double  ProductDemand[]={40,28,25,15,11,9,3,0,0,-8,-10,-12,-18,-25,-33};
  double  ProductDemand[]={30,25,20,15,10,5,0,0,0,-5,-10,-15,-20,-25,-30};
  int     MAXdemands=15;
  int     thisCorrMethod,thisDefuzzMethod,idx;
  double  QOH,pdQOH[24],Domain[2],currDemand,invAction[24],adjfactor[24];
  float   dmdmem,qtymem,rsltmem,CIX,pdCIX[24];
  FILE    *mdllog;

  mdllog=MtsGetSystemFile(SYSMODFILE);

  FuzzysetDescriptor *FAM[5][5]=
   {
    {invFuzzysetDescriptorptr[3],invFuzzysetDescriptorptr[4],invFuzzysetDescriptorptr[5],invFuzzysetDescriptorptr[5],invFuzzysetDescriptorptr[6]},
    {invFuzzysetDescriptorptr[3],invFuzzysetDescriptorptr[3],invFuzzysetDescriptorptr[4],invFuzzysetDescriptorptr[5],invFuzzysetDescriptorptr[6]},
    {invFuzzysetDescriptorptr[1],invFuzzysetDescriptorptr[2],invFuzzysetDescriptorptr[3],invFuzzysetDescriptorptr[4],invFuzzysetDescriptorptr[5]},
    {invFuzzysetDescriptorptr[1],invFuzzysetDescriptorptr[1],invFuzzysetDescriptorptr[2],invFuzzysetDescriptorptr[3],invFuzzysetDescriptorptr[4]},
    {invFuzzysetDescriptorptr[0],invFuzzysetDescriptorptr[1],invFuzzysetDescriptorptr[1],invFuzzysetDescriptorptr[3],invFuzzysetDescriptorptr[3]}
   };
  printf("%s\n","---Executing Inventory Management Policy");
  QOH= 70;
  Domain[0]=-45;Domain[1]=45;
  invVariableDescriptorptr=VarCreateScalar("InvAction",REAL,Domain,"0",&status);
  FzyInitFZYctl(&status);
  if(!(FzyAddFZYctl(invVariableDescriptorptr,&ivaFuzzysetDescriptorptr,&FSVptr,&status)))
    {
     MtsSendError(12,PgmId,"InvAction");
     exit(9);
    }
  thisCorrMethod  =FSVptr->FzySVcorrMethod;
  thisDefuzzMethod=FSVptr->FzySVdefuzzMethod;
//--Inventory management model. How much inventory should we keep
//--based on demand and the amount already in-stock? This model
//--generates an inventory action based on these factors that is
//--used to produce a new quantity-on-hand for the next cycle.
//
  if(QOH<1.0)
    {
     fprintf(mdllog,"%s\n",
      "Caution. Current QOH negative or zero. QOH=1 assumed.");
     QOH=1;
    }
  fprintf(mdllog,"%s%10.2f\n",
   "Quantity On-Hand        [QOH]: ", QOH);
  fprintf(mdllog,"%s%10.2f\n",
   "Economic Reorder Point  [ERP]: ", ERP);
  pdQOH[0]=QOH;
  pdCIX[0]=1.0;
  for(i=0;i<MAXdemands;i++)
    {
     currDemand=ProductDemand[i];
     printf("%3d. %s%10.2f%s%10.2f\n",
       i+1,"QOH: ",QOH,",Demand: ",currDemand);
     fprintf(mdllog,"\n%s\n","------------------------------------");
     dmdmem=0;
//
//--Look at each demand fuzzy region and find the degree of
//--membership for the current demand in these FAM columns/
     for(j=0;j<dmdFuzzysetDescriptorcnt;j++)
       {
        qtymem=0;
        dmdmem=FzyGetMembership(dmdFuzzysetDescriptorptr[j],currDemand,&idx,&status);
        if(dmdmem>0)
          for(k=0;k<qtyFuzzysetDescriptorcnt;k++)
            {
             qtymem=FzyGetMembership(qtyFuzzysetDescriptorptr[k],QOH,&idx,&status);
             if(qtymem!=0)
               {
                fprintf(mdllog,"%3d. %s%s%s%s%s\n",i+1,"Rule [",
                dmdFuzzysetDescriptorptr[j]->FuzzysetDescriptorid,",",qtyFuzzysetDescriptorptr[k]->FuzzysetDescriptorid,"]");
                rsltmem=min(dmdmem,qtymem);
                rsltFuzzysetDescriptorptr=FAM[k][j];
                FzyCondProposition(
                  rsltFuzzysetDescriptorptr,FSVptr,thisCorrMethod,rsltmem,&status);
                fprintf(mdllog,
                 "%s%2d%s%2d%s%s%s%5.3f%s%s%s%s%5.3f%s\n%s%s%s%5.3f%s\n",
                  "FAM(",k,",",j,"): if QOH is ",
                    qtyFuzzysetDescriptorptr[k]->FuzzysetDescriptorid," [",qtymem,"] and ",
                  "Demand is ",dmdFuzzysetDescriptorptr[j]->FuzzysetDescriptorid," [",dmdmem,"]",
                  "                then InvAction is ",
                   rsltFuzzysetDescriptorptr->FuzzysetDescriptorid," [",rsltmem,"];");
                FzyDrawSet(ivaFuzzysetDescriptorptr,SYSMODFILE,&status);
               }
            }
       }
     invAction[i]=FzyDefuzzify(ivaFuzzysetDescriptorptr,thisDefuzzMethod,&CIX,&status);
     if(invAction[i]<0) adjfactor[i]=1-(fabs(invAction[i])/100);
       else          adjfactor[i]=1+(invAction[i]/100);
     QOH*=adjfactor[i];
      fprintf(mdllog,"%s%12.3f\n","QOH         : ",QOH);
     QOH=ceil(MtsRound(QOH,1,&status));
      fprintf(mdllog,"%s%12.3f\n","round(QOH)  : ",QOH);
     pdQOH[i+1]=QOH;
     pdCIX[i+1]=CIX;
     FzyResetFZYctl(&status);
    }
  fprintf(mdllog,"%s\n%s\n",
   "      QOH        Demand     invAction   CIX     adjfactor",
   "---   --------   --------   ---------   -----   --------- ");
  for(i=0;i<MAXdemands;i++)
    fprintf(mdllog,"%2d.   %8.2f   %8.2f   %9.2f   %5.3f   %9.2f\n",
     i+1,pdQOH[i],ProductDemand[i],invAction[i],pdCIX[i],adjfactor[i]);
  fprintf(mdllog,"%s\n"," ");
  return;
 }
