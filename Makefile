CC_gcc := gcc
CC_clang := clang
CFLAGS := --std=c99 -Wall -Wextra -pedantic -O2 -pipe
.PHONY : clean install
gcc:
	mkdir -p bin
	$(CC_gcc) $(CFLAGS) echo.c -o bin/echo
	$(CC_gcc) $(CFLAGS) true.c -o bin/true
	$(CC_gcc) $(CFLAGS) false.c -o bin/false
clang:
	mkdir -p bin
	$(CC_llvm) $(CFLAGS) echo.c -o bin/echo
	$(CC_llvm) $(CFLAGS) true.c -o bin/true
	$(CC_llvm) $(CFLAGS) false.c -o bin/false
clean:
	rm -r bin
install:
	# we don't allow installing yet, sorry for the inconvenience
