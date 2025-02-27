
#ifndef _SUDOKU_H
#define _SUDOKU_H

#include<vector>
#include<set>
#include<cstdlib>
#include"cnfparser.h"
#include"sudopart.h"
typedef std::vector<int>  vint;
typedef std::vector<vint> vvint;
typedef std::set<int> sint;
typedef std::set<std::pair<int, int> > spairii;
class SudoKu
{
private:
    const int hardclass;
    int checktemp;//临时变量，不再一直调用vvnum[][]
    vvint vvnum;
    vvint initialmat;
    vvint result;

    void change_Number();//初始化9×9格子
    //5个初始化算法
    void change_value(int lhs,int rhs);
    void swap_col(int lhs,int rhs);
    void swap_row(int lhs,int rhs);
    void swap_threecol(int lhs,int rhs);
    void swap_threerow(int lhs,int rhs);

    int onlyone(int a,int b);
public:
    ~SudoKu(){}
    explicit SudoKu(int a);

    const vint & operator[](int a)const{return vvnum[a];}

    vint & operator[](int a){return vvnum[a];}
    vvint copy();
    void set(const vvint& vec);

    vvint getdata();
    const vvint& getresult(){return result;}

    //same num check
    void check1(int a, int b, spairii &vecpr);

    //only number check
    void check2(int a, int b, spairii &vecpr);

    bool haswrong(int a, int b);
    bool haswrong2(int a, int b);
    bool checkwin();

    sudomatptr sudotransfer();
    //void show();
};

//Assist class
class GameLevel
{
private:
    const int level;
    std::vector<std::vector<bool> >defaultshow;//9×9的显示方式
    vint ways;//显示方式,每行显示出来几个

    void setlevel();//所有设置，调用下两个函数

    void sayEasyWays();//设置成员ways
    void sayMediumWays();
    void sayHardWays();
    void sayHellWays();

    void generate_map();//设置defaultshow，调用下一函数

    void changeRow(std::vector<bool>&,int);

public:
    const std::vector<bool>& operator[](int a)const{return defaultshow[a];}

    explicit GameLevel(int a):level(a),
        defaultshow(9,std::vector<bool>(9,0)),ways(9,0)
        {setlevel();generate_map();}
    
    //void show();
};

class SudokuCrack
{
public:
    SudokuCrack(vvint &);
    int beginCrack();
private:
    bool checkwin();
    int selectBetter();//选择最优点
    int countLackNum(int i, int j);//统计x,y对应坐标的可能数目
    sint& getLackedNumSet( int i, int j );
    int attemptLocate( int i, int j);//对最优点进行猜


    vvint vvnum;//0是没有数字，1-9为正常数字
    static int times;
};

#endif
