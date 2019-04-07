#include"savesudo.h"

extern int SaveSudoku2cnf(sudomatptr sudo, char *filename){
    FILE * fp;
	//stuats result = OK;
    fp = fopen(filename, "w");
	if (!fp) return ERROR;	

	int i, j;
	fprintf(fp, "c cnf formula of the following sudoku\n");	
	for (i = 0; i < 9; i++) {
		fprintf(fp, "c ");	
		for (j = 0; j < 9; j++) {
			int num = sudo->boxitem[i][j].num;
			if (num == 0) fprintf(fp, ".");	
			else fprintf(fp, "%d", num );	
		}
		fprintf(fp, "\n");	
	}
	int ClauseNum = 0, LiteralNum = 0;
	char * fmlaStr = NULL;
	//malloc memory
	if ((fmlaStr = (char*)malloc(sizeof(char)*MAX_CNFFMLA_LENGTH)) == NULL)
		return ERROR;
	memset(fmlaStr, 0, sizeof(char)*MAX_CNFFMLA_LENGTH);

    if(sudotrans(sudo, fmlaStr, ClauseNum, LiteralNum)==ERROR){
		if (fmlaStr) free(fmlaStr);
		fprintf(fp, "ERROR");	
		fclose(fp);
		return ERROR;
	}
	//print the coment 
	fprintf(fp, "p cnf %d %d\n%s", LiteralNum, ClauseNum, fmlaStr);
	if(fmlaStr) free(fmlaStr);
	fclose(fp);

	if ( SaveSudomat(sudo, filename) == ERROR) return ERROR;
	else return OK;

}


extern int sudotrans(sudomatptr sudo, char *fmlaStr, int * clsnum, int *ltrlnum){
	//return string of cnf formula of sudoku
	if(Setsudoinfo(sudo)==ERROR) return ERROR; //set sudo solve information to the mat
	*ltrlnum = AssignLtrlIndex(sudo);
	//form clause by single numin one box
	fmlaStr = UniqueRule(sudo, fmlaStr, clsnum);

	//form clause by row and col
	fmlaStr = Rowalone(sudo, fmlaStr, clsnum);
	fmlaStr = Colalone(sudo, fmlaStr, clsnum);

	//
	fmlaStr= Boxalone(sudo, fmlaStr, clsnum);

	//
	fmlaStr = BoxExist(sudo, fmlaStr, clsnum);
	return OK;

}

extern int SaveSudomat(sudomatptr sudo, char * filename){
	//save the cnf information of sudo mat 
	
}

extern int Setsudoinfo(sudomatptr sudo){
	int i,j;
	for(i = 0; i<9; ++i){
		for(j = 0; j<9 ;++j){
			//for every single hole
			if(sudo->boxitem[i][j].isempty==1){
				//this is an empty box 
				int t;
				for(t = 0; t<9;++t){
					sudo->boxitem[i][j].possiblenum[t]=1;
				}
				for (t = 0; t < 9; t++) {
					if(sudo->boxitem[i][t].num!=0){
						sudo->boxitem[i][j].possiblenum[sudo->boxitem[i][t].num - 1] =0;
					}
				}
				for (t = 0; t < 9; t++) {
					if(sudo->boxitem[t][j].num!=0){
						sudo->boxitem[i][j].possiblenum[sudo->boxitem[t][j].num - 1] =0;
					}
				}
				int relaX, relaY;
				relaX =  i / 3 * 3;
				relaY = j / 3 * 3;
				int p, q;
				for(p =0; p<3; ++p){
					for(q+0; q<3; ++q){
						if(sudo->boxitem[relaX+p][relaY+q].num!=0){
							sudo->boxitem[i][j].possiblenum[sudo->boxitem[relaX+p][relaY+q].num - 1] =0;
						}
					}
				}

			}
		}
	}
	return OK;
}

extern int AssignLtrlIndex(sudomatptr sudo){
	int i,j, Ltrlnum = 0;
	for(i=0; i<9; ++i){
		for(j=0; j<9 ;++j){
			int t ;
			if(sudo->boxitem[i][j].isempty==1){
				for(t= 1; t<=9; ++t){
					if(sudo->boxitem[i][j].possiblenum[t-1]==1){
						Ltrlnum++;
						sudo->boxitem[i][j].Ltrlindex[t-1]==Ltrlnum;
					}
				}
			}
		}
	}
	return Ltrlnum;
}

char * BaseContradictClause(sudomatptr sudo, char *cnfstr, int *Clsnum, int x1, int y1, int x2, int y2){
	int i;
	for(i = 0; i<9;++i){
		int m = sudo->boxitem[x1][y1].Ltrlindex[i], n = sudo->boxitem[x2][y2].Ltrlindex[i];
		if((m!=0)&&(n!=0)&&(m<n)){
            int step = sprintf_s(cnfstr, Short_Length_C, "-%d -%d 0\n", m, n);
			cnfstr = cnfstr+ step;
			*Clsnum++;
		}
	}
	return cnfstr;
}

extern char * UniqueRule(sudomatptr sudo, char * cnfStr, int * Clsnum){
	int i, j, m, n;
	for (i = 0; i < 9; i++)
		for (j = 0; j < 9; j++)
			for (m = 0; m < 9; m++)
				for (n = m + 1; n < 9; n++) {	
					int m = sudo->boxitem[i][j].Ltrlindex[m], n = sudo->boxitem[i][j].Ltrlindex[n];
					if ((m != 0) && (n != 0)){
						int step = sprintf_s(cnfStr, Short_Length_C, "-%d -%d 0\n", m, n);
						cnfStr = cnfStr + step;	
						Clsnum++;		
					}
				}
	return cnfStr;
}

extern char * Rowalone(sudomatptr sudo, char * cnfStr, int *Clsnum) {
	int i, j, m;
	for (i = 0; i < 9; i++)
		for (j = 0; j < 9; j++)
			for (m = j + 1; m < 9; m++){	
				cnfStr = BaseContradictClause(sudo, cnfStr, Clsnum, i, j, i, m);	
			}
	return cnfStr;
}

extern char * Colalone(sudomatptr sudo, char * cnfStr, int *Clsnum) {
	int i, j, m;
	for (i = 0; i < 9; i++)
		for (j = 0; j < 9; j++)
			for (m = j + 1; m < 9; m++){	
				cnfStr = BaseContradictClause(sudo, cnfStr, Clsnum, j, i, m, i);	
			}
	return cnfStr;
}

extern char * Boxalone(sudomatptr sudo, char * cnfStr, int *Clsnum){
	int i, j, m, n;
	for (i = 0; i < 9; i++)
		for (j = 0; j < 9; j++) {
			int relaX = i / 3 * 3, relaY = j / 3 * 3;	
			for (n = 0; n < 3; n++)
				for (m = 0; m < 3; m++) {
					cnfStr = BaseContradictClause(sudo , cnfStr, Clsnum, i, j, relaX + n, relaY + m);	
				}
		}
	return cnfStr;
}	

extern char * BoxExist(sudomatptr sudo, char * cnfStr, int *Clsnum){
	int i, j, m;
	for (i = 0; i < 9; i++)
		for (j = 0; j < 9; j++) {	
			if (sudo->boxitem[i][j].num == 0) {	
				for (m = 0; m < 9; m++) {
					int Ltrl = sudo->boxitem[i][j].Ltrlindex[m];
					if (Ltrl != 0) {
						int step_var = sprintf_s(cnfStr, Unit_Length_C, "%d ", Ltrl);
						cnfStr = cnfStr + step_var;	
					}
				}
				int step_clause = sprintf_s(cnfStr, Unit_Length_C, "0\n");	
				cnfStr = cnfStr + step_clause;	
				Clsnum++;		
			}
		}
	return cnfStr;
}
