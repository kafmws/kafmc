#pragma once
#include"pch.h"

void preprocess(char *source_file_name);

void lexer();

/**
* NUM,number  ID,identifier
* LBrak, RBrak, LSBrak, RSBrak, LBrace, RBrace, ( ) [ ] { }
* Add, Sub, Mul, Div, Increse, Decline, Mod, + - * / ++ -- %
* AND, OR, NOT, EQ, NOTEQ, LArrow, RArrow, LArrAnd, RArrAnd,  &&  ||  !  ==  !=  <  >  <=  >=
* And, Or, Not, Xor, LShift, RShift,  &  |  ~  ^  <<  >>
* Comma, Assgin, Del, Arrow, Sizeof, Qst, Colon, SemiCol    ,  =  .  ->  sizeof  ?  :  ;
*/
enum {
	NUM, ID, LBrak, RBrak, LSBrak, RSBrak, LBrace, RBrace, 
	Add, Sub, Mul, Div, Increse, Decline, Mod, 
	AND, OR, NOT, EQ, NOTEQ, LArrow, RArrow, LArrAnd, RArrAnd, 
	And, Or, Not, Xor, LShift, RShift, 
	Comma, Assgin, Del, Arrow, Sizeof, Qst, Colon, SemiCol,
};