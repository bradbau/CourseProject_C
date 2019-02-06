

#ifndef _cnfparser_H_
#define _cnfparser_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1

#define status int

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
    struct cnf_literal_type * nextRef; //point to another reference with the same index in amother clause 
} cnf_literal;



typedef struct cnf_clause_type{
    struct cnf_literal_type * firstLiteral;
    struct cnf_literal_type * h_literal; 
    struct cnf_literal_type * t_literal; 
    struct cnf_literal_type * hb_literal; 
    struct cnf_literal_type * tb_literal;
    struct cnf_clause_type * prevsClause;
    struct cnf_clause_type * nextClause;
} cnf_clause;

typedef struct {
     cnf_clause * firstClause;
     cnd_clause * learnedClause;

} cnf_fmla;

extern cnf_fmla* cnfStdLoad(char * filename);//

extern status AddClause(cnf_fmla * phi, cnf_clause *alpha, int mode);// mode==0 add to self clause, mode==1 add to learned clause 

extern status DeleteClause(cnf_fmla *phi, cnf_clause *alpha);
extern status  RecollectLiteral(cnf_literal* l);
extern status IdenticalClause(cnf_clause * alpha, cnf_clause * beta);// whether the clause alpha and beta have same members
extern cnf_literal* HasLiteral(cnf_clause * alpha, cnf_literal * l);
extern cnf_clause* HasClause_basic(cnf_fmla * phi, cnf_clause * alpha);
extern cnf_clause* HasClause_improv(cnf_fmla * phi, cnf_clause * alpha);//using literal nextref pointer

extern cnf_literal * TraverseFormula(cnf_fmla * phi, cnf_literal * l, status(*visit)(cnf_literal *)); //return the address of the target literal, or return NULL


#ifdef __cplusplus
}
#endif
#endif // !_cnfparser_H_

