%option noyywrap yylineno case-insensitive

%{
#include <math.h>
#include "src/token.h"

void lex_error(char* msg, int line);
void report(char* msg, char *where, int line);
TokenArray tk_arr;
%}

/*\042 is '"'*/
DIGIT   [0-9]
ID      [a-zA-Z][A-Za-z0-9]*
OPERATOR ([.={;,?!#<>+\-*/()}.])

%%
[ \t\v\n]+  {  }
{OPERATOR}  { return write_operator_token(&tk_arr, yytext[0], yylineno); }
{DIGIT}+    { return write_integer_token(&tk_arr, atoi(yytext), yylineno); }
":="        { return write_operator_token(&tk_arr, T_WALRUS, yylineno); }
"<="        { return write_operator_token(&tk_arr, T_LE, yylineno); }
">="        { return write_operator_token(&tk_arr, T_GE, yylineno); }
"const"     { return write_operator_token(&tk_arr, T_CONST, yylineno); }
"var"       { return write_operator_token(&tk_arr, T_VAR, yylineno); }
"procedure" { return write_operator_token(&tk_arr, T_PROCEDURE, yylineno); }
"begin"     { return write_operator_token(&tk_arr, T_BEGIN, yylineno); }
"end"       { return write_operator_token(&tk_arr, T_END, yylineno); }
"then"      { return write_operator_token(&tk_arr, T_THEN, yylineno); }
"if"        { return write_operator_token(&tk_arr, T_IF, yylineno); }
"call"      { return write_operator_token(&tk_arr, T_CALL, yylineno); }
"while"     { return write_operator_token(&tk_arr, T_WHILE, yylineno); }
"do"        { return write_operator_token(&tk_arr, T_DO, yylineno); }
{ID}        { return write_id_token(&tk_arr, yytext, yylineno); }
<<EOF>>     { return -1; }

%%

static void init(){
        init_token_array(&tk_arr);
}

int main(int argc, char **argv) {
        init();

        if(argc < 2) { /* just read stdin */
                yylex();
                goto end;
        }
        FILE *f = fopen(argv[1], "r");
        if (!f) {
                perror(argv[1]);
                return 1;
        }
        yyin = f;
        yyrestart(f);
        while(yylex() != -1);
        fclose(f);

end:
        print_tokens(&tk_arr);
        yylex_destroy();
        free_token_array(&tk_arr);
        return 0;
}
