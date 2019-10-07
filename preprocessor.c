#include"pch.h"
#include"preprocessor.h"
#include"kafmc.h"

/**
* feature :
*               comment     support
*               preprocessor:
*                                       #define         
*                                       #include
*                                       #if etc.
**/

//initialize some global variables
void preprocess(char *source_file_name) {
    int fh = _open(source_file_name, 0);//source file handler
    int len = _filelength(fh);
    source_text = (char *)malloc(sizeof(char)*len + 1);
    memset(source_text, 0, sizeof(char)*len + 1);
    int i = 0;
    char c;//read comment or preprocess sentence
    int in_s_quotation = 0;//in ''
    int in_d_quotation = 0;//in ""
    int in_escape = 0;//may a escape character
    while (_read(fh, source_text + i, 1) > 0) {//read returns -1 when errors occur or 0 as EOF
        switch (source_text[i]) {
        case '#':if (!in_s_quotation && !in_d_quotation) {//preprocessor
            i--;
            while (_read(fh, &c, 1) > 0 && c != '\n');
            source_line_number++; 
        } break;
        case '/':if (!(in_s_quotation || in_d_quotation) && i > 0 && source_text[i - 1] == '/') {//process comment //
            while (_read(fh, &c, 1) > 0 && (c != '\n'));
            source_text[i - 1] = c;//record \n
            i--;
            source_line_number++;
        } break;
        case '"':if (!in_escape) { in_d_quotation = in_d_quotation ? 0 : in_s_quotation ? 0 : 1; } break;
        case '\'':if (!in_escape) { in_s_quotation = in_s_quotation ? 0 : in_d_quotation ? 0 : 1; } break;
        case '\\':in_escape = in_escape ? 0 : 1; break;
        case '*':if (source_text[i - 1] == '/' && !in_s_quotation && !in_d_quotation) {//process comment /**/
            i -= 2;
            int re = 1;
            while (re > 0) {//read success
                while ((re = _read(fh, &c, 1)) > 0 && c != '*');
                if ((re = _read(fh, &c, 1)) > 0 && c == '/') break;
            }
        }break;
        case '\t':source_text[i] = ' '; break;
            //case '\n':i--; break;//not ignore the \n for locate error and report errors or warnings
        default:break;
        }
        if (source_text[i] != '\\' || source_text[i - 1] == '\\') {//out of escape
            in_escape = 0;
        }
        i++;
    }
    source_text[i] = 0;
    puts(source_text);

    //initialize some global variables
    text_p = source_text;
}