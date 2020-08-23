#include <stdlib.h>
#include "options.c"
#include <stdio.h>

int main(int argc, char *argv[]) {
    if(argc == 1 || argc == 2) {
        puts("Bad Arguments.");
        exit(1);
    }
    int i = 0, flag = 0, no_options = 0, noOfTimes = 0, j = 1, k = 1, fil = 0;
    char options[20] = "", pattern[20];
    while(j < argc) {
        if(argv[j][0] == '-') {
            k = 1;
            while(k < strlen(argv[j])) {
                options[i] = argv[j][k];
                if(argv[j][k] == 'm') {
                    flag = 1;
                    noOfTimes = atoi(argv[j+1]);
                }
                k++;
                i++;
            }
            no_options++;
        }
        else {
            if(flag == 0)
                strcpy(pattern, argv[j++]);
            else {
                strcpy(pattern, argv[(j++) + 1]);
                j++;
            }
            break;
        }
        j++;
    }
    k = argc - no_options - 2;
    inputFilesetter(k);
    if(argc == 3 && no_options == 0) {
        _grep(argv[2], pattern);
        exit(1);
    }
    while(j < argc && fil != k) {
        fil++;
        if(!strcmp(options, "c")) {
            printf("%d\n", _c(argv[j], pattern, 'c', -1));
        }
        if(!strcmp(options, "b")) {
            _b(argv[j], pattern, &k);
        }
        if(!strcmp(options, "e")) {
            _e(argv[j], pattern);
        }
        if(!strcmp(options, "w")) {
            _w(argv[j], pattern);
        }
        if(!strcmp(options, "q")) {
            _q(argv[j], pattern);
        }
        if(!strcmp(options, "v")) {
            setFor_V();
            _grep(argv[j], pattern);
            resetFor_V();
        }
        if(!strcmp(options, "i")) {
            _i(argv[j], pattern);
        }
        if(!strcmp(options, "m")) {
            _m(argv[j], pattern, noOfTimes);
        }
        if(!strcmp(options, "H")) {
            setFor_H();
            resetFor_h();
            _grep(argv[j], pattern);
            resetFor_H();
        }
        if(!strcmp(options, "h")) {
            setFor_h();
            resetFor_H();
            _grep(argv[j], pattern);
            resetFor_h();
        }
        if(!strcmp(options, "f")) {
            _f(argv[j], pattern);
        }
        if(!strcmp(options, "r")) {
            _r(argv[j], pattern);
        }
        if(!strcmp(options, "cH") || !strcmp(options, "Hc")) {
            setFor_H();
            resetFor_h();
            printf("%d\n", _c(argv[j], pattern, 'c', -1));
            resetFor_H();
        }
        if(!strcmp(options, "ch") || !strcmp(options, "hc")) {
            setFor_h();
            resetFor_H();
            printf("%d\n", _c(argv[j], pattern, 'c', -1));
            resetFor_h();
        }
        if(!strcmp(options, "ci") || !strcmp(options, "ic")) {
            setFor_CASE();
            printf("%d\n", _c(argv[j], pattern, 'i', -1));
            resetFor_CASE();
        }
        if(!strcmp(options, "cm") || !strcmp(options, "mc")) {
            printf("%d\n", _c(argv[j], pattern, 'c', noOfTimes));
        }
        if(!strcmp(options, "cv") || !strcmp(options, "vc")) {
            setFor_V();
            printf("%d\n", _c(argv[j], pattern, 'c', noOfTimes));
            resetFor_V();
        }
        if(!strcmp(options, "iv") || !strcmp(options, "vi")) {
            setFor_V();
            _i(argv[j], pattern);
            resetFor_V();
        }
        if(!strcmp(options, "ih") || !strcmp(options, "hi")) {
            setFor_h();
            resetFor_H();
            _i(argv[j], pattern);
            setFor_h();
        }
        if(!strcmp(options, "iH") || !strcmp(options, "Hi")) {
            resetFor_h();
            setFor_H();
            _i(argv[j], pattern);
            setFor_H();
        }
        j++;
    }
    return 0;
}
