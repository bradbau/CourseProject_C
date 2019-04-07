#ifndef _SUDOPART_H_
#define _SUDOPART_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"cnfparser.h"

//***************def the data structure of sudo
//in game, single box in sudo has property of cnf formula
typedef struct sudobox{
    int num;  // 0 means no number, else has num of 1-9
    int  isempty; // whether it is a blank
    //if isempty ==1,then has the following property
    int inputnum;
    int possiblenum[9]; // for possiblenum[i]==0. then this hole cannot fill i+1
    int Ltrlindex[9]; // 
} *sudoboxptr,sudobox;

typedef struct sudomat{
    int usercord[2];// the chosen box cordinate
    sudobox boxitem[9][9];
} *sudomatptr, sudomat;

//********************randomly create sudo mat
extern sudomatptr generate_sudoku(int level);
extern void InitialMat(sudomatptr sudo);
extern void exchangerow(sudomatptr sudo, int r1, int r2);//accept
extern void exchangecol(sudomatptr sudo, int c1, int c2);
extern int randseq(int min, int max);
extern int SetEmptyBox(sudomatptr sudo, int emptynum);

extern int  winningchecek(sudomatptr sudo);







#endif
