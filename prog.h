/*********************************
**********************************
 Zaher Khirullah
*********************************/

#ifndef PROG_H_
#define PROG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jrb.h>
#include <fcntl.h>
#include <fields.h>
#include <unistd.h>
#include <assert.h>

int add_fun(char* inputed[]);
int pro_fun(char* inputed[]);
int search_fun(char* inputed[]);
int print_fun();
int write_fun(char* inputed[]);
int temizleme(char* inputed[]);
char** str_split(char* a_str, const char a_delim);
#endif