#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int omp_odd_counter(int *a, int n) {
	int i;
	int count_odd = 0;
	#pragma omp parallel for shared(a, count_odd)
	for(i=0; i<n; i++) {
		if( a[i] % 2 == 1 ) {
			count_odd++;
		}
	}
	return count_odd;
}

int main(int argc, char** argv) {
	int n=10, count_odd;
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	count_odd = omp_odd_counter(a, n);
	printf("NUMBER OF ODD IN ARRAY IS %d", count_odd);
	return 0;
}
