#ifndef _solver_H_
#define _solver_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"cnfparser.h"



#ifdef __cplusplus
extern "C"
{
#endif

//define the function for solving sat problem by dpll

extern bool DPLL_basic(cnf_fmla *phi); // return the satisfiability of a formula

extern status SingalLiteralEliminating(cnf_fmla *phi, int LtrlIndex, int AssignValue);
extern status LiteralAssigned(cnf_fmla *phi,int LtrlIndex);
extern status BCP_propagate(cnf_fmla *phi);

extern int SelectedLiteral_basic(cnf_fmla *phi);//return the index of selected literal
extern int SelectedLiteral_improv(cnf_fmla *phi);

extern int Terminated(cnf_fmla * phi);//judge the state of the formula, 0 means not ,1 means satisfied, -1 means not satisfied 

extern int backtrack_chrono(cnf_fmla *phi); //return the literal for next elimination 
extern status backtrack_jump(cnf_fmla *phi);

extern status RecoverHiddenClause(cnf_fmla * phi, int pivotValue);
extern status RecoverHiddenLiteral(cnf_fmla * phi, int LtrlValue);





#ifdef __cplusplus
}
#endif
#endif // !solver_H_

