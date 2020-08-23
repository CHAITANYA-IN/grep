#include "getset.h"

void inputFilesetter(int d) {
    input_files = d;
}

void setFor_V() {
    SET_V = 1;
}

void setFor_H() {
    SET_H = 1;
}

void setFor_h() {
    SET_h = 1;
}

void setFor_B() {
    SET_B = 1;
}

void resetFor_B() {
    SET_B = 0;
}

void setFor_M() {
    SET_M = 1;
}

void setFor_CASE() {
    SET_CASE = 1;
}

void resetFor_CASE() {
    SET_CASE = 0;
}

void resetFor_V() {
    SET_V = 0;
}

void resetFor_H() {
    SET_H = 0;
}

void resetFor_h() {
    SET_h = 0;
}

void resetFor_M() {
    SET_M = 0;
}

void setInputNumberForFiles(int argc) {
    input_files = argc;
}

