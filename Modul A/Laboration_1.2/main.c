/*********************************************************
Ragnar Winblad von Walter, rwr21002, 199702221798
Datastrukturer, algoritmer och programkonstruktion, DVA244
Laboration 1.2
**********************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>

int sum(int num);

int main(void) {
	assert(sum(1) == 1);
	assert(sum(2) == 3);
	assert(sum(3) == 6);
	assert(sum(4) == 10);
	assert(sum(5) == 15);
	assert(sum(20) == 210);
	assert(sum(0) == 0);
	assert(sum(-1) == 0);

	printf("Enter number: ");
	int input;
	(void)scanf("%d", &input);

	int mySum = sum(input);
	return 0;
}
int sum(int num) {
	if (num < 1)
		return 0;
	printf("sum(%d) anropas\n", num);
	int fsum = num + sum(num - 1);
	printf("sum(%d) returnerar %d\n", num, fsum);
	return fsum;
}
