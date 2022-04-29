

CC=gcc
AR=ar
INCL=-I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux



.SUFFIXES: .c
.c.o:
	$(CC) $(INCL) -O2 -fPIC -c $< -Wall

all: h


h.h:
	javac -h ./ h.java
libtest.so: h.o
	$(CC) -shared -o $@ $^	-Wall -rdynamic
# libtest.a: h.h h.o
# 	$(AR) rcs $@ $^

h: h.class h.h libtest.so
	java -Djava.library.path=$(PWD) $@ 
 
h.class: h.java
	javac $<
clean:
	rm -rf *.class *.o *.gch *.so *.a h.h

