
all: loc1.so main
loc1.so: loc1.c
	$(CC) -std=c99 -fPIC -shared $+ -o $@
main: main.c
	$(CC) -std=c99 -fPIC -llua $+ -o $@
clean:
	rm -rf *.o *.so a.txt main
