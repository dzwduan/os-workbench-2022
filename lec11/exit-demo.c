#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/syscall.h>

void func() {
  printf("Goodbye, Cruel OS World!\n");
}

int main(int argc, char *argv[]) {
  atexit(func);

  if (argc < 2) return EXIT_FAILURE;

  if (strcmp(argv[1], "exit") == 0)
    exit(0);
  if (strcmp(argv[1], "_exit") == 0)
    _exit(0); //exit_group， 关闭整个线程组
  if (strcmp(argv[1], "__exit") == 0)
    syscall(SYS_exit, 0);  //只关闭一个线程,比较老
}

//使用静态链接编译，查看strace内容更加少


//fork, execve, exit 进程的创建 重置 销毁
