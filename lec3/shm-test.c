/*
 * @Date: 2022-06-18 17:36:10
 * @LastEditors: zhenwei duan
 * @LastEditTime: 2022-06-18 17:36:21
 * @FilePath: /jyy-os/lec3/shm-test.c
 */
#include "thread.h"

//证明了线程可以共享内存
int x = 0;

//如果共享内存可以看到 hello 12345...
//如果不共享内存看到的一直为1，只需要将x 放进Thello函数测试

void Thello(int id) {
  usleep(id * 100000);
  printf("Hello from thread #%c\n", "123456789ABCDEF"[x++]);
}

int main() {
  for (int i = 0; i < 10; i++) {
    create(Thello);
  }
}
