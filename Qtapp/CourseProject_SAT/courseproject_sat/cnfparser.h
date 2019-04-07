

#ifndef _cnfparser_H_
#define _cnfparser_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define INFEASIBLE -1

#define int int

#ifdef __cplusplus
extern "C"
{
#endif

//define the  data structure of cnf formula
//
typedef struct cnf_literal_type{
    int index;
    struct cnf_literal_type * prevsLiteral;
    struct cnf_literal_type * nextLiteral;
 
} cnf_literal;

typedef struct cnf_clause_type{
    int pivotIndex;
    struct cnf_literal_type * firstLiteral;
    struct cnf_literal_type * d_literal; //put the unsatisfied literal before the d_literal 
    struct cnf_clause_type * prevsClause;
    struct cnf_clause_type * nextClause;
} cnf_clause;

typedef struct {
    cnf_clause * firstClause;
    cnf_clause * learnedClause;//not in consideration in _basic
    cnf_clause * d_clause;//divide the satisfied clause and the undetermined ones
    int * literalValue;  // array storage the value of literal by sequence
    int * assignStack;     //store the literal index by decision level
    int assignDepth;
    int clauseNum;
    int literalNum;
} cnf_fmla;

extern cnf_fmla* cnfStdLoad(char * filename);

extern int AddClause(cnf_fmla * phi, cnf_clause *alpha, int mode);// mode==0 add to self clause, mode==1 add to learned clause 

extern int DeleteClause(cnf_fmla *phi, cnf_clause *alpha);
extern int  RecollectLiteral(cnf_literal* l);
extern int IdenticalClause(cnf_clause * alpha, cnf_clause * beta);// whether the clause alpha and beta have same members
extern cnf_literal* HasLiteral(cnf_clause * alpha, int l);// only search the item between h/t literal
extern cnf_clause* HasClause_basic(cnf_fmla * phi, cnf_clause * alpha);
extern cnf_clause* HasClause_improv(cnf_fmla * phi, cnf_clause * alpha);//using literal nextref pointer

//extern cnf_literal * TraverseFormula(cnf_fmla * phi, cnf_literal * l, int(*visit)(cnf_literal *)); //return the address of the target literal, or return NULL


#ifdef __cplusplus
}
#endif
#endif // !_cnfparser_H_

