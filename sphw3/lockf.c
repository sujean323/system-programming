#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/file.h>
#include<string.h>
#define BUF_SIZE 4096

int main(){
    int x=0;
    char buf[BUF_SIZE];
    memset(buf, 0, BUF_SIZE);
    int fd=open("./lockf.db", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    int filesize=lseek(fd, 0, SEEK_END);
    for(int i=0;i<1000;i++){
	lockf(fd, F_LOCK, filesize);
	lseek(fd, 0, SEEK_END);
	lseek(fd, -4, SEEK_CUR);
        read(fd, buf, 4); //Read last number
        sscanf(buf, "%d", &x);
        lseek(fd, 0, SEEK_END);
        lseek(fd, x, SEEK_CUR);
        sprintf(buf, "%d", x+1);
        write(fd, buf, 4);
        lockf(fd, F_UNLCK, filesize);
        usleep(100000);
    }
    return 0;
}
