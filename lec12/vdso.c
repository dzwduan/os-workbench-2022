
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

double gettime() {
  struct timeval t;
  gettimeofday(&t, NULL); // trapless system call
  return t.tv_sec + t.tv_usec / 1000000.0;
}

int main() {
  printf("Time stamp: %ld\n", time(NULL)); // trapless system call
  double st = gettime();
  sleep(1);
  double ed = gettime();
  printf("Time: %.6lfs\n", ed - st);
}


//gdb info inferiors
//pmap /proc/pid/maps 发现time位于vdso
//根据汇编读出的是vvar的内容, 但是不能访问这一段内存，x ($rip - 0x4967)