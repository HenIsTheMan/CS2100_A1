#include "Assg1Q4ans.h"

#include <stdio.h>

int almostFunc0(int a0){
	int t1; //Technically not in given qn

	int t0 = 32; //li $t0, 32

	int v0 = 0; //add $v0, $zero, $zero

	goto $L3; //j $L3

$L6:
	++v0; //addi $v0, $v0, 1

	--t0; //addi $t0, $t0, -1

$L7:
	//* beq $t0, $zero, $L8
	if(t0 == 0){
		goto $L8;
	}
	//*/

	a0 <<= 1; //sll $a0, $a0, 1

$L3:
	t1 = (a0 < 0) ? 1 : 0; //slti $t1, $a0, 0

	//* beq $t1, $zero, $L6
	if(t1 == 0){
		goto $L6;
	}
	//*/

	--t0; //addi $t0, $t0, -1

	goto $L7; //j $L7
$L8:
	return v0; //jr $ra
}

int almostFunc1(int a0){
	int i = 32; //Originally $t0

	int count = 0; //Originally $v0

	goto $L3;

$L6:
	++count;

	--i;

$L7:
	if(i == 0){
		goto $L8;
	}

	a0 <<= 1;

$L3:
	if(a0 >= 0){
		goto $L6;
	}

	--i;

	goto $L7;
$L8:
	return count;
}

int almostFunc2(int a0){
	int i = 32;
	int count = 0;

	while(1){
		//* $L3 without "goto $L7;" at the end
		if(a0 >= 0){
			//* $L6
			++count;
			--i;
			//*/

			goto $L7; //Since $L7 follows $L6 in original (can use else instead)
		}

		--i;
		//*/

	$L7:
		//* $L7
		if(i == 0){
			return count; //$L8
		}

		a0 <<= 1;
		//*/
	}
}

int almostFunc3(int a0){
	int i = 32;
	int count = 0;

	while(1){
		if(a0 >= 0){
			++count;
		}

		if(--i == 0){
			return count;
		}

		a0 <<= 1;
	}
}

int almostFunc4(int a0){
	int count = 0;

	for(int i = 32;;){ //Especially so if i used to be $t0, a temp register
		if(a0 >= 0){
			++count;
		}

		if(--i == 0){
			break; //Since return is below now
		}

		a0 <<= 1;
	}

	return count;
}

int main(){
	int i;
	int funcResult;
	int almostFunc0Result;
	int almostFunc1Result;
	int almostFunc2Result;
	int almostFunc3Result;
	int almostFunc4Result;

	for(long long int index = -1; index <= (long)9999999; ++index){ //Only 1 -ve val as only counting when a0 >= 0 so -1 represents all -ve vals
		i = (int)index;

		funcResult = func(i);
		almostFunc0Result = almostFunc0(i);
		almostFunc1Result = almostFunc1(i);
		almostFunc2Result = almostFunc2(i);
		almostFunc3Result = almostFunc3(i);
		almostFunc4Result = almostFunc4(i);

		if(funcResult != almostFunc0Result
			|| funcResult != almostFunc1Result
			|| funcResult != almostFunc2Result
			|| funcResult != almostFunc3Result
			|| funcResult != almostFunc4Result
		){
			(void)printf("almostFunc0: %d\n", almostFunc0Result);
			(void)printf("almostFunc1: %d\n", almostFunc1Result);
			(void)printf("almostFunc2: %d\n", almostFunc2Result);
			(void)printf("almostFunc3: %d\n", almostFunc3Result);
			(void)printf("almostFunc4: %d\n", almostFunc4Result);
			(void)printf("func: %d\n", funcResult);
			return -1;
		}
	}

	(void)printf("VERIFIED");
}