/*********************************
*  __ --Grup Üyeleri--__ 
**********************************
1_ Eyad Almansour (B141210127)
2_ Zaher Khirullah(B151210568)
3_ Mohammad Almahamid (B141210263)
4_ Mumin Othman (G151210563)
5_ Abdulrahamn hamidi (G151210551)
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
int search_fun(char* inputed[]);
int print_fun();
int write_fun(char* inputed[]);
char** str_split(char* a_str, const char a_delim);

#endif