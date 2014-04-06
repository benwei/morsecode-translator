/*
 * Copyright (c) 2014, Ben Wei (ben@staros.mobi)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <string.h>
#include "morse.h"
static int verbose = 0;

#define MORSE_E_UNKNOWN_ESCAPE 2

static int show_morse_code(const char *code, unsigned int len)
{
    struct token_element *t = find_token(code);
    if (!t) {
        if (*code == '\\') {
            code++; 
            if (*code == 'x') {
                int c = hex_to_char(&code[1]);
                if (c < 0) {
                    printf("\\%s", code);
                    return MORSE_E_UNKNOWN_ESCAPE;
                } 

                printf("%c", (char)c);
                return 0;
            }
            printf("%s", code);
            return 0;
        } /* escape leading '\' */
        printf("%s", code);
        return 0;
    } 
    printf("%s", t->display);
    return 0;
}

void syntax()
{
    printf("sytax: [-v <morse code>] | -l\n");
}

int show_morse_code_with_check(const char *morse_buf, int morse_len, unsigned int current)
{
    int r = show_morse_code(morse_buf, morse_len);
    if (verbose && r != 0) {
        fprintf(stderr, "warning: unknown esacpe hex code '\\'x at %u\n", current - morse_len);
    }
    return r;
}
#define MAX_MORSE_CODE_LEN 5
int main(int argc, char **argv)
{
    int rc = 0;
    const char *input_code = NULL;
    char morse_buf[MAX_MORSE_CODE_LEN + 1] = {0};
    unsigned int morse_len = 0;
    const char *p;
    if (argc < 2) {
        syntax();
        return 1;
    }

    input_code=argv[1];
    if (*input_code == '-') {
        switch(input_code[1]) {
            case  'l':
                show_morse_code_table();
                return 0;
            case 'v':
                verbose++;
                if (argc < 3) {
                    syntax();
                    return 1;
                }
                input_code = argv[2];
                break;
        };
    }

    for (p=input_code; *p != '\0';++p)
    {
        if (morse_len < MAX_MORSE_CODE_LEN) {
            if (*p != ' ' && *p != '\n') {
                morse_buf[morse_len++] = *p;
            }
        }

        if (*p == ' ' || *p == '\n') {
            morse_buf[morse_len] = '\0';
            rc |= show_morse_code_with_check(morse_buf, morse_len, p - input_code);
            morse_len = 0;
        }
    }

    if (morse_len != 0) {
        morse_buf[morse_len] = '\0';
        rc |= show_morse_code_with_check(morse_buf, morse_len, p - input_code);
    }
    printf("\n");

    return rc;
}
