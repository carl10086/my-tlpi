//
// Created by 俞思真 on 2021/1/25.
//
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"


#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif


int main(int argc, char *argv[]) {

    int inputFd, outputFd, openFlags;
    mode_t filePerms;
    char buf[BUF_SIZE];

    if (argc != 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s old-file new-file\n", argv[0]);


    inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1)
        errExit("opening file %s", argv[1]);

    /*1. 不存在就创建; 2. 仅仅写; 3. 创建得时候文件 truncate -> 0 大小*/
    openFlags = O_CREAT | O_WRONLY | O_TRUNC;

    /*2. 设定创建文件得权限*/
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH;      /* rw-rw-rw- */


    outputFd = open(argv[2], openFlags, filePerms);
    if (outputFd == -1)
        errExit("opening file %s", argv[2]);

    ssize_t numRead;
    while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0) {
        if (write(outputFd, buf, numRead) != numRead) {
            fatal("write() returned error or partial write occurred");
        } else if (numRead == -1) {
            errExit("read failed");
        }
    }


    if (close(inputFd) == -1)
        errExit("close input");
    if (close(outputFd) == -1)
        errExit("close output");
    exit(EXIT_SUCCESS);
}

