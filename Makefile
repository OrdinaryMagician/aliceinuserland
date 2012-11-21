CFLAGS := -std=c99 -Wall -Wextra -O2 -pipe
LDFLAGS := -Wall -Wextra -O1
PREFIX =? /usr/local
.PHONY : clean install
au: au-obj
	$(CC) $(LDFLAGS) obj/helpers.o obj/echo.o -o bin/echo
	$(CC) $(LDFLAGS) obj/true.o -o bin/true
	$(CC) $(LDFLAGS) obj/false.o -o bin/false
au-obj:
	$(CC) $(CFLAGS) -c helpers.c -o obj/helpers.o
	$(CC) $(CFLAGS) -c echo.c -o obj/echo.o
	$(CC) $(CFLAGS) -c true.c -o obj/true.o
	$(CC) $(CFLAGS) -c false.c -o obj/false.o
clean:
	rm -f bin/*
	rm -f obj/*
install:
	cp bin/ "$(PREFIX)"
