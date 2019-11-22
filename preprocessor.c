#include"pch.h"

/**
* feature :
*               comment     support
*               preprocessor:
*                                       #define         
*                                       #include
*                                       #if etc.
**/

/**
*include files, read
*
*
*
**/

#define PREPROCESSOR_COMMAND_NUM 6

void preprocessor_include(char *command) {
    while (*command == ' ') command++;

}

static char *PREPROCESSOR_COMMAND[PREPROCESSOR_COMMAND_NUM] = {
    "include", "define", "if", "endif", "ifdef", "ifndef",
};

static void (*PREPROCESSOR[])(char *) = { preprocessor_include, };

static inline void preprocessor_dispatcher(char *preprocessor_text) {
    char *p = preprocessor_text;
    int n = 0;
    while (*p != ' ')n++;
    for (int i = 0; i < PREPROCESSOR_COMMAND_NUM; i++) {
        if (strncmp(PREPROCESSOR_COMMAND[i], preprocessor_text, n) == 0) {
            PREPROCESSOR[i](p);
            break;
        }
    }
}

void preprocess(char *source_file_name) {
    int fh = _open(source_file_name, 0);//source file handler
    int len = _filelength(fh);
    char *preprocessor_text = malloc(sizeof(char)*len+1);//for processor text
    memset(preprocessor_text, 0, sizeof(char)*len + 1);
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
            char *p = preprocessor_text;
            continuation:
                while (_read(fh, p, 1) > 0 && (*p) != '\n') { p++; }
                source_text[i] = '\n';
                source_line_number++;
                if (*(p - 1) == '\\') { *(p - 1) = '\n'; goto continuation; }
            //printf("preprocessor :%s\n", preprocessor_text);
                preprocessor_dispatcher(preprocessor_text);
        } break;
        case '/':if (!(in_s_quotation || in_d_quotation) && i > 0 && source_text[i - 1] == '/') {//process comment //
            while (_read(fh, &c, 1) > 0 && (c != '\n'));
            i--;
            source_text[i] = c;//record \n
            source_line_number++;
        } break;
        case '"':if (!in_escape) { in_d_quotation = in_d_quotation ? 0 : in_s_quotation ? 0 : 1; } break;
        case '\'':if (!in_escape) { in_s_quotation = in_s_quotation ? 0 : in_d_quotation ? 0 : 1; } break;
        case '\\':in_escape = in_escape ? 0 : 1; break;
        case '*':if (source_text[i - 1] == '/' && !in_s_quotation && !in_d_quotation) {//process comment /**/
            i-=2;
            int re = 1;
            while (re > 0) {//read success
                int flag = 0;
                while ((re = _read(fh, &c, 1)) > 0 && c != '*') { if (c == '\n') { source_text[i++] = '\n'; source_line_number++; flag = 1; } }
                if ((re = _read(fh, &c, 1)) > 0 && c == '/') { if (flag) { i--; } break; }
                if (c == '\n') { source_text[i] = '\n'; source_line_number++; }
            }
        }break;
        case '\t':source_text[i] = ' '; break;
        case '\n':source_line_number++; break;//do not ignore the \n for locating errors
        default:break;
        }
        if (source_text[i] != '\\' || source_text[i - 1] == '\\') {//out of escape
            in_escape = 0;
        }
        if(isprint(source_text[i]) || source_text[i] == '\n') i++;
        else { printf("\n%d lines [warning] unknown character \\%d ignored\n", source_line_number, (unsigned char)source_text[i]); }
    }
    source_text[i] = 0;
    puts(source_text);

    //initialize some global variables
    text_p = source_text;
    source_line_number = 1;
}
