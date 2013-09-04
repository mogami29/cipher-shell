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
	extern char*ptr;
	scroll();
    //	print_str(ptr); scroll();
	myPrintf("assertion failure line %d in %s.",line,file);
	longjmp(jmpEnv, 1);
}

void error_func(const char *str, const char* file, int line){
	extern char*ptr;
	scroll();
    //	print_str(ptr); scroll();
	myPrintf("error: %s occured in line %d of file %s\n",str, line, file);
	longjmp(jmpEnv, 1);
}

void exit2shell(){
	longjmp(jmpEnv, 1);
}

//-----
int main(int argc, const char * argv[]){

    // insert code here...
    printf("Hello, World!\n");
    return 0;
/*
	interpreter = create_interpreter();
    
	while(1) {
		if(setjmp(jmpEnv)==0){	//try
			HandleEvent();
		} else {				//catch
			scrollBy(FONTSIZE*2);
			newLine();
		}
	}
	dispose_interpreter(interpreter);
*/
}

