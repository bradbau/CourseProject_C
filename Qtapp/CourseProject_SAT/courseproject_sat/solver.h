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


extern int DPLL_basic(cnf_fmla *phi); // return the satisfiability of a formula
extern int DPLL_improv_v1(cnf_fmla *phi); //additional BCP module
extern int DPLL_improv_v2(cnf_fmla *phi); //
extern int DPLL_improv_v3(cnf_fmla *phi);

extern int SingleLiteralEliminating(cnf_fmla *phi, int LtrlIndex, int AssignValue);//this literal index must be positive
extern int LiteralAssigned(cnf_fmla *phi,int LtrlIndex);
extern int BCP_propagate(cnf_fmla *phi);
extern cnf_clause * SingleLiteralClause(cnf_fmla *phi);



extern int SelectedLiteral_basic(cnf_fmla *phi);//return the index of selected literal
extern int SelectedLiteral_improv(cnf_fmla *phi);

extern int Terminated(cnf_fmla * phi);//judge the state of the formula, 0 means not ,1 means satisfied, -1 means not satisfied 

extern int backtrack_chrono(cnf_fmla *phi); //return the literal for next elimination 
extern int backtrack_jump(cnf_fmla *phi, int cpoint); //cpoint is the literal index in the assignstack which assign cause conflict


extern int RecoverHiddenClause(cnf_fmla * phi, int pivotValue);
extern int RecoverHiddenLiteral(cnf_fmla * phi, int LtrlValue);

extern int ValueOfPivot(cnf_clause * SLClause);

extern int PredictedValue(cnf_fmla * phi, int Ltrlindex); //this function is of low efficency


#ifdef __cplusplus
}
#endif
#endif // !solver_H_

