#include"sudopart.h"

extern sudomatptr generate_sudoku(int level){
    sudomatptr sudo = NULL;
    InitialMat(sudo);
    // change rows and cols
    int changeround = 20;
    while(changeround--){
        int rangeseed = randseq(1, 3);
        int Lowerrange = (rangeseed-1)*3 + 1;
        int Upperrange = rangeseed*3;
        exchangecol(sudo, randseq(Lowerrange, Upperrange), randseq(Lowerrange, Upperrange));
        exchangerow(sudo, randseq(Lowerrange, Upperrange), randseq(Lowerrange, Upperrange));
    }
    //set empty box by level
    if(level==1){
        if(SetEmptyBox(sudo, 30)==ERROR)
        return ERROR;
    }
    else if(level ==2){
        if(SetEmptyBox(sudo, 45)==ERROR)
        return ERROR;
    }
    else if (level ==3)
    {
        if(SetEmptyBox(sudo, 65)==ERROR)
        return ERROR;
    }



    return sudo;
}

extern void InitialMat(sudomatptr sudo){
    sudo = (sudomatptr)malloc(sizeof(sudomat));

    int i, j;
    for(i = 0; i<9 ;++i){
        for(j = 0; j<9; ++j){
            sudo->boxitem[i][j].num= ((i-1)*3+j)%9+ i/3;//get standard layout of
            sudo->boxitem[i][j].isempty=0;
        }
    }

}


extern void exchangerow(sudomatptr sudo, int r1, int r2){
    int i;
    for(i=0; i<9; ++i){
        int buk = sudo->boxitem[r1][i].num;
        sudo->boxitem[r1][i].num = sudo->boxitem[r2][i].num;
        sudo->boxitem[r2][i].num = buk;
    }
}

extern void exchangecol(sudomatptr sudo, int c1, int c2){
    int i;
    for(i=0; i<9; ++i){
        int buk = sudo->boxitem[i][c1].num;
        sudo->boxitem[i][c1].num = sudo->boxitem[i][c2].num;
        sudo->boxitem[i][c2].num = buk;
    }
}



extern int randseq(int min, int max){
    if(max>min)
    return rand()%(max-min)+min;
    if(max<min)
    return rand()%(min-max)+max;
    else 
    return 0;
}

extern int SetEmptyBox(sudomatptr sudo, int emptynum){
    int x, y;
    while(emptynum){
        x = randseq(0,8);
        y = randseq(0,8);
        if(sudo->boxitem[x][y].isempty==0){
            sudo->boxitem[x][y].isempty=0;
            emptynum--;
        }
    }
    return OK;
}
extern int  winningchecek(sudomatptr sudo){
    int i, j;
    int numset[9]= {0};
    //row check
    for(i = 0; i<9; ++i){
        for(j=0; j<9; ++j){
            if(sudo->boxitem[i][j].isempty==0){
                if(numset[sudo->boxitem[i][j].num-1]==0){
                    numset[sudo->boxitem[i][j].num-1]++;
                }
                else return FALSE;
            }
            else{
                    if((sudo->boxitem[i][j].inputnum!=0)&&(numset[sudo->boxitem[i][j].inputnum-1]==0)){
                        numset[sudo->boxitem[i][j].inputnum-1]++;
                    }
                else return FALSE;
            }
        }
        memset(numset, 0, 9*sizeof(int));
    }
    //column check
    for(i = 0; i<9; ++i){
        for(j=0; j<9; ++j){
            if(sudo->boxitem[j][i].isempty==0){
                if(numset[sudo->boxitem[j][i].num]==0){
                    numset[sudo->boxitem[j][i].num]++;
                }
                else return FALSE;
            }
            else{
                if((sudo->boxitem[j][i].inputnum!=0)&&(numset[sudo->boxitem[j][i].inputnum-1]==0)){
                    numset[sudo->boxitem[j][i].inputnum]++;
                }
                else return FALSE;
            }
        }
        memset(numset, 0, 9*sizeof(int));
    }
    //middle box check
    int p,q;
    for(p=0; p<3; p++){
        for(q=0; q<3; q++){
            //start the check in one middle box
            for(i = 0; i<3; ++i){
                for(j = 0; j<3; ++j){
                    int cordX = 3*p+i;
                    int cordY = 3*q+j;
                    if (sudo->boxitem[cordX][cordY].isempty == 0)
                    {
                        if (numset[sudo->boxitem[cordX][cordY].num-1] == 0)
                        {
                            numset[sudo->boxitem[cordX][cordY].num-1]++;
                        }
                        else
                            return FALSE;
                    }
                    else
                    {
                        if ((sudo->boxitem[cordX][cordY].inputnum!=0)&&(numset[sudo->boxitem[cordX][cordY].inputnum-1]==0))
                        {
                            numset[sudo->boxitem[cordX][cordY].inputnum-1]++;
                        }
                        else
                            return FALSE;
                    }
                }
            }
            memset(numset, 0, 9*sizeof(int));
        }
    }
    return TRUE;

}
