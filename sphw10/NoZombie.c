/*
usage: ./NoZombie 10000
*/
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

void manyChild(int pid) {
    for (int i=0; i<100; i++) {
        pid = fork();
        if (pid == 0) {
        	sleep(i+1);
        	exit(1);
        }
        else continue;
    }
}

int main() {
    int pid;
    //sscanf(argv[1], "%d", &num);
    pid = fork();
    if (pid == 0) { //fake parent
        manyChild(pid);
        exit(0);
    }
    else{
    	int wstatus;
    	wait(&wstatus);
    }
    getchar();
}
