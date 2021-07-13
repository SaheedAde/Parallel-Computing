#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char** argv) {
	int n=15, num_threads=4;
	int a[n];
	int t[] = {0, 0, 0, 0};
	#pragma omp parallel for schedule(guided, 2)
	for (int i=0; i<n; i++) {
		a[i] = omp_get_thread_num();
		t[omp_get_thread_num()]++;
	}
	
	printf("guided, 2>>>>>>>>>>>>>>>\n"); 
	for(int i = 0; i < n; i++)
		printf("a = %d \n", a[i]); 
	for(int i = 0; i < num_threads; i++)
		printf("t%d= %d \n", i, t[i]); 
	return 0;
}
