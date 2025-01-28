#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int line_number = 1;

bool next_token(FILE *j_file, token *output) {
    char token_str[MAX_TOKEN_LENGTH];
    if (fscanf(j_file, "%s", token_str) == EOF) {
        return false;
    }

    if (token_str[0] == ';') {
        while (fgetc(j_file) != '\n' && !feof(j_file));
        line_number++;
        return next_token(j_file, output);
    }

    memset(output, 0, sizeof(token));

    // Recognize reserved tokens
    if (strcmp(token_str, "defun") == 0) {
        output->type = DEFUN;
    } else if (strcmp(token_str, "return") == 0) {
        output->type = RETURN;
    } else if (strcmp(token_str, "+") == 0) {
        output->type = PLUS;
    } else if (strcmp(token_str, "-") == 0) {
        output->type = MINUS;
    } else if (strcmp(token_str, "*") == 0) {
        output->type = MUL;
    } else if (strcmp(token_str, "/") == 0) {
        output->type = DIV;
    } else if (strcmp(token_str, "%") == 0) {
        output->type = MOD;
    } else if (strcmp(token_str, "dup") == 0) {
        output->type = DUP;
    } else if (strcmp(token_str, "swap") == 0) {
        output->type = SWAP;
    } else if (strcmp(token_str, "rot") == 0) {
        output->type = ROT;
    } else if (strcmp(token_str, "and") == 0) {
        output->type = AND;
    } else if (strcmp(token_str, "or") == 0) {
        output->type = OR;
    } else if (strcmp(token_str, "not") == 0) {
        output->type = NOT;
    } else if (strcmp(token_str, "lt") == 0) {
        output->type = LT;
    } else if (strcmp(token_str, "le") == 0) {
        output->type = LE;
    } else if (strcmp(token_str, "eq") == 0) {
        output->type = EQ;
    } else if (strcmp(token_str, "ge") == 0) {
        output->type = GE;
    } else if (strcmp(token_str, "gt") == 0) {
        output->type = GT;
    } else if (strcmp(token_str, "set_arg1") == 0) {
        output->type = SET_ARG;
        output->arg_no = 1;
    } else if (strcmp(token_str, "get_arg1") == 0) {
        output->type = GET_ARG;
        output->arg_no = 1;
    } else if (strncmp(token_str, "set_arg", 7) == 0 && isdigit(token_str[7])) {
        output->type = SET_ARG;
        output->arg_no = atoi(&token_str[7]);
    } else if (strncmp(token_str, "get_arg", 7) == 0 && isdigit(token_str[7])) {
        output->type = GET_ARG;
        output->arg_no = atoi(&token_str[7]);
    } else if (strcmp(token_str, "if") == 0) {
        output->type = IF;
    } else if (strcmp(token_str, "else") == 0) {
        output->type = ELSE;
    } else if (strcmp(token_str, "endif") == 0) {
        output->type = ENDIF;
    } else if (strcmp(token_str, "while") == 0) {
        output->type = WHILE;
    } else if (strcmp(token_str, "endwhile") == 0) {
        output->type = ENDWHILE;
    } else if (strcmp(token_str, "drop") == 0) {
        output->type = DROP;
    } else if (isdigit(token_str[0]) || (token_str[0] == '-' && isdigit(token_str[1]))) {
        output->type = LITERAL;
        if (strncmp(token_str, "0x", 2) == 0 || strncmp(token_str, "0X", 2) == 0) {
            output->literal_value = (int32_t)strtol(token_str, NULL, 16);
        } else {
            output->literal_value = atoi(token_str);
        }
    } else if (isalpha(token_str[0]) || token_str[0] == '_') {
        output->type = IDENT;
        strncpy(output->str, token_str, MAX_TOKEN_LENGTH);
    } else {
        output->type = BAD_TOKEN;
    }

    return true;
}


void print_token(FILE *f, token to_print) {
    fprintf(f, "Token type: %d, Value: %d, Arg no: %d, Str: %s\n",
            to_print.type, to_print.literal_value, to_print.arg_no, to_print.str);
}
