#include "thread.h"

#define N 100000

long sum = 0;

void Tsum() {
    for (int i=0; i<N; i++) sum++;

    //修改加上lock结果正确但是速度下降
    //asm volatile("lock add $1 , %0": "+m"(sum));
}


int main() {
    create(Tsum);
    create(Tsum);
    join();

    printf("sum = %ld\n", sum);
}


//如果优化O1， O2又不一样
//compiler barrier   asm volatile("":::"memory");    