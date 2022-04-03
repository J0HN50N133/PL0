#ifndef _PL0_TOKEN_H
#define _PL0_TOKEN_H
#include <string.h>
#include <stdlib.h>
#include "array.h"

enum yytokentype {
        T_NUMBER = 256,
        T_IDENT, T_ODD, T_DO, T_WHILE, T_IF, T_THEN, T_BEGIN, T_END,
        T_WALRUS, T_CALL, T_CONST, T_VAR, T_PROCEDURE, T_LE, T_GE,
};

typedef struct{
        enum yytokentype type;
        int line;
        char* lexeme;
        // 目前PL0只有数字这一种值
        union{ int int_val; } value;
} Token;
void init_token(Token*);
void print_token(Token*);
typedef struct{
        int capacity;
        int size;
        Token* tokens;
}TokenArray;

void init_token_array(TokenArray*);
// 插入Token并返回Token类型
int write_operator_token(TokenArray*, enum yytokentype, int);
int write_id_token(TokenArray*, char*, int);
int write_integer_token(TokenArray*, int, int);
void write_token_array(TokenArray*, Token);
void free_token_array(TokenArray*);
void print_tokens(TokenArray*);

#endif // _PL0_TOKEN_H
