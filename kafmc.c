// kafmc.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"

char *source_text = NULL;//all code after preprocess
char *text_p = NULL;//current position
int source_line_number = 0;//source code line number;

int main(int argc, char *argv[]){
	preprocess(argv[2]);
	lexer();
	printf("hello world");
	return 0;
}
