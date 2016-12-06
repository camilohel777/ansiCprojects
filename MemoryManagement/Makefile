CC=gcc
CFLAGS= -I.
DEPS = testcall.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
     
testcall: testcall.o
	gcc -o testcall testcall.o -I.
