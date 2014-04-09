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

/* FIXME: using hash to gain performance */
/* refrence: http://en.wikipedia.org/wiki/Morse_code */
static struct token_element tokens[] = {
{".-",   "A"},
{"-...", "B"},
{"-.-.", "C"},
{"-..",  "D"},
{".",    "E"},
{"..-.", "F"},
{"--.",  "G"},
{"....", "H"},
{"..",   "I"},
{".---", "J"},
{"-.-",  "K"},
{".-..", "L"},
{"--",   "M"},
{"-.",   "N"},
{"---",  "O"},
{".--.", "P"},
{"--.-", "Q"},
{".-.",  "R"},
{"...",  "S"},
{"-",    "T"},
{"..-",  "U"},
{"...-", "V"},
{".--",  "W"},
{"-..-", "X"},
{"-.--", "Y"},
{"--..", "Z"},
{".----", "1"},
{"..---", "2"},
{"...--", "3"},
{"....-", "4"},
{".....", "5"},
{"-....", "6"},
{"--...", "7"},
{"---..", "8"},
{"----.", "9"},
{"-----", "0"},
{NULL,   NULL},
};

void show_morse_code_table(void)
{
    static struct token_element *t = tokens;

    for (;t->token != NULL; ++t) {
        printf("%-5s -> %s\n", t->token, t->display);
    }
}

struct token_element *find_token(const char *input_code)
{
    int i = 0;
    for (i = 0; tokens[i].token != NULL; ++i)
    {
        if (strcmp(input_code, tokens[i].token) == 0) {
            return &tokens[i];
        }
    }
    return NULL;
}

const char *find_code_string(char display_char)
{
    int i = 0;
    for (i = 0; tokens[i].token != NULL; ++i)
    {
        if (tokens[i].display[0] == display_char) {
            return tokens[i].token;
        }
    }
    return NULL;
}

static inline int hexasc_to_digit(int x)
{
    if (x >= '0' && x <= '9')
        return x-'0';

    if (x >= 'A' && x <= 'F')
        return x-'A' + 10; 
    
    if (x >= 'a' && x <= 'f')
        return x-'a' + 10;
    return -1;
}

int hex_to_char(const char *twobyte)
{
    int low, high;

    high = hexasc_to_digit(twobyte[0]);
    if (high < 0) {
        return -1;
    } 

    low = hexasc_to_digit(twobyte[1]);
    if (low < 0) {
        return -1;
    } 

    return (high * 16 + low);
}
