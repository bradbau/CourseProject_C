#ifndef SAVESUDO_H_
#define SAVESUDO_H_


#include"sudopart.h"

//#define SHORT_COUNT_M 10206
#define LONG_COUNT_M 81
#define SHORT_CLAUSE_M "-999 -999 0\n"		//短子句最大字符串
#define LONG_CLAUSE_M "111 222 333 444 555 666 777 888 999 0\n"	//长子句最大字符串
#define LONG_UNIT_M "111 "	//长子句最大单元
//#define NO_SUD 20	//无伴随sud文件警告
#define Short_Length_C  strlen(SHORT_CLAUSE_M) + 1	//短子句最大长度+/0
const int Long_Length_C = 64;	//长子句最大长度+/0
const int Unit_Length_C = 10;		//长子句最大单元最大长度+/0
#define MAX_CNFFMLA_LENGTH  10206 * Short_Length_C + LONG_COUNT_M * Long_Length_C

extern int SaveSudoku2cnf(sudomatptr sudo, char *filename);

extern int sudotrans(sudomatptr sudo, char *fmlaStr, int * clsnum, int *ltrlnum);

extern int SaveSudomat(sudomatptr sudo, char * filename);

extern int Setsudoinfo(sudomatptr sudo);

extern int AssignLtrlIndex(sudomatptr sudo);

extern char * BaseContradictClause(sudomatptr sudo, char *cnfstr, int *Clsnum, int x1, int y1, int x2, int y2);

extern char * UniqueRule(sudomatptr sudo, char * cnfStr, int * Clsnum);

extern char * Rowalone(sudomatptr sudo, char * cnfStr, int *Clsnum);
extern char * Colalone(sudomatptr sudo, char * cnfStr, int *Clsnum);
extern char * Boxalone(sudomatptr sudo, char * cnfStr, int *Clsnum);
extern char * BoxExist(sudomatptr sudo, char * cnfStr, int *Clsnum);
#endif // !SAVESUDO_H_
