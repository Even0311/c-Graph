#include"Graph.h"
using namespace gdwg;
#include "test.h"
#include<time.h>
int main(){
    gdwg:: Graph<int,int> g;
    g.addNode(0);
    for(int i=1 ;i< 501;++i){
        g.addNode(i);
        g.addEdge(i-1,i,i);
    }





    time_t start, ends;
    clock_t cstart,cends;

    start=time(NULL);
    cstart=clock();

    for(int i=0;i<500;++i){
        g.mergeReplace(i,i+1);
    }
    ends=time(NULL);
    cends=clock();

    std::cout << "时间差：" << difftime(ends,start) << std::endl;
    std::cout << "Clock时间差：" << cends-cstart << std::endl;




};