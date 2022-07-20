#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 8
#define MAX_ITR 10

int f(int x){
	return x*x*x - 60*x*x + 900*x + 100;
}

typedef char sol[SIZE+1];

int decod(sol s){
	int val=0, i;
	for(i=0;i<SIZE;i++){
		val = val*2 + (s[i] - '0');
	}
}

void local_search(){
	sol s0="";
	int b, i;
	for(i=0;i<SIZE;i++){
		b=rand()%RAND_MAX;
		if((b%10)>5)
			s0[i]='1';
		else
			s0[i]='0';
	}
	sol s_best="", s_curr="", v[8], s_best_iter="";
	int f_best, f_curr, num_iter, j;
	
	strcpy(s_best,s0);
	strcpy(s_curr, s_best);
	f_best = f(decod(s_curr));
	num_iter=1;
	while(num_iter<=MAX_ITR){
		for(j=0;j<8;j++){
			strcpy(v[j], s_curr);
			if(v[j][j] == '0')
				v[j][j]='1';
			else
				v[j][j]='0';
			f_curr = f(decod(v[j]));
			if(f_curr<f_best){
				strcpy(s_best_iter, v[j]);
				f_best=f_curr;
			}
		}
		strcpy(s_curr, s_best_iter);
		num_iter++;
	}
	strcpy(s_best, s_best_iter);
	FILE *f;
	f = fopen("data.txt", "a");
	if(f==NULL){
		printf("Erreur");
		exit(1);
	}
	fprintf(f, "Remplacement\tMAX_ITR=%d\tSOLUTION=%s\n", MAX_ITR, s_best);
	fclose(f);
}

void local_search_inverse(){
	sol s0="";
	int b, i;
	for(i=0;i<SIZE;i++){
		b=rand()%RAND_MAX;
		if((b%10)>5)
			s0[i]='1';
		else
			s0[i]='0';
	}
	sol s_best="", s_curr="", s_iter="";
	int f_best, f_curr, num_iter;
	
	strcpy(s_best,s0);
	strcpy(s_curr, s_best);
	f_best = f(decod(s_curr));
	num_iter=1;
	int index1, index2, s;
	while(num_iter<=MAX_ITR){
		strcpy(s_iter, s_curr);
		index1=rand()%8;
		index2=rand()%8;
		if(index1>index2){
			int temp = index2;
			index2 = index1;
			index1 =  temp;
		}
		int n = index2-index1+1;
		for(s=0;s<n/2;s++){
			char tempc = s_iter[s+index1];
			s_iter[s+index1] = s_iter[index2-s];
			s_iter[index2-s] = tempc;
		}
		f_curr=f(decod(s_iter));
		if(f_curr<f_best){
			strcpy(s_curr, s_iter);
			f_best=f_curr;
		}
		num_iter++;
	}
	strcpy(s_best, s_curr);
	FILE *f;
	f = fopen("data.txt", "a");
	if(f==NULL){
		printf("Erreur");
		exit(1);
	}
	fprintf(f, "Inversion\tMAX_ITR=%d\tSOLUTION=%s\n", MAX_ITR, s_best);
	fclose(f);
}

int main(){
	local_search();
	local_search_inverse();
	return 0;
}
