//
//  main.c
//  cipher-shell
//
//  Created by 最上嗣生 on 2013/08/19.
//  Copyright (c) 2013年 最上嗣生. All rights reserved.
//

#include <stdio.h>
#include <setjmp.h>
#include "ciph.h"


//--- taken from app.cp
jmp_buf jmpEnv;

void assert_func(const char* file, int line){
	scroll();
	//extern char*ptr;
    //	print_str(ptr); scroll();
	myPrintf("assertion failure line %d in %s.",line,file);
	longjmp(jmpEnv, 1);
}

void error_func(const char *str, const char* file, int line){
	scroll();
	//extern char*ptr;
    //	print_str(ptr); scroll();
	myPrintf("error: %s occured in line %d of file %s\n",str, line, file);
	longjmp(jmpEnv, 1);
}

void exit2shell(){
	longjmp(jmpEnv, 1);
}

//-----

Interpreter	interpreter;

int main(int argc, const char * argv[]){ 
    char str[256];
    
    interpreter = create_interpreter();
    while(1) {
        if(setjmp(jmpEnv)==0){	//try
            fgets(str, 255, stdin);
            interpret(interpreter, str);
        } else {				//catch
        //    scrollBy(FONTSIZE*2);
        //    newLine();
        }
    }
    dispose_interpreter(interpreter);

    //printf("Hello, World!\n");
    return 0;
}

void scroll(){
    printf("\n");
}


#include <stdarg.h>

void myPrintf(const char *fmt,...){
	va_list	ap;
//	char str[256];
	
    va_start(ap,fmt);
	if (fmt) {
		vprintf(fmt, ap);
	}
	va_end(ap);
}
