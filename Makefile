CC_gcc := gcc
CC_tcc := tcc
CC_llvm := clang
CFLAGS := --std=c99 -Wall -Wextra -pedantic -O2 -pipe
TCFLAGS := -Wall
.PHONY : clean install
gcc:
	mkdir -p bin
	$(CC_gcc) $(CFLAGS) echo.c -o bin/echo
	$(CC_gcc) $(CFLAGS) true.c -o bin/true
	$(CC_gcc) $(CFLAGS) false.c -o bin/false
tcc:
	mkdir -p bin
	$(CC_tcc) $(TCFLAGS) echo.c -o bin/echo
	$(CC_tcc) $(TCFLAGS) true.c -o bin/true
	$(CC_tcc) $(TCFLAGS) false.c -o bin/false
llvm:
	mkdir -p bin
	$(CC_llvm) $(CFLAGS) echo.c -o bin/echo
	$(CC_llvm) $(CFLAGS) true.c -o bin/true
	$(CC_llvm) $(CFLAGS) false.c -o bin/false
clean:
	rm -r bin
install:
	# we don't allow installing yet, sorry for the inconvenience
