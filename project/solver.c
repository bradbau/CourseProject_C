#include"solver.h"

bool DPLL_basic(cnf_fmla *phi){
// return the satisfiability of a formula

//repeat
    //Singal Literal Eliminating

    //variable selection 
    //assign value

    // determine

        //if unsais backtrack
            //(add learned clause 

        //if satisfied 
            // return result stack
        
        //if undetermined 
        //continue

    int solve_state;
    int preL = SelectedLiteral_basic(phi);

    while(!(solve_state = Terminated(phi))){
        
        if(SingalLiteralEliminating(phi, preL, 1)){
            preL = SelectedLiteral_basic(phi);
            continue;
        }
        else{
            preL = backtrack_chrono(phi);
            
        }
    }
    return solve_state;

}

extern int SelectedLiteral_basic(cnf_fmla *phi){
    //simplist way to produce unassigned literal
    int Ltrl;
    for(Ltrl = 1; Ltrl <= phi->literalNum; ++Ltrl){
        if(phi->literalValue[Ltrl-1]==0)
        return Ltrl;
    }
}

extern status Terminated(cnf_fmla * phi){
    //when the last literal in assignstack has a value in literalvalue suggesting it has been assigned twice, dpll should end with unsatisfied
    if(phi->assignDepth==1){
        if(phi->literalValue[phi->assignStack[0]-1]>2){
            return -1;
        }
        else return 0;
    }
    else if(phi->assignDepth==phi->literalNum){
        return 1;
    }
    else if(phi->d_clause==NULL){
        return 1;
    }
    else 
    return 0;
}

extern status SingalLiteralEliminating(cnf_fmla *phi, int LtrlIndex, int AssignValue)
{
    //initially set literal as positive 1
    //put all staisfied cls before the h_literal, 
    cnf_clause * preCls =phi->d_clause;
    cnf_literal * tarLtrl;
    if(LiteralAssigned(phi, LtrlIndex))
        return INFEASIBLE; // the literal has been set, error with code
    phi->assignStack[phi->assignDepth] = LtrlIndex;
    phi->assignDepth++;

    if(phi->literalValue[LtrlIndex-1]== 0)
        phi->literalValue[LtrlIndex-1] = AssignValue;
    else{
        phi->literalValue[LtrlIndex-1] = phi->literalValue[LtrlIndex-1] +2;
    }
    while(preCls){
        if(tarLtrl = HasLiteral(preCls, LtrlIndex)){
            //satisfied clause, move to the hidden zone
            if((tarLtrl->index>0&&phi->literalValue[LtrlIndex-1]%4 <= 1)|| (tarLtrl->index<0&&phi->literalValue[LtrlIndex-1]%4 >1)){
               //exchange data field
               cnf_literal * temp;
               temp = preCls->firstLiteral;
               preCls->firstLiteral = phi->d_clause->firstLiteral;
               phi->d_clause->firstLiteral = temp;
               temp = preCls->d_literal;
               preCls->d_literal = phi->d_clause->d_literal;
               phi->d_clause->d_literal = temp;
               //set the pivot index
               phi->d_clause->pivotIndex = LtrlIndex;
               //shift the d_clause
               phi->d_clause = phi->d_clause->nextClause;
            }
            //unsatisfied clause, hide the unsatisfied literal
            else{
                if(preCls->d_literal->nextLiteral->index ==0){
                    return FALSE;// prepare to backtrack 
                }

                int temp = preCls->d_literal->index;
                preCls->d_literal->index = tarLtrl->index;
                tarLtrl->index = temp;
                preCls->d_literal = preCls->d_literal->nextLiteral;
            }
        }
        preCls = preCls->nextClause;
    }
    return OK;
}   


extern status LiteralAssigned(cnf_fmla *phi ,int LtrlIndex){
    int i;
    for(i = 0; i<phi->assignDepth; ++i){
        if(LtrlIndex == abs(phi->assignStack[i]))
        return TRUE;
    }
    return FALSE;
}


extern int backtrack_chrono(cnf_fmla *phi){
    int topLtrl = phi->assignStack[phi->assignDepth-1];
    while(phi->literalValue[topLtrl-1]>2){
        phi->literalValue[topLtrl-1] = 0;
        //recover the hidden clause and literal(in the unhidden clause)
        RecoverHiddenLiteral(phi, topLtrl);
        RecoverHiddenClause(phi, topLtrl);

        phi->assignStack[phi->assignDepth-1] = 0;
        phi->assignDepth--;
        topLtrl = phi->assignStack[phi->assignDepth-1];
    }
    //recover the hidden clause and literal(in the unhidden clause)
    RecoverHiddenLiteral(phi, topLtrl);
    RecoverHiddenClause(phi, topLtrl);
    phi->assignStack[phi->assignDepth-1] = 0;
    phi->assignDepth--;
    return topLtrl;

}

extern status RecoverHiddenClause(cnf_fmla * phi, int pivotValue){
    while(phi->d_clause->prevsClause && phi->d_clause->prevsClause->pivotIndex == pivotValue){
        phi->d_clause = phi->d_clause->prevsClause;
        phi->d_clause->pivotIndex = 0;
    }
    return OK;
}

extern status RecoverHiddenLiteral(cnf_fmla * phi, int LtrlValue){
    cnf_clause * preCls = phi->d_clause;
    while(preCls){
        while(preCls->d_literal->prevsLiteral && abs(preCls->d_literal->prevsLiteral->index)==LtrlValue){
            preCls->d_literal = preCls->d_literal->prevsLiteral;
        }
        preCls = preCls->nextClause;
    }
    return OK;
}


