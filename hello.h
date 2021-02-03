#ifndef _HELLO_H_ //如果没有引入头文件file.h
	#define _HELLO_H_ //那就引入头文件file.h
	//结构体和函数声明....
	
	//1 根据跟文件路径和模式获取文件指针
	// FILE* getFILE(char* filePath,char* mode);
	//2 使用临时文件替换原文件
	void printhello();
#endif