/*
 * @Date: 2022-06-17 11:09:22
 * @LastEditors: zhenwei duan
 * @LastEditTime: 2022-06-17 11:15:36
 * @FilePath: /jyy-os/lec2/logisim.c
 */
#include<stdio.h>
#include<unistd.h>

//X-macro

#define REGS_FOREACH(_) _(X) _(Y)
#define RUN_LOGIC  X1 = !X && Y; \
                   Y1 = !X && !Y;

#define DEFINE(X)  static int X, X##1;
#define UPDATE(X)  X =X##1;
#define PRINT(X)   printf(#X " = %d; ", X);


int main() {
    //DEFINE(X)  DEFINE(Y)
    REGS_FOREACH(DEFINE);

    while (1) { //clock
        RUN_LOGIC;
        //PRINT(X)  PRINT(Y)
        REGS_FOREACH(PRINT);
        //UPDATE(X) UPDATE(Y)
        REGS_FOREACH(UPDATE);
        putchar('\n');
        sleep(1);
    }
}