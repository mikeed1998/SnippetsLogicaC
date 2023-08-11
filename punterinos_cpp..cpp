#include <iostream>

using namespace std;

void _13_stack_vs_heap(void) {
	int a;		// goes on stack
	int *p;

	p = new int;
	*p = 10;
	delete p;

	p = new int[20];
	delete[] p;
}

int main() {
	_13_stack_vs_heap();

	return 0;
}