#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>
#include"mysem.h"
struct csem{
	int count;};
	struct mysem B1;
	struct mysem B2;
	
	void c_init(struct csem *a,int N){
	a->count = N;
	my_init(&B1,1);
	my_init(&B2,0);
	}
	
	void wait(struct csem*a){
		mywait(&B1);
		a->count--;
		if(a->count<0){
			printf("block");
			mypost(&B1);
			mywait(&B2);
		}
		mypost(&B1);
	}
	void post(struct csem*a){
		mywait(&B1);
		a->count++;
		if(a->count<=0){
			mypost(&B2);
		}
		else{
			mypost(&B1);
		}
	}
