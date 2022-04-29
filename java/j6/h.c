#include <jni.h>
#include "h.h"
#include <stdio.h>
#include <stdlib.h>


JNIEXPORT void JNICALL Java_h_test(JNIEnv * env, jobject obj) 
{
	printf("hello, world!\n");

	return;
}

