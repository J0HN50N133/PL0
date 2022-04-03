//
// Created by johnsonlee on 4/3/22.
//

#include <stdio.h>
#include "token.h"

void free_token_array(TokenArray * arr) {
    for(int i = 0; i < arr->size; i++) {
        if (arr->tokens[i].type == T_IDENT) {
            free(arr->tokens[i].lexeme);
        }
    }
    reallocarray(arr->tokens, 0, sizeof (Token));
    init_token_array(arr);
}

void write_token_array(TokenArray *arr, Token tk) {
    if (arr->capacity < arr->size + 1) {
        arr->capacity = GROW_CAPACITY(arr->capacity);
        if(!(arr->tokens = reallocarray(arr->tokens, arr->capacity, sizeof(Token)))) exit(1);
    }
    arr->tokens[arr->size++] = tk;
}

void init_token_array(TokenArray *arr) {
    arr->size = 0;
    arr->capacity = 0;
    arr->tokens = NULL;
}

int write_operator_token(TokenArray *arr, enum yytokentype type, int line) {
    Token tk;
    init_token(&tk);
    tk.type = type;
    tk.line = line;
    write_token_array(arr, tk);
    return type;
}

int write_integer_token(TokenArray *arr, int value, int line) {
    Token tk;
    init_token(&tk);
    tk.type = T_NUMBER;
    tk.value.int_val = value;
    tk.line = line;
    write_token_array(arr, tk);
    return T_NUMBER;
}

int write_id_token(TokenArray *arr, char* id, int line) {
    int size = strlen(id);
    char *cpy = (char*)malloc(size+1);
    strcpy(cpy, id);
    Token tk;
    init_token(&tk);
    tk.type = T_IDENT;
    tk.lexeme = cpy;
    tk.line = line;
    write_token_array(arr, tk);
    return T_IDENT;
}

void print_tokens(TokenArray* arr) {
    for(int i = 0; i < arr->size; i++){
        printf("%d: ", i);
        print_token(arr->tokens + i);
    }
}
void init_token(Token *tk) {
    tk->lexeme = NULL;
    tk->line = -1;
    tk->type = -1;
}
static const char* readable[] = {
        "number", "id", "odd", "DO", "while", "if", "then", "begin",
        "end", ":=", "call", "const", "var", "procedure", "<=", ">=",
};
void print_token(Token* tk) {
    if(tk->type < 256) {
        printf("<%c, %d>\n", tk->type, tk->line);
    }
    else if(tk->type == T_NUMBER) {
        printf("<%s %d, %d>\n", "number", tk->value.int_val, tk->line);
    }
    else{
        printf("<%s, %d>\n", tk->type == T_IDENT ? tk->lexeme :readable[tk->type - 256], tk->line);
    }
}
