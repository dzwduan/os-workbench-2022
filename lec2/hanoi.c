#include<stdio.h>
#include<assert.h>

//ref https://www.zhihu.com/question/24385418
void hanoi_r(int n, char from, char to, char via) {
    if (n == 1)
        printf("%c -> %c\n", from, to);
 
    else {
        hanoi_r(n-1, from, via, to);
        hanoi_r(1,  from,  to,  via);
        hanoi_r(n-1, via,  to,  from);
    }
    return ;
}


typedef struct {
    int pc, n;
    char from , to, via;
}Frame;

#define call(...)  ({*(++top) = (Frame){.pc = 0, __VA_ARGS__}; })
#define ret()      ({top--;})
#define goto(loc)  ({f->pc = (loc) - 1;})


void hanoi(int n, char from, char to, char via) {
    Frame stk[64], *top = stk - 1;
    //初始化第0个栈帧
    call(n ,from, to, via);

    //TODO: 不理解f->pc
    for (Frame *f; (f=top) >= stk; f->pc++) {
        switch (f->pc)
        {
        case 0:
            if (f->n==1) {
                printf("%c -> %c\n", f->from, f->to);
                goto(4);
            }
            break;
        case 1:
            call(f->n - 1, f->from, f->via, f->to);
            break;
        case 2:
            call(       1, f->from, f->to, f->via);
            break;
        case 3:
            call(f->n - 1, f->via, f->to, f->from);
            break;
        case 4:
            ret();
        default:
            assert(0);
        }
    }
}


int main() {
    hanoi(3, 'A', 'B', 'C');
}