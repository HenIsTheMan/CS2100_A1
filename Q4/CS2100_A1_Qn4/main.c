#include "Assg1Q4ans.h"

void funcDirect0(int a0){
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
	return; //jr $ra
}

void funcDirect1(int a0){
	int i = 32; //Originally t0

	int count = 0; //Originally v0

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
	return;
}

void funcDirect2(int a0){
	int i = 32;
	int count = 0;

	while(1){
		//* $L3 without "goto $L7;" at the end
		if(a0 >= 0){
			//* $L6
			++count;
			--i;
			//*/

			goto $L7; //Since $L7 follows $L6 in original
		}

		--i;
		//*/

	$L7:
		//* $L7
		if(i == 0){
			return; //$L8
		}

		a0 <<= 1;
		//*/
	}
}

int main(){
	funcDirect2(5);
}