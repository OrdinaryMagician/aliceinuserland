CFLAGS := -std=c99 -Wall -Wextra -pedantic -O2 -pipe -Wno-unused-function -Wno-unused-parameter
PREFIX ?= /usr/local
.PHONY : clean install
all: echo true false sleep cat yes
echo: echo-obj helpers-obj
	$(CC) $(CFLAGS) obj/helpers.o obj/echo.o -o bin/echo
echo-obj:
	$(CC) $(CFLAGS) -c src/echo.c -o obj/echo.o
true: true-obj
	$(CC) $(CFLAGS) obj/true.o -o bin/true
true-obj:
	$(CC) $(CFLAGS) -c src/true.c -o obj/true.o
false: false-obj
	$(CC) $(CFLAGS) obj/false.o -o bin/false
false-obj:
	$(CC) $(CFLAGS) -c src/false.c -o obj/false.o
sleep: sleep-obj
	$(CC) $(CFLAGS) obj/sleep.o -o bin/sleep
sleep-obj:
	$(CC) $(CFLAGS) -c src/sleep.c -o obj/sleep.o
cat: cat-obj
	$(CC) $(CFLAGS) obj/cat.o -o bin/cat
cat-obj:
	$(CC) $(CFLAGS) -c src/cat.c -o obj/cat.o
yes: yes-obj
	$(CC) $(CFLAGS) obj/yes.o -o bin/yes
yes-obj:
	$(CC) $(CFLAGS) -c src/yes.c -o obj/yes.o
helpers-obj:
	$(CC) $(CFLAGS) -c src/helpers.c -o obj/helpers.o
clean:
	rm -f bin/*
	rm -f obj/*
install: install-echo install-true install-false install-sleep install-cat install-yes
install-echo: install-prepare
	cp bin/echo "$(PREFIX)/bin/"
install-true: install-prepare
	cp bin/true "$(PREFIX)/bin/"
install-false: install-prepare
	cp bin/false "$(PREFIX)/bin/"
install-sleep: install-prepare
	cp bin/sleep "$(PREFIX)/bin/"
install-cat: install-prepare
	cp bin/cat "$(PREFIX)/bin/"
install-yes: install-prepare
	cp bin/yes "$(PREFIX)/bin/"
install-prepare:
	mkdir -p "$(PREFIX)/bin"
