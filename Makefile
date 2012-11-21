CC_gcc := gcc
CC_clang := clang
CFLAGS := -std=c99 -Wall -Wextra -O2 -pipe
LDFLAGS := -Wall -Wextra -O1
.PHONY : clean install
gcc: gcc-obj
	mkdir -p bin
	$(CC_gcc) $(LDFLAGS) obj/helpers.o obj/echo.o -o bin/echo
	$(CC_gcc) $(LDFLAGS) obj/true.o -o bin/true
	$(CC_gcc) $(LDFLAGS) obj/false.o -o bin/false
gcc-obj:
	mkdir -p obj
	$(CC_gcc) $(CFLAGS) -c helpers.c -o obj/helpers.o
	$(CC_gcc) $(CFLAGS) -c echo.c -o obj/echo.o
	$(CC_gcc) $(CFLAGS) -c true.c -o obj/true.o
	$(CC_gcc) $(CFLAGS) -c false.c -o obj/false.o
clang: clang-obj
	mkdir -p bin
	$(CC_clang) $(LDFLAGS) obj/helpers.o obj/echo.o -o bin/echo
	$(CC_clang) $(LDFLAGS) obj/true.o -o bin/true
	$(CC_clang) $(LDFLAGS) obj/false.o -o bin/false
clang-obj:
	mkdir -p obj
	$(CC_clang) $(CFLAGS) -c helpers.c -o obj/helpers.o
	$(CC_clang) $(CFLAGS) -c echo.c -o obj/echo.o
	$(CC_clang) $(CFLAGS) -c true.c -o obj/true.o
	$(CC_clang) $(CFLAGS) -c false.c -o obj/false.o
clean:
	rm -r bin
	rm -r obj
install:
	# we don't allow installing yet, sorry for the inconvenience
