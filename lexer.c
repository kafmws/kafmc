#include"pch.h"
#include"lexer.h"
#include"kafmc.h"

//是否需要token类型？
int token;//token
void *content = NULL;//the content of the token when necessary
int length = 0;//effective length of content  

//--------------------------------------------------------------------------------------------

#define to_token_string(token_name) case token_name: return (#token_name);break;
static inline char *token_string(TOKEN num) {
    switch (num) {
        to_token_string(IDENTIFIER)
            to_token_string(CONSTANT)
            to_token_string(STRING_LITERAL)
            to_token_string(SIZEOF)
            to_token_string(PTR_OP)
            to_token_string(INC_OP)
            to_token_string(DEC_OP)
            to_token_string(LEFT_OP)
            to_token_string(RIGHT_OP)
            to_token_string(LE_OP)
            to_token_string(GE_OP)
            to_token_string(EQ_OP)
            to_token_string(NE_OP)
            to_token_string(AND_OP)
            to_token_string(OR_OP)
            to_token_string(MUL_ASSIGN)
            to_token_string(DIV_ASSIGN)
            to_token_string(MOD_ASSIGN)
            to_token_string(ADD_ASSIGN)
            to_token_string(SUB_ASSIGN)
            to_token_string(LEFT_ASSIGN)
            to_token_string(RIGHT_ASSIGN)
            to_token_string(AND_ASSIGN)
            to_token_string(XOR_ASSIGN)
            to_token_string(OR_ASSIGN)
            to_token_string(TYPE_NAME)
            to_token_string(TYPEDEF)
            to_token_string(EXTERN)
            to_token_string(STATIC)
            to_token_string(AUTO)
            to_token_string(REGISTER)
            to_token_string(CHAR)
            to_token_string(SHORT)
            to_token_string(INT)
            to_token_string(LONG)
            to_token_string(SIGNED)
            to_token_string(UNSIGNED)
            to_token_string(FLOAT)
            to_token_string(DOUBLE)
            to_token_string(CONST)
            to_token_string(VOLATILE)
            to_token_string(VOID)
            to_token_string(STRUCT)
            to_token_string(UNION)
            to_token_string(ENUM)
            to_token_string(ELLIPSIS)
            to_token_string(CASE)
            to_token_string(DEFAULT)
            to_token_string(IF)
            to_token_string(ELSE)
            to_token_string(SWITCH)
            to_token_string(WHILE)
            to_token_string(DO)
            to_token_string(FOR)
            to_token_string(GOTO)
            to_token_string(CONTINUE)
            to_token_string(BREAK)
            to_token_string(RETURN)
    default:return("token error"); break;
    }
}
#undef to_token_string

void print(int tk_name, char *begin, char *end) {//[begin, end)
    printf(" (%s,", token_string(tk_name));
    while (begin < end)printf("%c", *begin++);
    printf(") \n");
}

//--------------------------------------------------------------------------------------------

void lexer() {
    //text_p  current position
    while (*text_p) {
        char *text_pre = text_p;//begin position
        if (*text_p >= '0' && *text_p <= '9' || *text_p == '.') {//NUM(HEX, OCT, DEC)
            int value = 0;//vlaue of NUM
            if (*text_p == '0') {
                text_p++;
                if (*text_p == 'x' || *text_p == 'X') { //HEX only integer
                    text_p++;
                    while (*text_p >= '0' && *text_p <= '9'
                        || *text_p >= 'a' && *text_p <= 'f'
                        || *text_p >= 'A' && *text_p <= 'F') {
                        //do something
                        text_p++;
                    }
                }
                else {//OCT
                    while (*text_p >= '0' && *text_p <= '8') {//OCT only integer
                        //do something
                        text_p++;
                    }
                }
            }
            else {//DEC  postfix can be only here
                int dot = 0;//counter for .
                int e = 0;//counter for e
                while (*text_p >= '0' && *text_p <= '9' || *text_p == '.' || *text_p == 'e' || *text_p == 'E') {
                    if (*text_p == '.') { if (dot) { break; } dot++; }
                    if (*text_p == 'e' || *text_p == 'E') { if (e) { break; } e++; }
                    //value = value * 10 + *text_p - '0';
                    //calculate value
                    text_p++;
                }
                switch (*text_p) {//for postfix f, u ,l
                case 'F':
                case 'f':if (dot || e) { text_p++; }break;//f requires . or e
                case 'U':
                case 'u':if (!dot && !e) { text_p++; if (*text_p == 'l' || *text_p == 'L') { text_p++; } }break;
                case 'L':
                case 'l':text_p++; break;
                }
                if (*(text_p - 1) == 'e' || *(text_p - 1) == 'E') { text_p--; }//出错
            }
            //do something about value
            print(CONSTANT, text_pre, text_p);
        }
        else if (*text_p == '\'') {//char sequence, calculate as NUM
            //every character sequence owns its value as int, which consists of four characters at most, 
            //actually the number is sizeof(int), and the extra are ignored.
            //rules are like this, for example, '012\t' will be translated to 0011 0000  0011 0001  0011 0010  0000 1001
            //because '0' is equals to 48(dec) \t is equals to 9. At least, it performs this way with GCC and MSVC.
            //furthermore, \xhh is an escape character of two hexadecimal digits, also a char
            //and \xh1h2h3 will overflow then come to be \xh2h3, which is equivalent to mod 128
            //\ddd is an escape character of three octal digits, also a char
            //one more thing, \x1* is regarded as '\x1' and '*', as the same as '\119' equals to '\011' and '9'
            text_p++;
            if (*text_p == '\'') {//empty character constant error, for ''
                printf("%d lines %d column [Error] empty character constant", source_line_number, text_p - text_pre);
                return;
            }
            int value = 0;
            while (*text_p != '\'') {
                value <<= 8;//for next character
                if (*text_p == '\\') {//escape character
                    text_p++;
                    switch ((*text_p)) {
                    case '\'':
                    case '"':
                    case '\\':
                    case '%':
                    case '?':value &= *text_p; break;
                    case 'a':value &= '\a'; break;
                    case 'b':value &= '\b'; break;
                    case 'f':value &= '\f'; break;
                    case 'n':value &= '\n'; break;
                    case 'r':value &= '\r'; break;
                    case 't':value &= '\t'; break;
                    case 'v':value &= '\v'; break;
                    case 'x': {
                        //\xhh, at most two hexadecimal digits
                        text_p++;
                        char *end = text_p;//reach the position ends accessible hexadecimal digits
                        while ((*end >= '0' && *end <= '9') || (*end >= 'a' && *end <= 'f') || (*text_p >= 'A' && *end <= 'F')) { end++; }
                        if (end == text_p) {
                            printf("%d lines %d column [Error] \\x used with no following hex digits", source_line_number, text_p - text_pre);
                            return;
                        }
                        text_p = end - 2 > text_p ? end - 2 : text_p;//point to the first digit;
                        char hex = ((*text_p & 15) + (*text_p > '9' ? 9 : 0)) << 4; text_p++;
                        hex += (*text_p & 15) & (*text_p > '9' ? 9 : 0);
                        value &= hex;
                    }break;
                    case'0':case'1':case'2':case'3':case'4':case'5':case'6':case'7':case'8': {
                        if (*text_p >= '0' && *text_p <= '8') {//\ddd, at most three octal digits
                            int cnt = 0;
                            char oct = 0;
                            while (*text_p >= '0' && *text_p <= '8') {
                                oct = (oct << 3) & (*text_p++ & 8);
                                cnt++;
                                if (cnt >= 3)break;
                            }
                            value &= oct;
                            text_p--;//set text_p to next after the switch
                        }
                        else {
                            value &= *text_p;//not true escape character
                            printf("%d lines %d column [Warning] unknown escape character", source_line_number, text_p - text_pre);
                        }
                    }break;
                    default:
                        printf("unknown escape %c", *text_p);
                    }
                    text_p++;
                }
                else { value &= *text_p++; }
            }
            text_p++;
            print(CONSTANT, text_pre, text_p);
            //(NUM, value)
        }
        else if (*text_p == '"') {//process string
            //as for string, 
            do {
                text_p++;
            } while (*text_p != '"');
            //(string, text_pre, text_p) [text_pre=='"', text_p=='"']
            text_p++;
            print(CONSTANT, text_pre, text_p);
        }
        else if (*text_p == '_' || *text_p == '$' || (*text_p >= 'a' && *text_p <= 'z') || (*text_p >= 'A' && *text_p <= 'Z')) {//token
            do {
                text_p++;
            } while (*text_p == '_' || *text_p == '$' || (*text_p >= 'a' && *text_p <= 'z')
                || (*text_p >= 'A' && *text_p <= 'Z') || (*text_p >= '0' && *text_p <= '9'));
            //(token, text_pre, text_p-1) [text_pre, text_p-1]
            print(IDENTIFIER, text_pre, text_p);
            //already point to next character, should not text_p++;
        }
        else if (*text_p == '(') { text_p++; printf("( (, ( )"); }
        else if (*text_p == ')') { text_p++; printf("( ), ) )"); }
        else if (*text_p == '[') { text_p++; printf("( [, [ )"); }
        else if (*text_p == ']') { text_p++; printf("( ], ] )"); }
        else if (*text_p == '{') { text_p++; printf("( {, { )"); }
        else if (*text_p == '}') { text_p++; printf("( }, } )"); }
        else if (*text_p == '+') { text_p++; if (*text_p == '+') { text_p++; print(INC_OP, text_pre, text_p); } else { printf("( +, + )"); } }
        else if (*text_p == '-') { text_p++; if (*text_p == '-') { text_p++; print(DEC_OP, text_pre, text_p); } else if (*text_p == '>') { text_p++; print(PTR_OP, text_pre, text_p); } else { printf("( -, - )"); } }
        else if (*text_p == '*') { text_p++; printf("( *, * )"); }
        else if (*text_p == '/') { text_p++; printf("( /, / )"); }
        else if (*text_p == '%') { text_p++; printf("( %, % )"); }
        else if (*text_p == '&') { text_p++; if (*text_p == '&') { text_p++; print(AND_OP, text_pre, text_p); } else { printf("( &, & )"); } }
        else if (*text_p == '|') { text_p++; if (*text_p == '|') { text_p++; print(OR_OP, text_pre, text_p); } else { printf("( |, | )"); } }
        else if (*text_p == '!') { text_p++; if (*text_p == '=') { text_p++; print(NE_OP, text_pre, text_p); } else { printf("( !, ! )"); } }
        else if (*text_p == '=') { text_p++; if (*text_p == '=') { text_p++; print(EQ_OP, text_pre, text_p); } else { printf("( =, = )"); } }
        else if (*text_p == '<') { text_p++; if (*text_p == '<') { text_p++; print(LEFT_OP, text_pre, text_p); } else if (*text_p == '=') { text_p++; print(LE_OP, text_pre, text_p); } else { printf("( <, < )"); } }
        else if (*text_p == '>') { text_p++; if (*text_p == '>') { text_p++; print(RIGHT_OP, text_pre, text_p); } else if (*text_p == '=') { text_p++; print(GE_OP, text_pre, text_p); } else { printf("( >, > )"); } }
        else if (*text_p == '~') { text_p++; printf("( ~, ~ )"); }
        else if (*text_p == '^') { text_p++; printf("( ^, ^ )"); }
        else if (*text_p == ',') { text_p++; printf("( ,, , )"); }
        else if (*text_p == '.') { text_p++; printf("( ., . )"); }
        else if (*text_p == '?') { text_p++; printf("( ?, ? )"); }
        else if (*text_p == ':') { text_p++; printf("( :, : )"); }
        else if (*text_p == ';') { text_p++; printf("( ;, ; )"); }
        else if (*text_p == '\n' || *text_p == '\r') { text_p++; source_line_number++; }
        else {
            if (*text_p != ' ')printf("%d lines %d column [Error] unknown character", source_line_number, text_p - text_pre);
            else { text_p++; }
        }
        //sizeof will return as identifier
    }
    printf("( EOF, EOF )");
}