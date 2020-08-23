#include <stdio.h>

#define RED "\033[1;31m"
#define BLUE "\033[1;34m"
#define RESET "\033[0m"

int get_line(FILE *fp, char *s);
int _c(char *filename, char *pattern, char option_c_i, int m) ;
FILE* _fp(char *filename, char *pattern) ;
void _m(char *filename, char *pattern, int noOfTimes) ;
void _grep(char *filename, char *pattern) ;
void _i(char *filename, char *pattern);
void _f(char *filename, char *inputfile);
int _w(char *filename, char *pattern) ;
void _e(char *filename, char *pattern) ;
void _r(char *fold,char *word);
void _q(char *filename, char *pattern);
void printColor(char *, char *);
void _b(char *filename, char *pattern, int *d);
