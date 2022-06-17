/*
 * @Date: 2022-06-17 14:45:01
 * @LastEditors: zhenwei duan
 * @LastEditTime: 2022-06-17 15:07:10
 * @FilePath: /jyy-os/lec2/demo.c
 */
#include <stdio.h>
#include <sys/syscall.h>

int _start() {
    //printf("hello world\n");
    syscall(SYS_exit, 42);
}