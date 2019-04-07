#include"display.h"

//#define DEGUB

// measuring the effiency of solver on single cnf case  return time comsumed 
extern char* CaseRunner_single(char * filename, int(*solver)(cnf_fmla *), char * resultDir){
    //part 1 solve the problem
    clock_t start, finish; 
    int result;
    cnf_fmla *phi = cnfStdLoad(filename);

    start = clock();
    result = solver(phi);
    finish = clock();

    //part 2 save in file

    char * resDir = ConstructResname(filename, resultDir);

    FILE *fp;
	if ((fp = fopen(resDir, "w+")) == NULL)
	{
        char * err;
        err = (char*)malloc(32*sizeof(char));
        sprintf(err, "File open error\n ");
        return err;
	}
    free(resDir);

    char * ResStr = ConstructResStr(result, phi, finish-start);

    fwrite(ResStr, sizeof(char), strlen(ResStr), fp);

    if(!fclose(fp))
        return ResStr;
    else return NULL;
}

extern char * ConstructResname(char * srcfilename, char * resDirStr){
    char * resFN, *buffer, *resDir;

    buffer = (char *)malloc(128*sizeof(char));
    resFN = (char *)malloc(128*sizeof(char));
    resDir = (char *)malloc(128*sizeof(char));
    strcpy(buffer, srcfilename);
    const char * temp = buffer;
    buffer = strrchr(temp, '/');
    if(buffer==NULL)
        buffer = strrchr(temp, '\\');

    //dealt with the .cnf
    char * cutposi = strrchr(buffer, '.');
    while(*cutposi){
        *cutposi  = NULL;
        cutposi++;
    }

    strcpy(resFN, buffer);

    strcpy(resDir, resDirStr);
    strcat(resFN, ".res");
    strcat(resDir, resFN);
    free(resFN);
    return resDir;
}

extern char * ConstructResStr(int result, cnf_fmla* phi, int timeuse){
    char * ResStr;
    int strlenth = 16+ phi->literalNum*((int)log10(phi->literalNum)+3);
    int stepcover=0, step=0;
    ResStr = (char*)malloc(strlenth*sizeof(char));
    step = sprintf(ResStr, "s");
    ResStr+=step;
    stepcover+= step;
    if(result==1){
        step = sprintf(ResStr, " 1\nv");
        stepcover+=step;
        ResStr+=step;
        // then output the literal value

        int i;
        for(i = 0; i<phi->literalNum; ++i){
            if(phi->literalValue[i]==0){
                step = sprintf(ResStr, " +-%d", i+1);
                ResStr+=step;
                stepcover+= step;
            }
            else if(phi->literalValue[i]%4 <= 1){
                step = sprintf(ResStr, " +%d", i+1);
                ResStr+=step;
                stepcover+= step;
            }
            else{
                step = sprintf(ResStr, " -%d", i+1);
                ResStr+=step;
                stepcover+= step;
            }
        }

    }
    else {

         step = sprintf(ResStr, " 0\nv\n");
         ResStr+=step;
         stepcover+= step;
    }

    //output the time consuming
    step = sprintf(ResStr, "\nt %dms\n", timeuse);
    ResStr+=step;
    stepcover+= step;

    //mark the date
    time_t t;
    time(&t);
    const char* calbuf;
    calbuf = ctime(&t);
    step = sprintf(ResStr, calbuf);

    ResStr[strlen(ResStr)]=NULL;
    ResStr =ResStr- stepcover;

    if(result ==1){
    char *res = DisplayRes(phi);

   // ResStr = (char *)realloc(ResStr, ((strlen(ResStr)+strlen(res)+2))*sizeof(char));
    char *newbase;
    newbase = (char*)malloc( (strlen(ResStr)+strlen(res)+2)*sizeof(char) );
    strcpy(newbase, ResStr);
    strcat(newbase, res);
   // free(ResStr); why?
    ResStr = newbase;
    }

    //free(ResStr);
    //free(res);

    return ResStr;

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

        strcat(casefolder, "\\");
        strcat(casefolder, env->d_name);
        
        if(env->d_name[0]!='.'){  //helpless
            const char * envname = env->d_name;

            if(strstr(envname, ".cnf")){
                if(!opendir(resfolder)){
                    mkdirs(resfolder);
                }
                if(CaseRunner_single(casefolder, solver, resfolder)== NULL)
                return ERROR;
            }
            else {
                char * subresfolder;
                subresfolder = (char *)malloc(256*sizeof(char));
                strcpy(subresfolder, resfolder);
                strcat(subresfolder, "\\");
                strcat(subresfolder, env->d_name);
                const char * dirname = subresfolder;
                mkdir(dirname);
                if(CaseRunner_batch(casefolder, solver, subresfolder)== NULL)
                return ERROR;
                free(subresfolder);
            }
        }
       
    }
    return OK;


}

extern char * Displaycnf(cnf_fmla *phi){
    char * cnfStr;
    int* cnfstrsize;
    cnfstrsize = (int*)malloc(sizeof(int));
    (*cnfstrsize)= 512;
    cnfStr = (char *)malloc((*cnfstrsize)*sizeof(char));
    sprintf(cnfStr, "cnf变元数：%d，cnf子句数：%d\n", phi->literalNum, phi->clauseNum);
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

extern char * DisplayRes(cnf_fmla *phi){
    int* cnfstrsize;
    cnfstrsize = (int*)malloc(sizeof(int));
    (*cnfstrsize)= 128;
    if(phi->assignDepth!=phi->literalNum){
        return NULL;
    }
    char * Res;
    Res = (char *)malloc((*cnfstrsize)*sizeof(char));
    sprintf(Res, "以下是公式验证结果\n");
    cnf_clause * preCls = phi->firstClause;
    while(preCls){
        Res = AddClsStr_Res(phi, preCls, Res, cnfstrsize);
        preCls = preCls->nextClause;
        
    }
    return Res;
}

extern char * AddClsStr_Res(cnf_fmla * phi, cnf_clause *preCls, char *Res, int * cnfstrsize){
    cnf_literal * preLtrl = preCls->firstLiteral;

    while(preLtrl->index!=0){
         char * Ltrlbuffer;
            Ltrlbuffer = (char *)malloc(64*sizeof(char));
            if(phi->literalValue[abs(preLtrl->index)-1]%4<=1){
               snprintf(Ltrlbuffer, 64, "%d(1) V ", preLtrl->index);

            }
            else{
               snprintf(Ltrlbuffer, 64, "%d(0) V ", preLtrl->index);

            }
            //DEBUG
          //  printf("%s", Ltrlbuffer);
            int Ltrllen = strlen(Ltrlbuffer)+2;
            char * newbase;
            newbase = (char *)malloc(((*cnfstrsize)+Ltrllen)*sizeof(char));
            strcpy(newbase, Res);
            free(Res);
            Res = newbase;
            Res = newbase;
            strcat(Res, Ltrlbuffer);
            (*cnfstrsize)+=Ltrllen;
            free(Ltrlbuffer);

            preLtrl = preLtrl->nextLiteral;
    }
     char *cutposition = strrchr(Res, 'V');
    *cutposition = '\n';
    return Res;

}

extern char * AddClsStr(cnf_clause *preCls, char *cnfStr, int * cnfstrsize){
    cnf_literal * preLtrl = preCls->firstLiteral;
    while(preLtrl->index!=0){
        if(preLtrl->index>0){
            char * Ltrlbuffer;
            Ltrlbuffer = (char *)malloc(64*sizeof(char));
            snprintf(Ltrlbuffer, 64, "%d V ", preLtrl->index);
            //DEBUG
          //  printf("%s", Ltrlbuffer);
            int Ltrllen = strlen(Ltrlbuffer)+2;
            char * newbase;
            newbase = (char *)malloc(((*cnfstrsize)+Ltrllen)*sizeof(char));
            strcpy(newbase, cnfStr);
            free(cnfStr);
            cnfStr = newbase;
            cnfStr = newbase;
            strcat(cnfStr, Ltrlbuffer);
            (*cnfstrsize)+=Ltrllen;
            free(Ltrlbuffer);
        }
        else if(preLtrl->index<0){
            char * Ltrlbuffer;
            Ltrlbuffer = (char *)malloc(64*sizeof(char));
            snprintf(Ltrlbuffer, 64, "﹁%d V ", abs(preLtrl->index));
             //DEBUG
           // printf("%s", Ltrlbuffer);
            int Ltrllen = strlen(Ltrlbuffer)+4;
            char *newbase;
            newbase = (char *)malloc(((*cnfstrsize)+Ltrllen)*sizeof(char));
            strcpy(newbase, cnfStr);
            free(cnfStr);
           //cnfStr = (char *)realloc(cnfStr, ((*cnfstrsize)+Ltrllen)*sizeof(char));
            cnfStr = newbase;
            strcat(cnfStr, Ltrlbuffer);
            (*cnfstrsize)+=Ltrllen;
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


