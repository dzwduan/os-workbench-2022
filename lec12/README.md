如何实现pmap?
1. strace pmap pid
发现一行 openat(AT_FDCWD, "/proc/44979/maps", O_RDONLY) = 3
cat /proc/44979/maps
00400000-00401000 r--p 00000000 08:05 4080170                            /home/dzw/jyy-os/lec12/a.out
00401000-00402000 r-xp 00001000 08:05 4080170                            /home/dzw/jyy-os/lec12/a.out
7ffff7ff9000-7ffff7ffd000 r--p 00000000 00:00 0                          [vvar]
7ffff7ffd000-7ffff7fff000 r-xp 00000000 00:00 0                          [vdso]
7ffffffde000-7ffffffff000 rw-p 00000000 00:00 0                          [stack]
ffffffffff600000-ffffffffff601000 --xp 00000000 00:00 0                  [vsyscall]
内容比pmap更加详细，pmap实际是对该文件的解析

man 5 proc 找maps
    address           perms offset  dev   inode       pathname
    00400000-00452000 r-xp 00000000 08:02 173521      /usr/bin/dbus-daemon
    00651000-00652000 r--p 00051000 08:02 173521      /usr/bin/dbus-daemon
    00652000-00655000 rw-p 00052000 08:02 173521      /usr/bin/dbus-daemon
    00e03000-00e24000 rw-p 00000000 00:00 0           [heap]
    00e24000-011f7000 rw-p 00000000 00:00 0           [heap]

[vdso] The virtual dynamically linked shared object.  See vdso(7).


静态链接和动态链接的起始地址不同，是因为地址空间随机化

vvar vdso是什么？

vdso在不进入系统调用的情况下完成系统调用
os给所有进程映射一个页面vvar, 直接查看该页面可以得到所需信息, man vdso查看不同arch支持哪些系统调用
   riscv functions
       The table below lists the symbols exported by the vDSO.

       symbol                   version
       ────────────────────────────────────
       __kernel_rt_sigreturn    LINUX_4.15
       __kernel_gettimeofday    LINUX_4.15
       __kernel_clock_gettime   LINUX_4.15
       __kernel_clock_getres    LINUX_4.15
       __kernel_getcpu          LINUX_4.15
       __kernel_flush_icache    LINUX_4.15

fast system call : 比INT操作更少
使用共享内存和内核通信来实现


gdb a.out 在starti时没有libc, 运行到main libc出现
mmap munmap 管理进程进程地址空间的系统调用
mmap可以将文件映射到进程的地址空间 strace a.out 会看到很多mmap
mmap可以很容易实现加载器, 只需要解析地址+mmap


pidof -- find the process ID of a running program.