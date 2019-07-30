#include"pch.h"

//暂未考虑预处理的实现，屏蔽#开头的行，以及//种注释开始到该行结束

void preprocess(char *source_file_name) {
	int fh = _open(source_file_name, 0);//source file handler
	int len = _filelength(fh);
	source_text = (char *)malloc(sizeof(char)*len + 1);
	memset(source_text, 0, sizeof(char)*len + 1);
	int i = 0;
	char c;//read comment or preprocess sentence
	int in_s_quotation = 0;//in ''
	int in_d_quotation = 0;//in ""
	while (_read(fh, source_text + i, 1) > 0) {//read returns -1 when errors occur or 0 as EOF
		switch (source_text[i]) {
		case '#':i--; while (_read(fh, &c, 1) > 0 && c != '\n'); source_line_number++; break;//preprocess sentence
		case '/':if (!(in_s_quotation || in_d_quotation) && i > 0 && source_text[i - 1] == '/') {//comment
			while (_read(fh, &c, 1) > 0 && c != '\n');
			i-=2;
			source_line_number++;
		} break;
		case '"':in_d_quotation = in_d_quotation ? 0 : in_s_quotation ? 0 : 1; break;
		case '\'':in_s_quotation = in_s_quotation ? 0 : in_d_quotation ? 0: 1; break;
		case '\t':source_text[i] = ' '; break;
		//case '\n':i--; break;//not ignore the \n for locate error and report errors or warnings
		default:break;
		}
		i++;
	}
	source_text[i] = 0;
	puts(source_text);
}

void lexer() {
	//text_p  current position
	char *text_pre = text_p;//begin position
	while (*text_p) {
		if (*text_p >= '0' && *text_p <= '9'){//NUM(HEX, OCT, DEC)
			int value = 0;//vlaue of NUM
			if (*text_p == '0') {
				text_p++;
				if (*text_p == 'x' || *text_p == 'X') { //HEX only integer
					text_p++;
					while (*text_p >= '0' && *text_p <= '9') {
						//do something
						text_p++;
					}
				}
				else {//OCT
					while (*text_p >= '0' && *text_p <= '9') {//OCT only integer
						//do something
						text_p++;
					}
				}
			}
			else {//DEC
				int del = 0;//counter for .
				while (*text_p >= '0' && *text_p <= '9' || *text_p == '.') {
					if (*text_p == '.') { del++; if (del > 1) { break; } continue; }
					//value = value * 10 + *text_p - '0';
					//calculate value
				}
			}
			//do something about value
			//(NUM, value)
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
					switch (*text_p) {
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
					case 'x':{
						//\xhh, at most two hexadecimal digits
						text_p++;
						char *end = text_p;//reach the position ends accessible hexadecimal digits
						while ((*end >= '0' && *end <= '9') || (*end >= 'a' && *end <= 'f') || (*text_p >= 'A' && *end <= 'F')) { end++; }
						if (end == text_p) {
							printf("%d lines %d column [Error] \\x used with no following hex digits", source_line_number, text_p - text_pre);
							return;
						}
						text_p = end - 2 > text_p ? end - 2 : text_p;//point to the first digit;
						char hex = ((*text_p & 15) + (*text_p > '9' ? 9 : 0)) << 4; *text_p++;
						hex += (*text_p & 15) & (*text_p > '9' ? 9 : 0);
						value &= hex;
					}break;
					default:
						if (*text_p >= '0' && *text_p <= '8') {//\ddd, at most three octal digits
							int cnt = 0; 
							char oct = 0;
							while (*text_p >= '0' && *text_p <= '8') { 
								oct = (oct << 3) & (*text_p++ & 8);
								cnt++;
								if (cnt >= 3)break;
							}
							value &= oct;
							text_p--;
						}
						else {
							value &= *text_p;//not true escape character
							printf("%d lines %d column [Warning] unknown escape character", source_line_number, text_p - text_pre);
						}
						break;
					}
				}
				else { value &= *text_p; }
			}
			text_p++;
			//(NUM, value)
		}
		else if (*text_p == '"') {//process string
			//as for string, 
			do {
				text_p++;
			} while (*text_p!='"');
			//(string, text_pre, text_p) [text_pre=='"', text_p=='"']
			text_p++;
		}
		else if (*text_p == '_' || *text_p == '$'
		|| (*text_p >= 'a' && *text_p <= 'z') || (*text_p >= 'A' && *text_p <= 'Z')) {//token
			do {
				*text_p++;
			} while (*text_p == '_' || *text_p == '$' || (*text_p >= 'a' && *text_p <= 'z') 
				|| (*text_p >= 'A' && *text_p <= 'Z') || (*text_p >= '0' && *text_p <= '9'));
			//(token, text_pre, text_p-1) [text_pre, text_p-1]
			//already point to next character, should not text_p++;
		}
		else if (*text_p == '(') {}
		else if (*text_p == ')') {}
		else if (*text_p == '[') {}
		else if (*text_p == ']') {}
		else if (*text_p == '{') {}
		else if (*text_p == '}') {}
		else if (*text_p == '+') { *text_p++; if (*text_p == '+') {} else {} }
		else if (*text_p == '-') { *text_p++; if (*text_p == '-') {} else if (*text_p == '>') {} else {} }
		else if (*text_p == '*') {}
		else if (*text_p == '/') {}
		else if (*text_p == '%') {}
		else if (*text_p == '&') { *text_p++; if (*text_p == '&') {} else {} }
		else if (*text_p == '|') { *text_p++; if (*text_p == '|') {} else {} }
		else if (*text_p == '!') { *text_p++; if (*text_p == '=') {} else {} }
		else if (*text_p == '=') { *text_p++; if (*text_p == '=') {} else {} }
		else if (*text_p == '<') { *text_p++; if (*text_p == '<') {} else if (*text_p == '=') {} else {} }
		else if (*text_p == '>') { *text_p++; if (*text_p == '>') {} else if (*text_p == '=') {} else {} }
		else if (*text_p == '~') {}
		else if (*text_p == '^') {}
		else if (*text_p == ',') {}
		else if (*text_p == '.') {}
		else if (*text_p == '?') {}
		else if (*text_p == ':') {}
		else if (*text_p == ';') {}
		else if (*text_p == '\n' || *text_p == '\r') { source_line_number++; }
		else {
			if(*text_p !=' ')printf("%d lines %d column [Error] unknown character", source_line_number, text_p - text_pre);
		}
		//sizeof will return as identifier
	}
}