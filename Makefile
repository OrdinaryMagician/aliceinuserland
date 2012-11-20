CC_gcc := gcc
CC_tcc := tcc
CC_llvm := clang
CFLAGS := --std=c99 -Wall -Wextra -pedantic -O2 -pipe
TCFLAGS := -Wall
.PHONY : clean install
gcc:
	mkdir -p bin
	$(CC_gcc) $(CFLAGS) echo.c -o bin/echo
tcc:
	mkdir -p bin
	$(CC_tcc) $(TCFLAGS) echo.c -o bin/echo
llvm:
	mkdir -p bin
	$(CC_llvm) $(CFLAGS) echo.c -o bin/echo
clean:
	rm -r bin
install:
	# we don't allow installing yet, sorry for the inconvenience
