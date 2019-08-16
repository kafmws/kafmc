#pragma once
#include"pch.h"

void preprocess(char *source_file_name);

void lexer();

/**
* IDENTIFIER, CONSTANT, STRING_LITERAL, SIZEOF,
*
*	PTR_OP, INC_OP, DEC_OP, LEFT_OP, RIGHT_OP, LE_OP, GE_OP, EQ_OP, NE_OP,
*   ->              ++              --             <<                 >>             <=         >=          ==         !=
*
*	AND_OP, OR_OP, MUL_ASSIGN, DIV_ASSIGN, MOD_ASSIGN, ADD_ASSIGN,
*       &&           ||             *=                       \=                      %=                     +=
*
*	SUB_ASSIGN, LEFT_ASSIGN, RIGHT_ASSIGN, AND_ASSIGN,
*           -=                      <<=                        >>=                        &=
*
*	XOR_ASSIGN, OR_ASSIGN, TYPE_NAME,
*          ^=                      |=
*
*	TYPEDEF, EXTERN, STATIC, AUTO, REGISTER,
*
*	CHAR, SHORT, INT, LONG, SIGNED, UNSIGNED, FLOAT, DOUBLE, CONST, VOLATILE, VOID,
*
*	STRUCT, UNION, ENUM, ELLIPSIS,
*                                                  ...
*
*	CASE, DEFAULT, IF, ELSE, SWITCH, WHILE, DO, FOR, GOTO, CONTINUE, BREAK, RETURN,
**/
typedef enum {
	IDENTIFIER = 128, CONSTANT, STRING_LITERAL, SIZEOF,

	PTR_OP, INC_OP, DEC_OP, LEFT_OP, RIGHT_OP, LE_OP, GE_OP, EQ_OP, NE_OP,
	AND_OP, OR_OP, MUL_ASSIGN, DIV_ASSIGN, MOD_ASSIGN, ADD_ASSIGN,
	SUB_ASSIGN, LEFT_ASSIGN, RIGHT_ASSIGN, AND_ASSIGN,
	XOR_ASSIGN, OR_ASSIGN, TYPE_NAME,

	TYPEDEF, EXTERN, STATIC, AUTO, REGISTER,
	CHAR, SHORT, INT, LONG, SIGNED, UNSIGNED, FLOAT, DOUBLE, CONST, VOLATILE, VOID,
	STRUCT, UNION, ENUM, ELLIPSIS,

	CASE, DEFAULT, IF, ELSE, SWITCH, WHILE, DO, FOR, GOTO, CONTINUE, BREAK, RETURN,
}TOKEN;

/*
* NUM,number  ID,identifier
* LBrak, RBrak, LSBrak, RSBrak, LBrace, RBrace, ( ) [ ] { }
* Add, Sub, Mul, Div, Increse, Decline, Mod, + - * / ++ -- %
* AND, OR, NOT, EQ, NOTEQ, LArrow, RArrow, LArrAnd, RArrAnd,  &&  ||  !  ==  !=  <  >  <=  >=
* And, Or, Not, Xor, LShift, RShift,  &  |  ~  ^  <<  >>
* Comma, Assgin, Del, Arrow, Sizeof, Qst, Colon, SemiCol    ,  =  .  ->  sizeof  ?  :  ;
*/