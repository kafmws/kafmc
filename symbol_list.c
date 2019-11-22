#include"pch.h"

char *ANSI_C_KEYWORDS_LIST[ANSI_C_KEYWORDS_NUM] = {

    "typedef", "extern", "static", "auto", "register", "char", "short", "int", "long", "signed",

    "unsigned", "float", "double", "const", "volatile", "void", "struct", "union", "enum", "case",

    "default", "if", "else", "switch", "while", "do", "for", "goto", "continue", "break", "return",

    "sizeof",
};

int ANSI_C_KEYWORDS_LEN_LIST[ANSI_C_KEYWORDS_NUM] = {
    7, 6, 6, 4, 8, 4, 5, 3, 4, 6,
    8, 5, 6, 5, 8, 4, 6, 5, 4, 4,
    7, 2, 4, 6, 5, 2, 3, 4, 8, 5, 6,
    6,
};

int ANSI_C_KEYWORDS_NUM_LIST[ANSI_C_KEYWORDS_NUM] = {

    TYPEDEF, EXTERN, STATIC, AUTO, REGISTER, CHAR, SHORT, INT, LONG, SIGNED,

    UNSIGNED, FLOAT, DOUBLE, CONST, VOLATILE, VOID, STRUCT, UNION, ENUM, CASE,

    DEFAULT, IF, ELSE, SWITCH, WHILE, DO, FOR, GOTO, CONTINUE, BREAK, RETURN,

    SIZEOF,
};