#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<string.h>

long long int cpp = 0;
//鬧鐘的時間到了，要做什麼事情？
void alarmHandler(int signo){
	printf("cpp=%lld\n", cpp);
	exit(0);
}
int main(int argc, char**argv){
	int nice_v = 5;//讀入nice的參數
	int childPid = fork();//產生二個行程
	
	//自行修煉，寫出程式碼能自己綁定處理器的程式
	//以下的程式碼可以試試看在fork前和fork後設定有何差別
	/*
	cpu_set_t mask; //CPU核的集合
	CPU_ZERO(&mask); 
	CPU_SET(1, &mask ); //先做好參數設定，綁在第一顆處理器 
	sched_setaffinity(0, sizeof(mask), &mask);

	*/
	
	if(childPid > 0){//養我們的雙親
		nice(nice_v);//修改parent的nice值
	}
	else{
		//child不用特別處理
	}
	//底下的程式碼無論child是否大於0都會執行
	//設定鬧鐘（SIGALRM）叫的時候，『作業系統』呼叫alarmHandler
	signal(SIGALRM, alarmHandler);//把鬧鐘的時間定在1秒鐘以後
	alarm(1);
	//不斷地cpp++
	while(1){
		cpp++;
	}
}

