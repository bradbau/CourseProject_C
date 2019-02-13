#include"display.h"
// measuring the effiency of solver on single cnf case  return time comsumed 
extern status CaseRunner_single(char * filename, bool(*solver)(cnf_fmla *), char * resultDir){
    //part 1 solve the problem
    clock_t start, finish; 
    int result;
    cnf_fmla *phi = cnfStdLoad(filename);

    start = clock();
    result = solver(phi);
    finish = clock();

    //part 2 save in file

    //construct output filename
    char * resFN;
    resFN = (char *)malloc(1024*sizeof(char));
    strcpy(resFN, filename);
    resFN = strtok(resFN, ".");
    resFN = strcat(resFN, ".res");
    resultDir = strcat(resultDir, "//");
    resFN = strcat(resFN, resultDir);
    FILE *fp;
	if ((fp = fopen(resFN, "w+")) == NULL)
	{
		printf("File open error\n ");
		return ERROR;
	}
    free(resFN);


    fputs("s", fp);
    if (result==1){
        fwrite(" 1\n", sizeof(char), strlen(" 1\n"), fp);
    }
    else{
        fwrite(" 0\n", sizeof(char), strlen(" 0\n"), fp);
    }


    char Cminus[16] = " -";
    char Cadd[16] = " +";
    char Cneural[16] = " +-";
    fputs("v", fp);
    int i;
    for(i =0; i<phi->literalNum; i++){
        if(phi->literalValue[i]==0){
            char * numbuf;
            numbuf = (char *)malloc(sizeof(char *));
            itoa(i+1, numbuf, 10);
            const char *buf;
            buf = strcat(Cneural, numbuf);
            fwrite(buf, sizeof(char), strlen(buf), fp);
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


extern status CaseRunner_batch(char *filefolder, bool(*solver)(cnf_fmla *), char * resultDir){
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
        strcat(casefolder, "//");
        strcat(casefolder, env->d_name);
        strcat(resfolder, "//");
        strcat(resfolder, env->d_name);
        if(env->d_reclen==24){
            const char * envname = env->d_name;
            if(strstr(envname, ".cnf")){
                if(CaseRunner_single(casefolder, solver, resultDir)== ERROR)
                return ERROR;
            }
            else {
                if(CaseRunner_batch(casefolder, solver, resfolder)== ERROR)
                return ERROR;
            }
        }
       
    }



}