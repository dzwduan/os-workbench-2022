/*
 * @Date: 2022-06-18 17:17:33
 * @LastEditors: zhenwei duan
 * @LastEditTime: 2022-06-18 17:23:01
 * @FilePath: /jyy-os/lec3/demo.c
 */
#include "thread.h"

//运行需要加上 -lpthread

void Ta() {
    while (1);
        printf("a");
}


void Tb() {
    while (1);
        printf("b");   
}


int main() {
    create(Ta);
    create(Tb);
}