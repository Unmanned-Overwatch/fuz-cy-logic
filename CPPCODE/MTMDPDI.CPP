/*------------------------------------------------------------*



*--------------------Procedure Description--------------------*
| mtmdsdi.cpp   Earl Cox  04/01/93  Initialize PDB block      |
| This routine initializes a Policy  Descriptor Block in the  |
| fuzzy modelling system. A policy  is a partition of the     |
| model into operational or functional units.                 |
*----------------Modification Audit/Change Log----------------*
| Rev  Sar                                                    |
| No   Code  Date      Rellvl  Mod  Description               |
| --   ----- --------  ------  ---  --------------------------|
|                                                             |
*-------------------------------------------------------------*/
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <PDB.hpp>
#include   <SystemTypes.hpp>
void MdlInitPDB(PDB *PDBptr)
  {
    int i,j;
//--Blank out the model and environment identification
//--slots. These will be set as the system starts.
    memset(PDBptr->PDBid,       ' ',IDENLEN);
    memset(PDBptr->PDBdesc,     ' ',DESCLEN);
    PDBptr->PDBVariableDescriptorcnt=     0;
    PDBptr->PDBFuzzysetDescriptorcnt=     0;
    PDBptr->PDBhdbcnt=     0;
    PDBptr->PDBndbcnt=     0;
//--Clear all the hash dictionaries associated with
//--the environment and the currently active model
    for(i=0;i<VariableDescriptormax;i++) PDBptr->PDBvariables[i]= NULL;
    for(i=0;i<FuzzysetDescriptormax;i++) PDBptr->PDBfuzzysets[i]= NULL;
    for(i=0;i<HDBmax;i++) PDBptr->PDBhedges[i]=    NULL;
    for(i=0;i<NDBmax;i++) PDBptr->PDBnoise[i]=     NULL;
    PDBptr->PDBnext=NULL;
    return;
  }
