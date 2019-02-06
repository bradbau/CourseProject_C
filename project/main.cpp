#include"cnfparser.h"

#define DEBUG


int main()
{
    //
    cnf_fmla* Phi;
    char filename[80];
    strcpy(filename , "D://__Learningmate//CourseProject//SATcase//base//functionality//sat-20.cnf");
    Phi = cnfStdLoad(filename);

    return 0;

}

