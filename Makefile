CFLAGS := -std=c99 -Wall -Wextra -pedantic -O2 -pipe -Wno-unused-function -Wno-unused-parameter -Isrc/
PREFIX ?= /usr/local
.PHONY : clean install
UTILS := echo true false sleep cat yes printenv basename dirname head
SOURCES := $(patsubst %.c,%.o,$(wildcard src/*.c))
all: $(SOURCES) $(UTILS)
.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<
echo:
	$(CC) $(CFLAGS) src/helpers.o src/echo.o -o bin/echo
true:
	$(CC) $(CFLAGS) src/true.o -o bin/true
false:
	$(CC) $(CFLAGS) src/false.o -o bin/false
sleep:
	$(CC) $(CFLAGS) src/sleep.o -o bin/sleep
cat:
	$(CC) $(CFLAGS) src/cat.o -o bin/cat
yes:
	$(CC) $(CFLAGS) src/yes.o -o bin/yes
printenv:
	$(CC) $(CFLAGS) src/printenv.o -o bin/printenv
basename:
	$(CC) $(CFLAGS) src/basename.o -o bin/basename
dirname:
	$(CC) $(CFLAGS) src/dirname.o -o bin/dirname
head:
	$(CC) $(CFLAGS) src/head.o -o bin/head
clean:
	rm -f bin/*
	rm -f src/*.o
install:
	mkdir -p "$(PREFIX)/bin"
	cp -r bin/ "$(PREFIX)/bin/"
