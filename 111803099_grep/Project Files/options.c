#include "options.h"
#include "getset.c"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <regex.h>
#include <dirent.h>

void printColor(char *line, char *pattern) {
    int i = 0;
    while(i < strlen(line)) {
        if((line + i) == strstr((line + i), pattern)) {
            printf("%s%s%s", RED, pattern, RESET);
            i += strlen(pattern) - 1;
        }
        else {
            printf("%c", line[i]);
        }
        i++;
    }
    puts("");
}


void _b(char *filename, char *pattern, int *d) {
    FILE *fp = fopen(filename, "r");
    if(fp == NULL) {
        puts("File not found.");
        exit(1);
    }
    char s[1000] = "", *p = NULL;
    int sum = 0;
    int retval = 0;
    regex_t re;
    if (regcomp(&re, pattern, REG_EXTENDED) == 0) {
        while(fgets(s, 1000, fp) != NULL) {
            s[strlen(s) - 1] = '\0';
            if(!SET_V) {
                if((retval = regexec(&re, s, 0, NULL, 0)) == 0) {
                    printf("%d:", sum);
                    printColor(s, pattern);
                    *d = sum;
                }
            }
            else {
                printf("%d:", sum);
                printColor(s, pattern);
                *d = sum;
            }
            sum += strlen(s)+1;
        }
    }
}

int _c(char *filename, char *pattern, char option_c_i, int m) {
    FILE *fp = fopen(filename, "r");
    if(fp == NULL) {
        puts("File not found.");
        exit(1);
    }
    char s[100] = "";
    int a = 0, b = 0, a_ = 0, b_ = 0;
    if((!SET_h)&&((SET_H)||(input_files != 1))) {
        printf("%s", BLUE);
        printf("%s:", filename);
        printf("%s", RESET);
    }
    if(m != -1) {
        setFor_M();
    }
    while(fgets(s, 100, fp)) {
        s[strlen(s)-1] = '\0';
        if(strstr(s, pattern))
            a++;
        else
            a_++;
        if(strcasestr(s, pattern))
            b++;
        else
            b_++;
        bzero(s, strlen(s));
    }
    if(!SET_V) {
        if(SET_M) {
            if(option_c_i == 'c') {
                if(a > m)
                    return(m);
                else
                    return(a);
            }
            else {
                if(b > m)
                    return(m);
                else
                    return(b);
            }
        }
        else {
            if(option_c_i == 'c')
                return(a);
            else
                return(b);
        }
    }
    else {
        if(SET_M) {
            if(option_c_i == 'c') {
                if(a_ > m)
                    return(m);
                else
                    return(a_);
            }
            else {
                if(b_ > m)
                    return(m);
                else
                    return(b_);
            }
        }
        else {
            if(option_c_i == 'c')
                return(a_);
            else
                return(b_);
        }
    }
    fclose(fp);
}

void _m(char *filename, char *pattern, int noOfTimes) {
    FILE *fp = fopen(filename, "r");
    if(fp == NULL) {
        puts("File not found.");
        exit(1);
    }
    int i = 0;
    int data = 0;
    char s[100] = "", *p = NULL;
    if(fp) {
        while(fgets(s, 100, fp)) {
            s[strlen(s)-1] = '\0';
            if(i < noOfTimes) {
                if(!SET_CASE) {
                    if(!SET_V) {
                        if((p = strstr(s, pattern))) {
                            if(SET_B) {
                                _b(filename, p, &data);
                                exit(1);
                            }
                            if((!SET_h)&&((SET_H)||(input_files != 1))) {
                                printf("%s", BLUE);
                                printf("%s:", filename);
                                printf("%s", RESET);
                            }
                            printColor(s, pattern);
                            i++;
                        }
                    }
                    else {
                        if((p = strstr(s, pattern)) == NULL) {
                            printColor(s, pattern);
                            i++;
                        }
                    }
                }
                else {
                    if(!SET_V) {
                        if((p = strcasestr(s, pattern))) {
                            if(SET_B) {
                                _b(filename, p, &data);
                                exit(1);
                            }
                            printf("%s\n", s);
                            i++;
                        }
                    }
                    else {
                        if((p = strcasestr(s, pattern)) == NULL) {
                            printf("%s", s);
                            i++;
                        }
                    }
                }
            }
            else {
                return;
            }
            bzero(s, strlen(s));
        }
    }
    fclose(fp);
}

void _grep(char *filename, char *tofind) {
    FILE *fp = fopen(filename, "r");
    if(fp == NULL) {
        puts("File not found.");
        exit(1);
    }
    char s[100] = "", *p = NULL;
    regex_t re;
    int retval = 0;
    int data = 0;
    if(fp) {
        if(regcomp(&re, tofind, REG_EXTENDED) == 0) {
               if(fp) {
                   while(fgets(s, 100, fp) != NULL) {
                       s[strlen(s)-1] = '\0';
                       if(!SET_V) {
                           if((retval = regexec(&re, s, 0, NULL, 0)) == 0) {
                               if((!SET_h)&&((SET_H)||(input_files != 1))) {
                                   printf("%s", BLUE);
                                   printf("%s:", filename);
                                   printf("%s", RESET);
                               }
                               if(SET_B) {
                                   _b(filename, p, &data);
                                   exit(1);
                               }
                               printColor(s, tofind);
                           }
                       }
                       else {
                           if (!((retval = regexec(&re, s, 0, NULL, 0)) == 0)) {
                               if((!SET_h)&&((SET_H)||(input_files != 1))) {
                                   printf("%s", BLUE);
                                   printf("%s:", filename);
                                   printf("%s", RESET);
                               }
                               if(SET_B) {
                                   _b(filename, p, &data);
                                   exit(1);
                               }
                               printColor(s, tofind);
                           }
                       }
                       bzero(s, strlen(s));
                   }
               }
        }
    }
    fclose(fp);
}

void _i(char *filename, char *pattern) {
    FILE *fp = fopen(filename, "r");
    if(fp == NULL) {
        puts("File not found.");
        exit(1);
    }
    int data = 0;
    char s[100] = "", *p = NULL;
    if(fp) {
        while(fgets(s, 100, fp) != NULL) {
            s[strlen(s)-1] = '\0';
            if(!SET_V) {
                if((p = strcasestr(s, pattern))) {
                    if((!SET_h)&&((SET_H)||(input_files != 1))) {
                            printf("%s", BLUE);
                            printf("%s:", filename);
                            printf("%s", RESET);
                    }
                    if(SET_B) {
                        _b(filename, p, &data);
                        exit(1);
                    }
                    printColor(s, pattern);
                }
            }
            else {
                if((p = strcasestr(s, pattern)) == NULL) {
                    if((!SET_h)&&((SET_H)||(input_files != 1))) {
                            printf("%s", BLUE);
                            printf("%s:", filename);
                            printf("%s", RESET);
                    }
                    printColor(s, pattern);
                }
            }
            bzero(s, strlen(s));
        }
    }
    fclose(fp);
}

void _f(char *filename, char *inputfile) {
    FILE *ip, *fp = fopen(filename, "r");
    if(fp == NULL) {
        puts("File not found.");
        exit(1);
    }
    char s[100] = "", *p = NULL;
    char tofind[50] = "";
    if(fp) {
        while(fgets(s, 100, fp)) {
            s[strlen(s)-1] = '\0';
            ip = fopen(inputfile, "r");
            if(ip == NULL) {
                puts("File not found.");
                exit(1);
            }
            while(fgets(tofind, 50, ip)) {
                tofind[strlen(tofind)-1] = '\0';
                if((p = strstr(s, tofind))) {
                    if((!SET_h)&&((SET_H) || (input_files != 1))){
                            printf("%s", BLUE);
                            printf("%s:", filename);
                            printf("%s", RESET);
                    }
                    printColor(s, tofind);
                    break;
                }
                else if(SET_V && p == NULL) {
                        if((!SET_h)&&((SET_H)||(input_files != 1))) {
                                printf("%s", BLUE);
                                printf("%s:", filename);
                                printf("%s", RESET);
                        }
                        printColor(s, tofind);
                        break;
                }
                bzero(tofind, strlen(tofind));
            }
            fclose(ip);
            bzero(s, strlen(s));
        }
    }
}

int _w(char *filename, char *pattern) {
    FILE *fp = fopen(filename, "r");
    if(fp == NULL) {
        puts("File not found.");
        exit(1);
    }
    int a = 0, b = 0, a_ = 0, b_ = 0, data = 0;
    char s[100] = "", *p = NULL;
    if(fp) {
        while(fgets(s, 100, fp) != NULL) {
            s[strlen(s)-1] = '\0';
            if(!SET_CASE) {
                if(!SET_V) {
                    if((p = strstr(s, pattern))) {
                        if(!((*(p-1) >= 'A' &&*(p-1) <= 'Z') || (*(p-1) >= 'a' &&*(p-1) <= 'z'))) {
                            if(!((*(p+strlen(pattern)) >= 'A' &&*(p+strlen(pattern)) <= 'Z') || (*(p+strlen(pattern)) >= 'a' &&*(p+strlen(pattern)) <= 'z'))) {
                                if((!SET_h)&&((SET_H)||(input_files != 1))) {
                                    printf("%s", BLUE);
                                    printf("%s:", filename);
                                    printf("%s", RESET);
                                }
                                printColor(s, pattern);
                                a++;
                            }
                        }
                    }
                }
                else {
                    if((p = strstr(s, pattern)) == NULL) {
                        if(!((*(p-1) >= 'A' &&*(p-1) <= 'Z') || (*(p-1) >= 'a' &&*(p-1) <= 'z'))) {
                            if(!((*(p+strlen(pattern)) >= 'A' && *(p+strlen(pattern)) <= 'Z') || (*(p+strlen(pattern)) >= 'a' && *(p+strlen(pattern)) <= 'z'))) {
                                if((!SET_h)&&((SET_H)||(input_files != 1))) {
                                    printf("%s", BLUE);
                                    printf("%s:", filename);
                                    printf("%s", RESET);
                                }
                                printColor(s, pattern);
                                b++;
                            }
                        }
                    }
                }
            }
            else {
                if(!SET_V) {
                    if((p = strcasestr(s, pattern))==0) {
                        if((!SET_h)&&((SET_H)||(input_files != 1))) {
                            printf("%s", BLUE);
                            printf("%s:", filename);
                            printf("%s", RESET);
                        }
                        if(!((*(p-1) >= 'A' &&*(p-1) <= 'Z') || (*(p-1) >= 'a' &&*(p-1) <= 'z'))) {
                            if(!((*(p+strlen(pattern)) >= 'A' &&*(p+strlen(pattern)) <= 'Z') || (*(p+strlen(pattern)) >= 'a' &&*(p+strlen(pattern)) <= 'z'))) {
                                printColor(s, pattern);
                                a_++;
                            }
                        }
                    }
                }
                else {
                    if((p = strcasestr(s, pattern)) == NULL) {
                        if((!SET_h)&&((SET_H)||(input_files != 1))) {
                            printf("%s", BLUE);
                            printf("%s:", filename);
                            printf("%s", RESET);
                        }
                        if(!((*(p-1) >= 'A' &&*(p-1) <= 'Z') || (*(p-1) >= 'a' && *(p-1) <= 'z'))) {
                            if(!((*(p+strlen(pattern)) >= 'A' &&*(p+strlen(pattern)) <= 'Z') || (*(p+strlen(pattern)) >= 'a' &&*(p+strlen(pattern)) <= 'z'))) {
                                printColor(s, pattern);
                                b_++;
                            }
                        }
                    }
                }
            }
            bzero(s, strlen(s));
        }
    }
    fclose(fp);
    if(!SET_CASE) {
        if(!SET_V)
            return(a);
        else
            return(b);
    }
    else {
        if(!SET_V)
            return(a_);
        else
            return(b_);
    }
}

void _e(char *filename, char *pattern) {
    FILE *fp = fopen(filename, "r");
    if(fp == NULL) {
        puts("File not found.");
        exit(1);
    }
    char s[100] = "", *p = NULL;
    int retval = 0, data = 0;
    char *tofind = pattern;
    regex_t re;
    if(!SET_CASE) {
        if(regcomp(&re, tofind, REG_EXTENDED) == 0) {
           if(fp) {
               while(fgets(s, 100, fp) != NULL) {
                   s[strlen(s)-1] = '\0';
                   if(!SET_V) {
                       if((retval = regexec(&re, s, 0, NULL, 0)) == 0) {
                           if((!SET_h)&&((SET_H)||(input_files != 1))) {
                               printf("%s", BLUE);
                               printf("%s:", filename);
                               printf("%s", RESET);
                           }
                           if(SET_B) {
                               _b(filename, p, &data);
                               exit(1);
                           }
                           printColor(s, pattern);
                       }
                   }
                   else {
                       if(!((retval = regexec(&re, s, 0, NULL, 0)) == 0)) {
                           if((!SET_h)&&((SET_H)||(input_files != 1))) {
                               printf("%s", BLUE);
                               printf("%s:", filename);
                               printf("%s", RESET);
                           }
                           if(SET_B) {
                               _b(filename, p, &data);
                               exit(1);
                           }
                           printColor(s, pattern);
                       }
                   }
                   bzero(s, strlen(s));
               }
           }
        }
    }
    else {
        if(regcomp(&re, tofind, REG_ICASE) == 0) {
           if(fp) {
               while(fgets(s, 100, fp) != NULL) {
                   s[strlen(s)-1] = '\0';
                   if(!SET_V) {
                       if((retval = regexec(&re, s, 0, NULL, 0)) == 0) {
                           if((!SET_h)&&((SET_H)||(input_files != 1))) {
                               printf("%s", BLUE);
                               printf("%s:", filename);
                               printf("%s", RESET);
                           }
                           printColor(s, tofind);
                       }
                   }
                   else {
                       if(!((retval = regexec(&re, s, 0, NULL, 0)) == 0)) {
                           if((!SET_h)&&((SET_H)||(input_files != 1))) {
                               printf("%s", BLUE);
                               printf("%s:", filename);
                               printf("%s", RESET);
                           }
                           printColor(s, tofind);
                       }
                   }
                   bzero(s, strlen(s));
               }
           }
        }
    }
    fclose(fp);
}

void _r(char *fold, char *word){
    DIR *dir = opendir(fold);
    char dname[50];
    struct dirent *dent;
    if(dir!=NULL) {
        while((dent = readdir(dir))) {
            if(dent->d_type != 8) {
                if(strcmp(dent->d_name, ".") == 0 || strcmp(dent->d_name, "..") == 0 || strcmp(dent->d_name, ".DS_Store") == 0){
                    continue;
                }
                else {
                    strcpy(dname, fold);
                    strcat(dname, "/");
                    strcat(dname, dent->d_name);
                    _r(dname,word);
                }
            }
            else {
                if(strcmp(dent->d_name, ".DS_Store") == 0) {
                    continue;
                }
                FILE *fp;
                strcpy(dname, fold);
                strcat(dname, "/");
                strcat(dname, dent->d_name);
                fp = fopen(dname, "r");
                if(fp==NULL) {
                    printf("File %s not open",dent->d_name);
                    return;
                }
                setFor_H();
                _e(dname, word);
                fclose(fp);
            }
        }
        closedir(dir);
        return;
    }
    else {
        puts("Directory Not Found.");
        exit(1);
    }
}

void _q(char *filename, char *pattern) {
    FILE *fp = fopen(filename, "r");
    if(fp == NULL) {
        puts("File not found.");
        exit(1);
    }
    char s[100] = "", *p = NULL;
    if(fp) {
        while(fgets(s, 100, fp) != NULL) {
            s[strlen(s)-1] = '\0';
            if((p = strstr(s, pattern))) {
                exit(1);
            }
        }
        exit(1);
    }
}

