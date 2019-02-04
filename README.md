
# project 内容说明
### cnfparser
该部分包括.c和.h文件，对主程序会使用到的cnf公式阅读以及解析生成对应链表的外部函数解析得到存储公式的结构体（根据时间优化设计或者按照要求中的链表结构）
+ 结构体使用



>但是真正能够将算法从理论水平推向实际问题的应用，能够对大规模的实例进行求解，算法的数据结构则起着至关重要的作用。
_陈稳. 基于DPLL的SAT算法的研究与应用.硕士学位论文，电子科技大学，2011_


本次实验使用了htLS结构，即Head/Tail Lists with Literal Sifting
__

>Joao P. Marques-Silva. Algebraic simplification techniques for propositional satisfiability. In
Proceedings of the International Conference on Principles and Practice of Constraint
59
Programming, pp. 537-542, September 2000

上述文献中对suitable data structures进行了讨论，并且分析了对大多数数据结构的优化，by special handling of small clauses。




### solver
包括.c 和.h文件， 包含判断cnf公式（结构体输入）是否为真的函数dpll，返回标准结果
+ 可优化内容
    - 公式预处理器
        >实验统计表明，一般基于DPLL的可满足性问题算法的运
        行总时间有80％--90％耗费在BCP过程中。
        BCP过程是最简单的优化过程，然而其也是到目前为止最有效的一种正向推理技术，对于DPLL算法性能的提高有着决定性的作用
        _熊伟.可满足性问题DPLL算法研究.硕士学位论文, 复旦大学,2007_


    - 每一步判断文字的选择
    在基本算法中包含一个决定下一步处理文字的函数，优化算法中用参数决定使用优化函数
        >最短子句出现频率最大(MOM,Maximum Occurrence in Minimization)方法

        >独立下降式变量和(VSIDS，Variable State Independent Decaying Sum)方

        >最短正子句优先策略

        >基于冲突分析和学习的非时序回溯

    - 添加学习子句与删除机制得到非同步回溯
    引入文字蕴含图，
        >一般来讲学习子旬长度越短对将来搜索空间的剪除效果越大，因此目前最先进的SAT解决器如zChaff,Minisat等均是采用第一蕴含点切割线的方法(IUIP)进行子句学习的．
         _熊伟.可满足性问题DPLL算法研究.硕士学位论文, 复旦大学,2007_


解函数包括基本版本与优化版
+ 基本版与优化插件位置






### sudoku


### display
+ 时间计算模块
+ 数独交互页面模块
+ 性能测试，文件调用模块
