#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SIZE 4096

int main() {
    int x=0;
    char buf[BUF_SIZE] = {0};
    //memset(buf, 0, BUF_SIZE);
    int fd = open("./flock.db", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    flock(fd, LOCK_EX); //Exclusive locks
    
    for (int i = 0; i < 1000; i++) {
    	lseek(fd, 0, SEEK_END);
    	lseek(fd, -BUF_SIZE, SEEK_CUR);
        read(fd, buf, BUF_SIZE);  //Read last number.
        sscanf(buf, "%d", &x);  //String to number (buf -> x).
        lseek(fd, 0, SEEK_END);
        lseek(fd, -x, SEEK_CUR);
        sprintf(buf, "%d", x+1);
        write(fd, buf, BUF_SIZE);
        usleep(100000);  //Sleep 0.1 sec.
    }
    flock(fd, LOCK_UN); //unlock
}
