#include<stdio.h>
#include<io.h>

typedef struct{
	int a;
}hh;

int main(){
	//�ȶ�ת���ַ����д��� 
	//'11' ��'0011 0001 0011 0001'  ��û��ת���ַ�ʱ��ÿ���ַ���ֵ��Ϊ8bit gcc�������Ҹ�λ����λ MSVC�������ҵ�λ����λ 
	// ����ת���ַ�ʱ���Ƚ�ת���ַ�ת�� 
	// \xhh ����λʮ��������ת��Ϊ8bit�����������ּ���ĸ������λ��ȡ�����λ //ͨ��������Կ��� \x111 warning: hex escape sequence out of range
	// \ddd ����λ�˽����� ת��Ϊ8bit �������ַ�������λ ֻת�������λ // \1111 warning: multi-character character constant
	// �ַ����а�intֵ���д��� Ҳ����˵����4λ��ض� ȡ����λ  //warning character constant too long for its type 
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
