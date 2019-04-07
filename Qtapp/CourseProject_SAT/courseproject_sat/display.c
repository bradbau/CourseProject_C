#include"display.h"

//#define DEGUB

// measuring the effiency of solver on single cnf case  return time comsumed 
extern int CaseRunner_single(char * filename, int(*solver)(cnf_fmla *), char * resultDir){
    //part 1 solve the problem
    clock_t start, finish; 
    int result;
    cnf_fmla *phi = cnfStdLoad(filename);

    start = clock();
    result = solver(phi);
    finish = clock();

    //part 2 save in file

    //construct output filename
    char * resFN, *buffer, *resDir;

    buffer = (char *)malloc(128*sizeof(char));
    resFN = (char *)malloc(128*sizeof(char));
    resDir = (char *)malloc(128*sizeof(char));
    strcpy(buffer, filename);
    const char * temp = buffer;
    buffer = strrchr(temp, '/');
    
    //dealt with the .cnf
    char * cutposi = strrchr(buffer, '.');
    while(*cutposi){
        *cutposi  = NULL;
        cutposi++;
    }


    
    strcpy(resFN, buffer);
    
    strcpy(resDir, resultDir);
    strcat(resFN, ".res");
    strcat(resDir, resFN);
    free(resFN); 
    FILE *fp;
	if ((fp = fopen(resDir, "w+")) == NULL)
	{
		printf("File open error\n ");
		return ERROR;
	}
    free(resDir);


    fputs("s", fp);
    if (result==1){
        fwrite(" 1\n", sizeof(char), strlen(" 1\n"), fp);
    }
    else{
        fwrite(" 0\n", sizeof(char), strlen(" 0\n"), fp);
    }


    char Cminus[16] = " -";
    char Cadd[16] = " ";//without +
    char Cneural[16] = " +-";
    fputs("v", fp);
    int i;
    for(i =0; i<phi->literalNum; i++){
        if(phi->literalValue[i]==0){
            char * numbuf;
            numbuf = (char *)malloc(16*sizeof(char *));
            itoa(i+1, numbuf, 10);
            char *buf;
            buf = (char *)malloc(16*sizeof(char *));
            strcpy(buf, Cneural);
            strcat(buf, numbuf);
            fwrite(buf, sizeof(char), strlen(buf), fp);
            free(buf);
        }
        else if(phi->literalValue[i]%4 <= 1){
            char * numbuf;
            numbuf = (char *)malloc(16*sizeof(char *));
            itoa(i+1, numbuf, 10);
            char *buf;
            buf = (char *)malloc(16*sizeof(char *));
            strcpy(buf, Cadd);
            strcat(buf, numbuf);
            fwrite(buf, sizeof(char), strlen(buf), fp);
            free(buf);
        }
        else{
            char * numbuf;
            numbuf = (char *)malloc(16*sizeof(char *));
            itoa(i+1, numbuf, 10);
            char *buf;
            buf = (char *)malloc(16*sizeof(char *));
            strcpy(buf, Cminus);
            strcat(buf, numbuf);
            fwrite(buf, sizeof(char), strlen(buf), fp);
            free(buf);
        }

    }
    fputs("\n", fp);
    fputs("t ", fp);
    char *timebuf;
    timebuf = (char *)malloc(64*sizeof(char));
    itoa(finish-start,timebuf , 10);
    fputs(timebuf,fp);
    free(timebuf);
    fputs("ms\n",fp);



    //time
    
    time_t t;
    time(&t);
    const char* calbuf;
    calbuf = ctime(&t);
    fwrite(calbuf, sizeof(char), strlen(calbuf), fp);
    if(!fclose(fp))
        return OK;
    else return ERROR;
}


extern int CaseRunner_batch(char *filefolder, int(*solver)(cnf_fmla *), char * resultDir){
    //1.traverse the folder

    struct dirent* env, subenv;
    DIR *pDir;
    pDir=opendir(filefolder);
    char * resfolder;
    resfolder = (char *)malloc(256*sizeof(char));
    strcpy(resfolder, resultDir);
    while (NULL != (env=readdir(pDir)))
    {
        //read 
        char * casefolder;
        casefolder = (char *)malloc(256*sizeof(char));
        strcpy(casefolder, filefolder);

        strcat(casefolder, "/");
        strcat(casefolder, env->d_name);
        
        if(env->d_name[0]!='.'){  //helpless
            const char * envname = env->d_name;

            if(strstr(envname, ".cnf")){
                if(!opendir(resfolder)){
                    mkdirs(resfolder);
                }
                if(CaseRunner_single(casefolder, solver, resfolder)== ERROR)
                return ERROR;
            }
            else {
                char * subresfolder;
                subresfolder = (char *)malloc(256*sizeof(char));
                strcpy(subresfolder, resfolder);
                strcat(subresfolder, "/");
                strcat(subresfolder, env->d_name);
                const char * dirname = subresfolder;
                mkdir(dirname);
                if(CaseRunner_batch(casefolder, solver, subresfolder)== ERROR)
                return ERROR;
                free(subresfolder);
            }
        }
       
    }
    return OK;


}

extern char * Displaycnf(cnf_fmla *phi){
    char * cnfStr;
    int cnfstrsize = 1024;
    cnfStr = (char *)malloc(cnfstrsize*sizeof(char));
    sprintf(cnfStr, "cnf变元数：%d，cnf子句数：%d\n", phi->clauseNum, phi->literalNum);
    // DEBUG
    //printf("%s", cnfStr);
    
    //add clause string to cnfstring
    cnf_clause * preCls = phi->firstClause;
    while(preCls){
        cnfStr = AddClsStr(preCls, cnfStr, cnfstrsize);
        preCls = preCls->nextClause;
        //DEBUG
       // printf("%s", cnfStr);
    }
    return cnfStr;
}


extern char * AddClsStr(cnf_clause *preCls, char *cnfStr, int cnfstrsize){
    cnf_literal * preLtrl = preCls->firstLiteral;
    while(preLtrl->index!=0){
        if(preLtrl->index>0){
            char * Ltrlbuffer;
            Ltrlbuffer = (char *)malloc(64*sizeof(char));
            snprintf(Ltrlbuffer, 64, "%d V ", preLtrl->index);
            //DEBUG
          //  printf("%s", Ltrlbuffer);
            int Ltrllen = strlen(Ltrlbuffer)+2;
            cnfStr = (char *)realloc(cnfStr, (cnfstrsize+Ltrllen)*sizeof(char)); 
            strcat(cnfStr, Ltrlbuffer);
            cnfstrsize+=Ltrllen;
            free(Ltrlbuffer);
        }
        else if(preLtrl->index<0){
            char * Ltrlbuffer;
            Ltrlbuffer = (char *)malloc(64*sizeof(char));
            snprintf(Ltrlbuffer, 64, "﹁%d V ", abs(preLtrl->index));
             //DEBUG
           // printf("%s", Ltrlbuffer);
            int Ltrllen = strlen(Ltrlbuffer)+2;
            cnfStr = (char *)realloc(cnfStr, (cnfstrsize+Ltrllen)*sizeof(char)); 
            strcat(cnfStr, Ltrlbuffer);
            cnfstrsize+=Ltrllen;
            free(Ltrlbuffer);
        }
        preLtrl = preLtrl->nextLiteral;
    }
    char *cutposition = strrchr(cnfStr, 'V');
    *cutposition = '\n';

   // cnfStr[strlen(cnfStr)-2] = '\n';
    //cnfStr[strlen(cnfStr)-1] = NULL;
   
   

    return cnfStr;

}

void mkdirs(char *muldir) 
{
    int i,len;
    char str[512];    
    strncpy(str, muldir, 512);
    len=strlen(str);
    for( i=0; i<len; i++ )
    {
        if( str[i]=='/' )
        {
            str[i] = '\0';
            if( access(str,0)!=0 )
            {
                mkdir( str);
            }
            str[i]='/';
        }
    }
    if( len>0 && access(str,0)!=0 )
    {
        mkdir( str);
    }
    return;
}


