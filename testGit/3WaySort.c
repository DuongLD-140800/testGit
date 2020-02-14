#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
typedef struct test {
	int key;
	char keyChar[30];
}test;

#define MAX 100000000
void printArray(int a[], int size) {
	for (int i = 0; i < size; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}
void memCpy(void *p1, const void *p2, size_t size) {
	const char *first = (const char *)p2;
	const char *last = (const char *)p2 + size;
	char *cpy = (char *)p1;
	while (first != last) *cpy++ = *first++; 
}
void exch(void *buff, int i, int j, size_t size) {
	void *swap = malloc(size);
	void *p1 = buff + i * size;
	void *p2 = buff + j * size;
	memCpy(swap, p1, size);
	memCpy(p1, p2, size);
	memCpy(p2, swap, size);
	free(swap);
}
void sort(void *buff, int l, int r, size_t size, int (*compare)(const void *, const void *)) {
	if (l > r) return;
	int i = l - 1, p = l - 1;
	int j = r, q = r;
	void *pevot = buff + r*size;
	while (1) {
		while(compare((buff + (++i)*size), pevot) < 0);
		while(compare((buff + (--j)*size), pevot) > 0) if(j == l) break;
		if (i >= j) break;
		exch(buff, i, j, size);
		if (compare((buff + i*size), pevot) == 0)
			exch(buff, i, ++p, size);
		if (compare((buff + j*size), pevot) == 0)
			exch(buff, j, --q, size);
	}
	exch(buff, i, r, size);
	j = i - 1;
	i = i + 1;
	for (int k = l; k <= p; k++) 
		exch(buff, k, j--, size);
	for (int k = r - 1; k >= q; k--) 
		exch(buff, k, i++, size);
	sort(buff, l, j, size, compare);
	sort(buff, i, r, size, compare);
}
// void sort(void* a, int size, int l, int r,
//                        int (*compare)(const void*, const void*)) {
// if (r <= l) return; int i = l-1, j = r; int p = l-1, q = r; 
// while(1) {
// 	while ( compare((char*)a+(++i)*size, (char*)a+r*size) < 0 );
// 	while (compare((char*)a+r*size, (char*)a+(--j)*size) < 0 )
// 		if (j == l) break;
// 	if (i >= j) break;
// 	exch(a, size, i, j);
// 	if (compare((char*)a+i*size, (char*)a+r*size)==0)
// 		exch(a, size, ++p, i);
// 	if (compare((char*)a+j*size, (char*)a+r*size)==0)
// 		exch(a, size, --q, j);
// 	}
// 	exch(a, size, i, r);
// 	j = i - 1;
// 	i = i + 1;
// 	for (int k = l ; k <= p; k++) exch(a, size, k, j--); 
// 	for (int k = r-1; k >= q; k--) exch(a, size, k, i++); 
// 	sort(a, size, l, j, compare);
// 	sort(a, size, i, r, compare);
// }
void createArray(int **a) {
	srand(time(NULL));
	*a = (int *) malloc(MAX * sizeof(int));
	for (int i = 0; i < MAX; ++i)
	{
		*(*a + i) = rand() % 10;
	}
}
int int_Compare(const void *x,const void *y) {
	int m = *((int *)x);
	int n = *((int *)y);
	if (m == n) return 0;
	return m > n ? 1:-1;
}
int struct_Compare(const void *x, const void *y) {
	test m = *((test *)x);
	test n = *((test *)y);
	return strcmp(m.keyChar, n.keyChar);
}
int main(int argc, char const *argv[])
{
	int *a = NULL;
	createArray(&a);

	clock_t start, end;
	double cpu_time_used;
	start = clock();
	sort(a, 0, MAX - 1, sizeof(int), int_Compare);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("cpu time : %f\n", cpu_time_used);
	free(a);
	return 0;
}
