#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

static int num_called = 0;

int omp_tasks(int v) {
	++num_called ;
	int a, b;
	if( v <= 2 ) {
		return 1;
	} else {
		#pragma omp task shared(a,b)
		a = omp_tasks(v-1);
		#pragma omp task shared(a,b)
		b = omp_tasks(v-2);
		#pragma omp taskwait
		return a + b;
	}
}

int main() {
	int res;
	#pragma omp parallel
	{
		#pragma omp master
		res = omp_tasks(5);
	}
	printf("res=%d\n", res);
	printf("num_called=%d\n",  num_called);
	return 0;
}
