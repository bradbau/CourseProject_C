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

   
    //declare the formula 
    cnf_fmla * cnfPhi;
    cnf_clause * preCls, *prevsCls;//present clause and previous clause
    cnf_literal *preLtrl, *prevsLtrl;
    cnfPhi = (cnf_fmla *)malloc(sizeof(cnf_fmla));
    cnfPhi->firstClause = (cnf_clause *)malloc(sizeof(cnf_clause));
    preCls = cnfPhi->firstClause;
    preCls->prevsClause = NULL;
    cnfPhi->learnedClause = NULL;
    preCls->firstLiteral = (cnf_literal *)malloc(sizeof(cnf_literal));
    preLtrl = preCls->firstLiteral;
    prevsLtrl = NULL;

    cnfPhi->d_clause = cnfPhi->firstClause;
    cnfPhi->literalValue = (int *)malloc(n_literal * sizeof(int));
    memset(cnfPhi->literalValue, 0, n_literal*sizeof(int));
    cnfPhi->literalNum = n_literal;
    cnfPhi->clauseNum = n_clause;

    cnfPhi->assignStack = (int *)malloc(n_literal * sizeof(int));
    memset(cnfPhi->assignStack, 0, n_literal*sizeof(int));
    cnfPhi->assignDepth = 0;

    char literal[16];
    
    while(fscanf(pFile, "%s",literal)>0){
        int ltrl = atoi(literal);
        if(literal[0]=='c'){
            char tbuf;
            while((tbuf = fgetc(pFile))!='\n');
            continue;
        }
        if(ltrl!=0){
            preLtrl->index = ltrl;
            preLtrl->prevsLiteral = prevsLtrl;
            if(prevsLtrl){
                prevsLtrl->nextLiteral = preLtrl;
            }
            prevsLtrl = preLtrl;
           
            preLtrl->nextLiteral = (cnf_literal *)malloc(sizeof(cnf_literal));
            preLtrl = preLtrl->nextLiteral;
        }
        else{
            preLtrl->index =0; //set the mark literal
            preLtrl->prevsLiteral = prevsLtrl;
            prevsLtrl->nextLiteral = preLtrl;
            preLtrl->nextLiteral = NULL;
            prevsLtrl = NULL;
           
            //set the divide pointer
            preCls->d_literal = preCls->firstLiteral;
            preCls->pivotIndex = 0;
            prevsCls = preCls;
            preCls->nextClause = (cnf_clause *)malloc(sizeof(cnf_clause));
            preCls = preCls->nextClause; 
            preCls->prevsClause = prevsCls;
            preCls->firstLiteral = (cnf_literal *)malloc(sizeof(cnf_literal));
            preLtrl = preCls->firstLiteral;
        }
    }
    //free the extra space allocated by the last round
    free(preLtrl);
    preCls = preCls->prevsClause;
    free(preCls->nextClause);
    preCls->nextClause = NULL;
    fclose(pFile);

    return  cnfPhi;
  
}


extern int AddClause(cnf_fmla * phi, cnf_clause *alpha, int mode){
    if(HasClause_basic(phi, alpha)!=NULL)
        return OK;
    else{
        cnf_clause * preCls, *lastCls;
        if(mode==0){
           preCls = phi->firstClause;
           phi->firstClause = alpha;
           phi->firstClause->prevsClause = NULL;
           phi->firstClause->nextClause = preCls;
           preCls->prevsClause = alpha;
           //add reference of literal
        }
        else{
            preCls = phi->learnedClause;
        }
        lastCls = preCls;
        
    }
}

extern int DeleteClause(cnf_fmla *phi, cnf_clause *alpha){
    cnf_clause * pCls;
    if(pCls = HasClause_basic(phi, alpha))
    pCls->prevsClause->nextClause = pCls->nextClause;
    pCls->nextClause->prevsClause = pCls->prevsClause;
    RecollectLiteral(alpha->firstLiteral);
    free(alpha);

}

extern int  RecollectLiteral(cnf_literal* l){
    if(!(l->nextLiteral)){
        free(l);
        return OK;
    } 
    else 
        RecollectLiteral(l->nextLiteral);
}

extern int IdenticalClause(cnf_clause * alpha, cnf_clause * beta){
// whether the clause alpha and beta have same members
//still has improve space
    cnf_literal * preLtrl = beta->firstLiteral;
    while(preLtrl){
        if(HasLiteral(alpha, preLtrl->index))
            preLtrl = preLtrl->nextLiteral;
        else{
            return FALSE;
        }
    }
    preLtrl = alpha->firstLiteral;
    while(preLtrl){
        if(HasLiteral(beta, preLtrl->index))
            preLtrl = preLtrl->nextLiteral;
        else{
            return FALSE;
        }
    }
    return TRUE;
}

extern cnf_literal* HasLiteral(cnf_clause * alpha, int l){
     cnf_literal * preLtrl = alpha->d_literal;
        do{
            if( abs(preLtrl->index)==abs(l))
                return preLtrl;
            else
                preLtrl = preLtrl->nextLiteral;
        }while(preLtrl->index!=0);
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
    preCls = phi->learnedClause;
    while(preCls){
        if(IdenticalClause(preCls, alpha))
        return preCls;
        else {
            preCls = preCls->nextClause;
        }
    }

}

extern cnf_literal * TraverseFormula(cnf_fmla * phi, cnf_literal * l, int(*visit)(cnf_literal *, cnf_literal *)){
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
    preCls = phi->learnedClause;
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