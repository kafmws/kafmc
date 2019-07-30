#include<stdio.h>
#include<io.h>

typedef struct{
	int a;
}hh;

int main(){
	//先对转义字符进行处理 
	//'11' →'0011 0001 0011 0001'  当没有转义字符时，每个字符按值作为8bit gcc从左至右高位到低位 MSVC从左至右低位到高位 
	// 存在转义字符时，先将转义字符转义 
	// \xhh 将两位十六进制数转义为8bit，若后面数字及字母超过两位，取最后两位 //通过报错可以看出 \x111 warning: hex escape sequence out of range
	// \ddd 将三位八进制数 转义为8bit 若后面字符超过三位 只转义后面三位 // \1111 warning: multi-character character constant
	// 字符序列按int值进行处理 也就是说超过4位会截断 取后四位  //warning character constant too long for its type 
	int a = '\%';
	char b = '%';
	printf("%d %d",a,b);
	return 0;
}
/*
* NUM,number  ID,identifier
* LBrak, RBrak, LSBrak, RSBrak, LBrace, RBrace, ( ) [ ] { }
* Add, Sub, Mul, Div, Increse, Decline, Mod, + - * / ++ -- %
* AND, OR, NOT, EQ, NOTEQ, LArrow, RArrow, LArrAnd, RArrAnd,  &&  ||  !  ==  !=  <  >  <=  >=
* And, Or, Not, Xor, LShift, RShift,  &  |  ~  ^  <<  >>
* Comma, Assgin, Del, Arrow, Sizeof, Qst, Colon, SemiCol    ,  =  .  ->  sizeof  ?  :  ;
*/
