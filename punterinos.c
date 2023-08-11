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
void _08_character_arrays_and_pointers_2(void);
void _08_01_print(char*);
void _09_character_arrays_and_pointers_3(void);
void _09_01_print(char*);
void _09_02_print(const char*);
void _10_pointers_and_multidimensional_arrays(void);
void _11_pointers_and_multidimensional_arrays_2(void);
void _11_01_func(int*);				// Argument: 1-D array of integers (Static) and (Dynamic)
void _11_02_func(int(*)[]);			// Argument: 2-D array of integers (Static)
void _11_03_func(int(*)[2][2]);		// Argument: 3-D array of integers (Static)
void _12_pointers_and_dynamic_memory(void);
void _13_stack_vs_heap(void);
void _14_malloc_calloc_realloc_free(void);
void _15_pointers_as_function_returns(void);
int* _15_01_add(int*, int*);
void _16_function_pointers(void);

int main(int argc, char const *argv[])
{
	_15_pointers_as_function_returns();
	
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
	char c[5];
	
	c[0] = 'J';
	c[1] = 'O';
	c[2] = 'H';
	c[3] = 'N';
	c[4] = '\0';

	int len = strlen(c);

	printf("String: %s, length = %d\n", c, len);

	char c2[] = "JOHN";
	printf("Size in bytes = %d\n", sizeof(c2));
	len = strlen(c2);
	printf("String: %s, length = %d\n", c2, len);

	char c3[5] = {'J', 'O', 'H', 'N', '\0'};
	len = strlen(c3);
	printf("String: %s, length = %d\n", c3, len);
}

void _08_character_arrays_and_pointers_2(void) {
	// Arrays are always passed to function by reference
	char c[20] = "Hello";

	_08_01_print(c);
}

void _08_01_print(char* c) {
	while(*c != '\0') {
		printf("%c", *c);
		c++;
	}
	printf("\n");
}

void _09_character_arrays_and_pointers_3(void) {
	char c[20] = "Hello";		// string gets stored in the space for array
	// char *c = "Hello"; 				// string gets stored as compile time constant
	_09_01_print(c);
	_09_02_print(c);
}

void _09_01_print(char* c) {
	c[0] = 'A';

	while(*c != '\0') {
		printf("%c", *c);
		c++;
	}
	printf("\n");
}

void _09_02_print(const char* c) {
	while(*c != '\0') {
		printf("%c", *c);
		c++;
	}
	printf("\n");
}

void _10_pointers_and_multidimensional_arrays(void) {
	int c[3][2][2] = {
		{ {2, 5}, {7, 9} },
		{ {3, 4}, {6, 1} },
		{ {0, 8}, {11, 13} }
	};

	printf("%d %d %d %d\n", c, *c, c[0], &c[0][0]);
	printf("%d\n", *(c[0][0] + 1));
}

void _11_pointers_and_multidimensional_arrays_2(void) {
	int a[2] = {1, 2};
	int b[2][3] = {{2,4,6}, {5,7,8}};		// B returns int (*)[3]
	int c[3][2][2] = {
		{ {2, 5}, {7, 9} },
		{ {3, 4}, {6, 1} },
		{ {0, 8}, {11, 13} }
	};

	
	int x[2][4];

	_11_01_func(a);		// A returns int*
	_11_02_func(b);		// A returns int(*)[]
	_11_03_func(c);		// A returns int(*)[][]

}

void _11_01_func(int *A) {
	printf("int*\n\n");
}

void _11_02_func(int (*A)[3]) {
	printf("int(*)[]\n\n");
}

void _11_03_func(int (*A)[2][2]) {
	printf("int(*)[][]\n\n");
}

void _12_pointers_and_dynamic_memory(void) {
	/*
		Application Memory
		
		------------------
		|      Heap      | ------> Free Store (Dynamic Memory Allocation)
		------------------
		|      Stack     | ------> Function calls and local variables
		------------------
		|  Static/Global | ------> Static and Global variables
		------------------
		|   Code (Text)  | ------> Instructions
		------------------
	*/
	/*
		Dynamic Memory functions:

		C:
			malloc
			calloc
			realloc
			free
		C++:
			new
			delete
	*/
}

void _13_stack_vs_heap(void) {
	int a; 		// goes on stack
	int *p;

	p = (int*)malloc(sizeof(int));
	*p = 10;
	free(p);

	p = (int*)malloc(20 * sizeof(int));
	*p = 20;
	free(p);
}

void _14_malloc_calloc_realloc_free(void) {
	// Allocate block of memory
	/*
		malloc - void* malloc(size_t size); 				|_ unsigned int _| return block of memory of X bytes
		calloc - void* calloc(size_t num, size_t size); 	|_ unsigned int, unsigned int _| return inicialized by 0 block of memory of X bytes
		realloc - void* realloc(void* ptr, size_t size); 	|_ void*, unsigned int _| return reallocated new X size of memory for a existent block of memory of X bytes 
	*/

	// Deallocate block of memory
	/*
		free - void free(void*);
	*/

	int n;
	printf("Enter the size of array\n");
	scanf("%d", &n);

	int *A = (int*)malloc(n * sizeof(int));

	for(int i = 0; i < n; i++) {
		A[i] = i + 1;
	}

	for(int i = 0; i < n; i++) {
		printf("%d ", A[i]);
	}

	free(A);
	A = NULL; // After free, adjust pointer to NULL

	printf("\n");

	int *B = (int*)calloc(n, sizeof(int));

	for(int i = 0; i < n; i++) {
		printf("%d ", B[i]);
	}

	free(B);
	B = NULL;

	printf("Enter the size of array\n");
	scanf("%d", &n);

	int *C = (int*)malloc(n * sizeof(int));

	for(int i = 0; i < n; i++) {
		C[i] = i + 1;
	}

	int *D = (int*)realloc(C, (n/2)*sizeof(int));
	// int *C = (int*)realloc(C, 0); // equivalent to free(C)
	// int *B = (int*)realloc(NULL, n*sizeof(int)); // equivalent to malloc

	printf("Prev block address = %d, new address = %d\n", C, D);

	for(int i = 0; i < 2 * n; i++) {
		printf("%d\n", D[i]);
	}
}

void _15_pointers_as_function_returns(void) { // calling function
	int a = 2, b = 4;
	// call by value
	printf("Address of a in main = %d\n", &a);
	int* ptr = _15_01_add(&a, &b);
	printf("Address of a = %d, Address of b = %d\n", &a, &b);
	printf("Sum = %d\n", *ptr); 	// value in a of main is copied to a fo add
								// value in b of main is copied to b fo add
}

int* _15_01_add(int* a, int* b) { // called function
	// a and b pointer to integers local to add
	printf("Address of a in Add = %d\n", &a);
	printf("Value in a of add (address of a of main) = %d\n", a);
	printf("Address at address stored in a of add = %d\n", *a);
	int* c = (int*)malloc(sizeof(int));
	*c = *(a) + *(b);
	return c;
}

void _16_function_pointers(void) {

}






