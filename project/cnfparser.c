#include"cnfparser.h"

extern cnf_fmla cnfStdLoad(char * filename){
// loading the .cnf file and put them into the htsl crossing list structure
    const char * FN = filename;
    FILE * pFILE;
    size_t fsize;
    char * buffer;
    char  * cbuf;
    pFile = fopen(Fn, "rb");
	if (pFile == NULL)
	{
		fputs("File error", stderr);
		return ERROR;
	}
    
	
    int n_clause, n_literal;
    buffer = (char *)malloc(1024*sizeof(char));
    while((cbuf = fgetc(pFILE))==c) ;
    if(cbuf!= 'p'){
        printf("file format error\n");
        return ERROR;
    }
    else{
        char ch_clause[36], ch_literal[36];
        fscanf("%s %s", ch_literal, ch_clause);
        n_literal = atoi(ch_literal);
        n_clause = atoi(ch_clause);

        


    }



    // in creating the crossing list ,using an array to store the ref of the last ref of the literal of certain index
}