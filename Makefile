CFLAGS := -std=c99 -Wall -Wextra -Werror -pedantic -Os -pipe
UTILS := echo true false sleep cat yes printenv basename dirname head sync \
	 logname
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
	$(CC) $(CFLAGS) src/helpers.o src/cat.o -o bin/cat
yes:
	$(CC) $(CFLAGS) src/helpers.o src/yes.o -o bin/yes
printenv:
	$(CC) $(CFLAGS) src/printenv.o -o bin/printenv
basename:
	$(CC) $(CFLAGS) src/basename.o -o bin/basename
dirname:
	$(CC) $(CFLAGS) src/dirname.o -o bin/dirname
head:
	$(CC) $(CFLAGS) src/helpers.o src/head.o -o bin/head
sync:
	$(CC) $(CFLAGS) src/sync.o -o bin/sync
logname:
	$(CC) $(CFLAGS) src/logname.o -o bin/logname
veryclean: clean
	rm -f bin/*
clean:
	rm -f src/*.o
