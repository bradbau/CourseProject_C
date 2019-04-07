#ifndef _DISPLAY_H_
#define _DISPLAY_H_


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <dirent.h>
#include <sys/stat.h>
#include<sys/types.h>
#include"cnfparser.h"
#include"solver.h"

#ifdef __cplusplus
extern "C"
{
#endif


// measuring the effiency of solver on single cnf case  return time comsumed 
extern int CaseRunner_single(char * filename, int(*solver)(cnf_fmla *), char * resultDir);

//measure the effience in batch 
//traverse the case file 
extern int CaseRunner_batch(char *filefolder, int(*solver)(cnf_fmla *), char * resultDir);

//construct an display string of cnf formula
extern char * Displaycnf(cnf_fmla *phi);

extern char * AddClsStr(cnf_clause *preCls, char *cnfStr, int cnfstrsize);

void mkdirs(char *muldir);//make mutiple directorys 


#ifdef __cplusplus
}
#endif
#endif // !_DISPLAY_H_
