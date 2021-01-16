#include <fcntl.h>
#include <sys/mman.h>
#include "../lib/tlpi_hdr.h"


#define MEM_SIZE 10

int main(int argc, char *argv[]) {

    char *addr;
    int fd;

    /*使用 mmap 映射的文件*/
    char *filename = "/Users/carl/tmp/useless/mem.txt";

    /*使用 mmap 修改后的内容*/
    char *newVal = "thisNew";

    fd = open(filename, O_RDWR);
    if (fd == -1) {
        errExit("open");
    }


    addr = mmap(NULL, MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (addr == MAP_FAILED) errExit("mmap");
    if (close(fd) == -1) errExit("close"); /*映射完之后就可以直接关闭了*/


    printf("Current string=%.*s\n", MEM_SIZE, addr);

    memset(addr, 0, MEM_SIZE); /*Zero out region*/
    strncpy(addr, newVal, MEM_SIZE - 1);

    if (msync(addr, MEM_SIZE, MS_ASYNC) == -1) { /*类似于 fsync 和 storage 同步*/
        errExit("msync");
    }


    printf("Copied Success\n");
    return 0;
}
