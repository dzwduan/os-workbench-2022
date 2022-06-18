/*
 * @Date: 2022-06-17 21:37:43
 * @LastEditors: zhenwei duan
 * @LastEditTime: 2022-06-18 00:19:03
 * @FilePath: /jyy-os/pstree/pstree.c
 */
#include <stdio.h>
#include <assert.h>
#include <getopt.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

int array[10000];
int idx = 0;

static int parse_args(int argc, char *argv[]);

int main(int argc, char *argv[]) {
  parse_args(argc, argv);
}


//1.获取命令行参数 ref ysyx
void show_pids() {}
void show_child() {}
void show_version() {}

static int parse_args(int argc, char *argv[]) {
  const struct option table[] = {
    {"show-pids"     , no_argument,   NULL, 'p'},
    {"numeric-sort"  , no_argument  , NULL, 'n'},
    {"version"       , no_argument,   NULL, 'V'},
    {"help"     , no_argument      , NULL, 'h'},
    {0          , 0                , NULL,  0 },
  };
  int o;
  while ( (o = getopt_long(argc, argv, "-pnVh", table, NULL)) != -1) {
    switch (o) {
      case 'p': show_pids(); break;
      case 'n': show_child(); break;
      case 'V': show_version(); break;
      default:
        printf("Usage: %s [OPTION...] \n\n", argv[0]);
        printf("\t-p,--show-pids          print pid of each process\n");
        printf("\t-n,--numeric-sort       print child of pid in sort\n");
        printf("\t-V,--version            print version\n");
        printf("\n");
        exit(0);
    }
  }
  return 0;
}


//2.获取系统中进程的编号
static int isdigitstr(char *str) {
  return (strspn(str, "0123456789") == strlen(str));
}

void show_pids() {
  DIR * dir;
  struct dirent *ptr;

  if ((dir = opendir("/proc")) == NULL) {
    perror("Open dir error...");
    exit(1);
  }

  while ((ptr = readdir(dir))) {
    if (isdigitstr(ptr->d_name)) {
      array[idx++] = ptr->d_name;
    }
  }
}


//3.