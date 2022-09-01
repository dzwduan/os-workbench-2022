#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  int n = 2;
  for (int i = 0; i < n; i++) {
    fork();
    printf("Hello\n");
    fflush(stdout);
  }
  for (int i = 0; i < n; i++) { 
    wait(NULL);
  }
}

//./a.out v.s. ./a.out | cat
//是因为向管道输出，fork拷贝了buffer的两个Hello\n, 使用fflush 或 setbuf(stdout, NULL)
//stdout分为 tty-> line buffer (换行打印) 和  file/pipe -> full buffer (4096byte 一起打印)
