CFLAGS := -std=c99 -Wall -Wextra -O2 -pipe
LDFLAGS := -Wall -Wextra -O1
PREFIX ?= /usr/local
.PHONY : clean install
all: echo true false sleep
echo: echo-obj helpers-obj
	$(CC) $(LDFLAGS) obj/helpers.o obj/echo.o -o bin/echo
echo-obj:
	$(CC) $(CFLAGS) -c src/echo.c -o obj/echo.o
true: true-obj
	$(CC) $(LDFLAGS) obj/true.o -o bin/true
true-obj:
	$(CC) $(CFLAGS) -c src/true.c -o obj/true.o
false: false-obj
	$(CC) $(LDFLAGS) obj/false.o -o bin/false
false-obj:
	$(CC) $(CFLAGS) -c src/false.c -o obj/false.o
sleep: sleep-obj
	$(CC) $(LDFLAGS) obj/sleep.o -o bin/sleep
sleep-obj:
	$(CC) $(CFLAGS) -c src/sleep.c -o obj/sleep.o
helpers-obj:
	$(CC) $(CFLAGS) -c src/helpers.c -o obj/helpers.o
clean:
	rm -f bin/*
	rm -f obj/*
install: install-echo install-true install-false install-sleep
install-echo: install-prepare
	cp bin/echo "$(PREFIX)/bin/"
install-true: install-prepare
	cp bin/true "$(PREFIX)/bin/"
install-false: install-prepare
	cp bin/false "$(PREFIX)/bin/"
install-sleep: install-prepare
	cp bin/sleep "$(PREFIX)/bin/"
install-prepare:
	mkdir -p "$(PREFIX)/bin"
