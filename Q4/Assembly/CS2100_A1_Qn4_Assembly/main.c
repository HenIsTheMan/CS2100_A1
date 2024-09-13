#include <stdio.h>

int main(){
	int a = 5;
	int b = 50;
	int result = 0;

	__asm{
		mov eax, a
		add eax, b
		mov result, eax
	}

	(void)printf("The result of %d + %d is %d\n", a, b, result);
}