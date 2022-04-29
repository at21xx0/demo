

CC ?= gcc

h: program h.class
	java $@
h.class: h.java
	javac $<

module-test:
	javac -d mods/com.test src/com.test/module-info.java src/com.test/com/test/h.java
	java --module-path mods -m com.test/com.test.h
program: program.c
	$(CC) $< -o $@
clean:
	rm -rf *.class program
