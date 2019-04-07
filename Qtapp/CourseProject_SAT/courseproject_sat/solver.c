#include"solver.h"

int DPLL_basic(cnf_fmla *phi){
// return the satisfiability of a formula

//repeat
    //Single Literal Eliminating

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
        
        if(SingleLiteralEliminating(phi, abs(preL), 1)){
            preL = SelectedLiteral_basic(phi);
            continue;
        }
        else{
            preL = backtrack_chrono(phi);
            
        }
    }
    return solve_state;

}


extern int DPLL_improv_v1(cnf_fmla *phi){ //equip the basic version with a bcp process

    int solve_state;
    int preL = SelectedLiteral_basic(phi);

    while(!(solve_state = Terminated(phi))){
        
        if(SingleLiteralEliminating(phi, abs(preL), 1)){
        //bcp_propagation
            if(BCP_propagate(phi)==FALSE){
                preL = backtrack_jump(phi, preL);
            }
            else{   
                preL = SelectedLiteral_basic(phi);
            }
        }
        else{
            preL = backtrack_chrono(phi);
            
        }
    }
    return solve_state;

}

extern int DPLL_improv_v2(cnf_fmla *phi){
    int solve_state;
    int preL = SelectedLiteral_basic(phi);

    while(!(solve_state = Terminated(phi))){
        
        if(SingleLiteralEliminating(phi, abs(preL), PredictedValue(phi,preL))){
            preL = SelectedLiteral_basic(phi);
            continue;
        }
        else{
            preL = backtrack_chrono(phi);
            
        }
    }
    return solve_state;

}

extern int DPLL_improv_v3(cnf_fmla *phi){
       int solve_state;
    int preL = SelectedLiteral_basic(phi);

    while(!(solve_state = Terminated(phi))){
        
        if(SingleLiteralEliminating(phi, abs(preL), PredictedValue(phi, preL))){
        //bcp_propagation
            if(BCP_propagate(phi)==FALSE){
                preL = backtrack_jump(phi, preL);
            }
            else{   
                preL = SelectedLiteral_basic(phi);
            }
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

extern int Terminated(cnf_fmla * phi){
    //when the last literal in assignstack has a value in literalvalue suggesting it has been assigned twice, dpll should end with unsatisfied
    if(phi->assignDepth==1){
        if(phi->literalValue[phi->assignStack[0]-1]>4){
            return -1;
        }
        else return 0;
    }
    else if(phi->assignDepth==phi->literalNum){
        return 1;
    }
    else if(phi->d_clause == NULL){
        return 1;
        //this step accelerate the termination when it is satisfied
    }
    else 
        return 0;
}

extern int SingleLiteralEliminating(cnf_fmla *phi, int LtrlIndex, int AssignValue)
{
    //initially set literal as positive 1
    //put all staisfied cls before the h_literal, 
    cnf_clause * preCls =phi->d_clause;
    cnf_literal * tarLtrl;
    
    if(!phi->literalValue[LtrlIndex-1]){
        //in case of backtrack assign, so the literal still exist in stack and its assignvalue has a none 0 value
        phi->assignStack[phi->assignDepth] = abs(LtrlIndex);
        phi->literalValue[LtrlIndex-1] = AssignValue;
    }
    else
        phi->literalValue[LtrlIndex-1] = phi->literalValue[LtrlIndex-1] +2;
    phi->assignDepth++;
    

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
                    return FALSE; // prepare to backtrack 
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


extern int LiteralAssigned(cnf_fmla *phi ,int LtrlIndex){
    int i;
    for(i = 0; i<phi->assignDepth; ++i){
        if(abs(LtrlIndex) == phi->assignStack[i])
        return TRUE;
    }
    return FALSE;
}


extern int backtrack_chrono(cnf_fmla *phi){
    int topLtrl = phi->assignStack[phi->assignDepth-1];

    while(phi->literalValue[topLtrl-1]>2 && phi->assignDepth>1){
        phi->literalValue[topLtrl-1] = 0;
        //recover the hidden clause and literal(in the unhidden clause)
        RecoverHiddenLiteral(phi, topLtrl);
        RecoverHiddenClause(phi, topLtrl);

        phi->assignStack[phi->assignDepth-1] = 0;
        phi->assignDepth--;
        topLtrl = phi->assignStack[phi->assignDepth-1];
    }
   
    if(phi->assignDepth ==1 && phi->literalValue[topLtrl-1]>2){
        //when all the space is traversed, switch to end term
        phi->literalValue[topLtrl-1]+=2;
        return topLtrl;
    }
     //recover the hidden clause and literal(in the unhidden clause)
    RecoverHiddenLiteral(phi, topLtrl);
    RecoverHiddenClause(phi, topLtrl);
    phi->assignDepth--;
    //the literal value will be changed in single literal assign process
    return topLtrl;

}

extern int backtrack_jump(cnf_fmla *phi, int cpoint){
    int topLtrl = phi->assignStack[phi->assignDepth-1];
    while(topLtrl!=cpoint){
        phi->literalValue[topLtrl-1] = 0;
        //recover the hidden clause and literal(in the unhidden clause)
        RecoverHiddenLiteral(phi, topLtrl);
        RecoverHiddenClause(phi, topLtrl);

        phi->assignStack[phi->assignDepth-1] = 0;
        phi->assignDepth--;
        topLtrl = phi->assignStack[phi->assignDepth-1];
    }
    if(phi->literalValue[topLtrl-1]>2){
        return backtrack_chrono(phi);
    }
    else{
        RecoverHiddenLiteral(phi, topLtrl);
        RecoverHiddenClause(phi, topLtrl);

        phi->assignDepth--;
    }
    return cpoint;
    

}

extern int RecoverHiddenClause(cnf_fmla * phi, int pivotValue){
    while(phi->d_clause->prevsClause && phi->d_clause->prevsClause->pivotIndex == pivotValue){
        phi->d_clause = phi->d_clause->prevsClause;
        phi->d_clause->pivotIndex = 0;
    }
    return OK;
}

extern int RecoverHiddenLiteral(cnf_fmla * phi, int LtrlValue){
    cnf_clause * preCls = phi->d_clause;
    while(preCls){
        while(preCls->d_literal->prevsLiteral && abs(preCls->d_literal->prevsLiteral->index)==LtrlValue){
            preCls->d_literal = preCls->d_literal->prevsLiteral;
        }
        preCls = preCls->nextClause;
    }
    return OK;
}


extern cnf_clause * SingleLiteralClause(cnf_fmla *phi){
    cnf_clause * preCls = phi->d_clause;
    while(preCls){
        if(preCls->d_literal->nextLiteral->index == 0){
            return preCls;
        }
        preCls = preCls->nextClause;
    }
    return NULL;
}

extern int BCP_propagate(cnf_fmla *phi){
    // if there exist single literal clause, then use SLE
    //return the int of whether the formula has an unavoidable mistake. TRUE means no mistake
    cnf_clause * SLClause;
        while( SLClause = SingleLiteralClause(phi)){
            if(SingleLiteralEliminating(phi, abs(SLClause->d_literal->index), ValueOfPivot(SLClause))  ==FALSE){ //value of pivot is not index of pivot
                return FALSE;
            }
        }
    return TRUE;
}

extern int ValueOfPivot(cnf_clause * SLClause){
    int assignvalue;
    if(SLClause->d_literal->index > 0){
        assignvalue = 1;
    }
    else if(SLClause->d_literal->index < 0){
        assignvalue = 2;
    }
    return assignvalue;
        
}


extern int PredictedValue(cnf_fmla * phi, int Ltrlindex){
    //account the number of positive and negative instances of the literal respectively
    //decide the value by the larger one
    int positive = 0,negative = 0;
    cnf_clause* preCls = phi->d_clause;
    while(preCls){
        cnf_literal* tempLtrl;
        if((tempLtrl = HasLiteral(preCls, Ltrlindex))!=NULL){
            if(tempLtrl->index>0)
                positive++;
            else 
                negative++;
        }
        preCls = preCls->nextClause;
    }
    if(positive>=negative)
    return 1;
    else 
    return 2;

}