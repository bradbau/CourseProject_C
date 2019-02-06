#include"cnfparser.h"

extern cnf_fmla* cnfStdLoad(char * filename){
// loading the .cnf file and put them into the htsl crossing list structure
    const char * FN = filename;
    FILE * pFile;
    size_t fsize;
    char * buffer;
    int cbuf;
    pFile = fopen(FN, "rb");
	if (pFile == NULL)
	{
		fputs("File error", stderr);
		return ERROR;
	}
    
	//process the comment lines
    int n_clause, n_literal;
    buffer = (char *)malloc(1024*sizeof(char));
    while((cbuf = fgetc(pFile)) == 'c') 
        fgets(buffer, 1023, pFile);
    if(cbuf != (int)'p'){
        printf("file format error\n");
        return ERROR;
    }
    else{
        char ch_clause[36], ch_literal[36];
        fscanf(pFile, "%*s %s %s", ch_literal, ch_clause);
        n_literal = atoi(ch_literal);
        n_clause = atoi(ch_clause);
    }

    //start processing the data

    // in creating the crossing list ,using an array to store the ref of the last ref of the literal of certain index
    cnf_literal ** lastRef;
    lastRef = (cnf_literal **)malloc(n_literal * sizeof(cnf_literal*));
    memset(lastRef, 0, n_literal * sizeof(cnf_literal*));
    //declare the formula 
    cnf_fmla * cnfPhi;
    cnf_clause * preCls, *prevsCls;//present clause and previous clause
    cnf_literal *preLtrl, *prevsLtrl;
    cnfPhi = (cnf_fmla *)malloc(sizeof(cnf_fmla));
    cnfPhi->firstClause = (cnf_clause *)malloc(sizeof(cnf_clause));
    preCls = cnfPhi->firstClause;
    cnfPhi->learnedClause = NULL;
    prevsCls = NULL;
    preCls->firstLiteral = (cnf_literal *)malloc(sizeof(cnf_literal));
    preLtrl = preCls->firstLiteral;
    prevsLtrl = NULL;

    char literal[16];
    
    while(fscanf(pFile, "%s",literal)>0){
        int ltrl = atoi(literal);
        if(ltrl!=0){
            preLtrl->index = ltrl;
            preLtrl->nextRef = NULL;
            preLtrl->prevsLiteral = prevsLtrl;
            if(prevsLtrl){
                prevsLtrl->nextLiteral = preLtrl;
            }
            prevsLtrl = preLtrl;
            if(lastRef[abs(ltrl)-1])
                lastRef[abs(ltrl)-1]->nextRef = preLtrl;
            
            lastRef[abs(ltrl)-1] = preLtrl;
            preLtrl->nextLiteral = (cnf_literal *)malloc(sizeof(cnf_literal));
            preLtrl = preLtrl->nextLiteral;
        }
        else{
            preLtrl->prevsLiteral = prevsLtrl;
            if(prevsLtrl){
                prevsLtrl->nextLiteral = preLtrl;
            }
            preLtrl->nextLiteral = NULL;
            
            //set the head and tail pointer
            preCls->h_literal = preCls->firstLiteral;
            preCls->t_literal = preLtrl;
            preCls->hb_literal = preCls->tb_literal = NULL;

            preCls->prevsClause = prevsCls;
            if(prevsCls)
                prevsCls->nextClause = preCls;
            prevsCls = preCls;
            preCls->nextClause = (cnf_clause *)malloc(sizeof(cnf_clause));
            preCls = preCls->nextClause; 
            preCls->firstLiteral = (cnf_literal *)malloc(sizeof(cnf_literal));
            preLtrl = preCls->firstLiteral;
        }
    }
    //free the extra space allocated by the last round
    free(preCls);
    free(preLtrl);
    fclose(pFile);

    return  cnfPhi;
  
}


extern status AddClause(cnf_fmla * phi, cnf_clause *alpha, int mode){
    if(HasClause(phi, alpha)==TRUE)
        return OK;
    else{
        cnf_clause * preCls, *lastCls;
        if(mode==0){
           preCls = phi->firstLiteral;
           phi->firstLiteral = alpha;
           phi->firstLiteral->prevsLiteral = NULL;
           phi->firstLiteral->nextLiteral = preCls;
           preCls->prevsLiteral = alpha;
           //add reference of literal
        }
        else{
            preCls = phi->learnedClause;
        }
        lastCls = pre
        
    }
}

extern status DeleteClause(cnf_fmla *phi, cnf_clause *alpha){
    cnf_clause * pCls;
    if(pCLs = HasClause_basic(phi, alpha))
    pCls->prevsClause->nextClause = pCls->nextClause;
    pCls->nextClause->prevsClause = pCls->prevsClause;
    RecollectLiteral(alpha->firstLiteral);
    free(alpha);

}

extern status  RecollectLiteral(cnf_literal* l){
    if(!(l->nextLiteral){
        free(l);
        return OK;
    } 
    else 
    RecollectLiteral(l->nextLiteral);
}

extern status IdenticalClause(cnf_clause * alpha, cnf_clause * beta)
{// whether the clause alpha and beta have same members
//still has improve space
    cnf_literal * preLtrl = beta->firstLiteral;
    while(preLtrl){
        if(HasLiteral(alpha, preLtrl))
            preLtrl = preLtrl->nextLiteral;
        else{
            return FALSE;
        }
    }
    preLtrl = alpha->firstLiteral;
    while(preLtrl){
        if(HasLiteral(beta, preLtrl))
            preLtrl = preLtrl->nextLiteral;
        else{
            return FALSE;
        }
    }
    return TRUE;
}

extern cnf_literal* HasLiteral(cnf_clause * alpha, cnf_literal * l){
     cnf_literal * preLtrl = alpha->firstLiteral;
        while(preLtrl){
            if( abs(alpha->index)==abs(l->index))
                return 
            else
                preLtrl = preLtrl->nextLiteral;
        }
    return NULL;
}

extern cnf_clause* HasClause_basic(cnf_fmla * phi, cnf_clause * alpha){
    cnf_clause * preCls = phi->firstClause;
    while(preCls){
        if(IdenticalClause(preCls, alpha))
        return preCls;
        else {
            preCls = preCls->nextClause;
        }
    }
    cnf_clause * preCls = phi->learnedClause;
    while(preCls){
        if(IdenticalClause(preCls, alpha))
        return preCls;
        else {
            preCls = preCls->nextClause;
        }
    }

}

extern cnf_literal * TraverseFormula(cnf_fmla * phi, cnf_literal * l, status(*visit)(cnf_literal *, cnf_literal *)){
//return the address of the target literal, or return NULL
   cnf_clause * preCls = phi->firstClause;
    while(preCls){
        cnf_literal * preLtrl = preCls->firstLiteral;
        while(preLtrl){
            if( visit(preLtrl, l))
            return preLtrl;
            else
                preLtrl = preLtrl->nextLiteral;
        }
        preCls = preCls->nextClause;
    }
    cnf_clause * preCls = phi->learnedClause;
    while(preCls){
        cnf_literal * preLtrl = preCls->firstLiteral;
        while(preLtrl){
            if( visit(preLtrl, l))
            return preLtrl;
            else
                preLtrl = preLtrl->nextLiteral;
        }
        preCls = preCls->nextClause;
    }
    return NULL;
} 