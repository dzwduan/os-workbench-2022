<!--
 * @Date: 2022-06-17 11:06:48
 * @LastEditors: zhenwei duan
 * @LastEditTime: 2022-06-17 13:21:12
 * @FilePath: /jyy-os/lec2.md
-->

# 什么是程序和编译器 `<br>`

## 状态机和数字电路 `<br>`

> 数字逻辑电路
> 状态 = 寄存器保存的值
> 初始状态 = RESET
> 迁移 = 组合逻辑电路计算寄存器下一周期的值

> c程序的状态机模型
> 状态 = 堆 + 栈
> 初始状态 = main的第一条语句
> 迁移 = 执行一条简单语句
> gdb实际上就是状态机视角

函数调用是什么?  push frame (frame.PC = 入口)
函数返回是什么? pop frame



## 构造最小的hello world

第一步，写出代码 `demo.c`

```c
#include <stdio.h>

int main() {
    printf("hello world\n");
}
```

编译 `gcc -c demo.c && objdump -d demo.o && ld a.o`

得到

> ld: warning: cannot find entry symbol _start; defaulting to 0000000000401000
> ld: demo.o: in function `main': demo.c:(.text+0x10): undefined reference to `puts'

修改

```c
int _start() {
    //printf("hello world\n");
}
```

此时运行 `gcc -c demo.c && objdump -d demo.o && ld demo.o出现`

> [1]    125124 segmentation fault (core dumped)  ./a.out

加上while(1)可以直接运行

使用 `size a.out`查看只有99 bytres

为什么不加while(1)无法执行，需要使用gdb调试，starti可以从第一条指令开始执行程序

> │  >0x401000 <_start>       endbr64                                                                                                                                                │
> │   0x401004 <_start+4>     push   %rbp                                                                                                                                            │
> │   0x401005 <_start+5>     mov    %rsp,%rbp                                                                                                                                       │
> │   0x401008 <_start+8>     nop                                                                                                                                                    │
> │   0x401009 <_start+9>     pop    %rbp                                                                                                                                            │
> │   0x40100a <_start+10>    retq

在retq出现错误，retq的具体行为

> rip <- m[rsp]
>
> rsp <- rsp + 8

x/16x打印得到 rsp对应的值是1，所以不能正常退出，加了while(1)死循环就不会有退出的问题


compiler barrier

加上"memory"会强制编译器不优化  

```c
asm volatile("nop"::"r"(x): "memory"));
```


strace => syscall trace  显示程序执行的系统调用


计算机世界没有魔法！
