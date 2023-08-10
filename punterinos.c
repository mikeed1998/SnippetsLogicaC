#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void _00_basics(void);
void _01_pointer_arithmetic(void);
void _02_pointer_types(void);
void _03_pointer_to_pointer(void);
void _04_pointers_as_function_arguments_call_by_reference(void);
void _04_01_increment(int);
void _04_02_increment_pointer(int*);
void _05_pointers_and_arrays(void);
void _06_arrays_as_function_arguments(void);
int _06_01_sumOfElements(int*, int);
void _06_02_double(int*, int);
void _07_character_arrays_and_pointers(void);

int main(int argc, char const *argv[])
{
	_07_character_arrays_and_pointers();
	
	return 0;
}

void _00_basics(void) {
	int a;
	int *p;

	a = 10;
	p = &a; 	// &a = address of a

	printf("%d\n", a);
	*p = 12;	// dereferencing
	printf("%d\n", a);

	printf("%d\n", p);
	printf("%d\n", *p);	//garbage	// *p- value at address pointed by p
	printf("%d\n", &a);
	
	printf("Address of P is %d\n", p);
	printf("Value at p is %d\n", *p);

	printf("%d\n", a);

	int b = 20;
	*p = b;

	printf("Address of P is %d\n", p);
	printf("Value at p is %d\n", *p);
}

void _01_pointer_arithmetic(void) {
	int a = 10;
	int *p = &a;

	printf("Address p is %d\n", p);			// p is x00002 
	printf("Value at Address p is %d\n", *p);
	printf("size of integer if %d bytes\n", sizeof(int));
	printf("Address p+1 is %d\n", p + 1);		// p is x00006		
	printf("Value at Address p+1 is %d\n", *(p + 1));	// garbage, no existe valor en p+1
}

void _02_pointer_types(void) {
	int a = 1025;
	int *p;

	p = &a;

	printf("Size of integer is %d\n", sizeof(int));
	printf("Address = %d, value = %d\n", p, *p);
	printf("Address = %d, value = %d\n", p+1, *(p+1));

	char *p0;
	p0 = (char*)p; // typecasting	

	printf("Size of char is %d\n", sizeof(char));
	printf("Address = %d, value = %d\n", p0, *p0);
	printf("Address = %d, value = %d\n", p0+1, *(p0+1));
	/*
		1025 = 00000000 00000000 00000100 00000001
								 p0+1 = 4  p0 = 1
	*/

	// Void Pointer - Generic Pointer
	void *ptr;
	ptr = p;

	printf("Size of void is %d\n", sizeof(void));
	printf("Address = %d\n", ptr);
	printf("Address = %d\n", ptr+1);
}

void _03_pointer_to_pointer(void) {
	int x = 5;
	int *p = &x;
	*p = 6;
	int **q = &p;
	int ***r = &q;

	printf("%d\n", *p);			// 6
	printf("%d\n", *q);			// x00004
	printf("%d\n", *(*q));		// 6
	printf("%d\n", *(*r));		// x00004
	printf("%d\n", *(*(*r)));	// 6
	***r = 10;
	printf("x = %d\n", x);
	**q = *p + 2;
	printf("x = %d\n", x);
}

void _04_pointers_as_function_arguments_call_by_reference(void) {
	int a;
	a = 10;
	
	_04_01_increment(a);
	printf("Address of variable a in increment = %d\n", &a);
	printf("Value of variable a in increment = %d\n", a);

	_04_02_increment_pointer(&a);
	printf("Address of variable a in increment = %d\n", &a);
	printf("Value of variable a in increment = %d\n", a);
}

void _04_01_increment(int a) {
	a = a + 1;
	printf("Address of variable a in increment = %d\n", &a);
}

void _04_02_increment_pointer(int *a) {
	*a = (*a) + 1;
	printf("Address of variable a in increment = %d\n", &a);
}

void _05_pointers_and_arrays(void) {
	int A[] = {2, 4, 5, 8, 1};

	// printf("%d\n", A);
	// printf("%d\n", &A[0]);
	// printf("%d\n", A[0]);
	// printf("%d\n", *A);

	int *p = A;
	// A++;		// invalid	
	// p++;		// valid

	int i;
	for(i = 1; i < 5; i++) {
		printf("Address = %d\n", A+i);
		printf("Address = %d\n", &A[i]);
		printf("Value = %d\n", A[i]);
		printf("Value = %d\n", *(A+i));
	}
}

void _06_arrays_as_function_arguments(void) {
	int A[] = {1, 2, 3, 4, 5};
	int size = sizeof(A) / sizeof(A[0]);
	int total = _06_01_sumOfElements(A, size);

	printf("Sum of elements = %d\n", total);

	_06_02_double(A, size);

	for (int i = 0; i < size; ++i)
	{
		printf("%d ", A[i]);
	}
}

int _06_01_sumOfElements(int *A, int size) {
	int i, sum = 0;
	for(i = 0; i < size; i++) {
		sum += A[i];
	}

	return sum;
}

void _06_02_double(int *A, int size) {
	int i;
	for(i = 0; i < size; i++) {
		A[i] = 2 * A[i];
	}
}

void _07_character_arrays_and_pointers(void) {

}