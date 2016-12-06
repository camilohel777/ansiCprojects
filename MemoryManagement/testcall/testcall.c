#include <stdio.h>
#include "testcall.h"

int main(void)
{
	//Different variables for allocating memory from small size to large size
	char* tester1, tester2, tester3, tester4;
	
	//performing memory allocation and assigning values to the pointers
	tester1 = (char*) malloc (7890);
	tester2 = (char*) malloc (1234567);
	tester3 = (char*) malloc (400500600);
	tester4 = (char*) malloc (9999999999);
	
	printf("Amount Claimed: [%d] bytes\n",syscall(__NR_get_slob_amt_free));
	printf("Amount Free: [%d] bytes\n",syscall(__NR_get_slob_amt_claimed));
	
	return 0;
}
