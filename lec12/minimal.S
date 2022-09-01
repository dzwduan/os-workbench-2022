#include <sys/syscall.h>

# gcc -c minimal.S | ld minimal.o
# ./a.out 

.global _start
_start:
    movq $SYS_write, %rax
    movq $1, %rdi
    movq $st, %rsi
    movq $(ed-st), %rdx
    syscall

    movq $SYS_exit, %rax
    movq $1, %rdi
    syscall


#pmap pid看进程内存分布



st:
    .ascii "\033[01;31mHello, OS World\033[0m\n"
ed: