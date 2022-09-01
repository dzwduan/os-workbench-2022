#include<stdio.h>

int main() {
    unsigned *p;
    p = (void *)main;

    printf("%x\n", *p);
}

//gdb : info inferiors 获取进程号
//