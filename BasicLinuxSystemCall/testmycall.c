//Camilo Rivera
//Camilo Riviere
//Testing and calling the system call
#include <stdio.h>
#include "testmycall.h"

int main(void)
{

	printf("%ld\n", syscall(__NR_mycall,5574139));

}
