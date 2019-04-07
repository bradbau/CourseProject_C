#include"cnfparser.h"
#include"solver.h"
#include"display.h"
//#define DEBUG


int main()
{
//test of cnfparser
#ifdef DEBUG
    cnf_fmla* phi;
    char filename[80];
    strcpy(filename , "D://__Learningmate//CourseProject//SATcase//base//functionality//sat-20.cnf");
    //strcpy(filename , "D://__Learningmate//CourseProject//SATcase//test//test.cnf");
    phi = cnfStdLoad(filename);
    int result = DPLL_basic(phi);
    printf("%d", result);
#endif


   // int res = CaseRunner_single("./SATcase/unsatisfied/eu-rand_net60-25-10.shuffled-3000.cnf", DPLL_basic, "./project/SATres_basic/unsatisfied");
   // int res = CaseRunner_single("./SATcase/test/7cnf20_90000_90000_7.shuffled-20.cnf", DPLL_improv_v1, "./project/SATres_v1/test");
   int res  = CaseRunner_batch("./SATcase/sudoku", DPLL_improv_v1, "./project/SATres_v1/sudoku");




    return 0;

}

