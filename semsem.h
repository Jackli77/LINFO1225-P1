#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>
#include"mysem.h"
struct csem{
	int count;
	struct mysem B1;
	struct mysem B2;
	};

	
	void c_init(struct csem *a,int N){
	a->count = N;
	my_init(&(a->B1),1);
	my_init(&(a->B2),0);
	}
	
	void wait(struct csem*a){
		mywait(&(a->B1));
		a->count--;
		if(a->count<0){
			printf("block ");
			mypost(&(a->B1));
			mywait(&(a->B2));
		}
		mypost(&(a->B1));
	}
	void post(struct csem*a){
		mywait(&(a->B1));
		a->count++;
		if(a->count<=0){
			mypost(&(a->B2));
		}
		else{
			mypost(&(a->B1));
		}
	}
