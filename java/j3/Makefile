

all:j3

h: h.class
	java $@
h.class: h.java
	javac $<
clean:
	rm -rf *.class test.jar deliver/*
j3:
	javac -d deliver com/test/*.java *.java
	#javac -sourcepath . *.java
	java -cp deliver test #com.test.h
test.jar:
	jar cvf $@ -C deliver . 
test: test.jar
	java -classpath $< $@
