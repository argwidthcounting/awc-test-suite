#ifndef TESTS_H
#define TESTS_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

typedef struct p { double x, y, z; } Point;

// Got this from ChatGPT by prompting "C print address without printf"
void printAddress(void* address);

// Got this from ChatGPT by prompting "C print number without printf"
void printNumber(int num);

// Dump the va_list to stderr
// Note that we do NOT use printf, since if something is going wrong, it would likely be effected
void dumpVAList(va_list l);

// Sum n numbers
int sum(int n, ...);

double sumFloats(int n, ...);

// Sum a 3 dimensional Point(x,y,z) struct
Point sumPoints(int n, ...);

// Takes a va_list as an argument and sums all ints inside
int vsum(int n, va_list l);

// Makes a copy of the provided va_list, then sums the numbers
int vsum_copy(int n, va_list l);

// Helper to  call vsum
int call_vsum(int n, ...);

// Helper to  call vsum_copy
int call_vsum_copy(int n, ...);

// Prints provided strings
void printABunch(int n, ...);

// Builds a string using malloc from a bunch of provided chars
char *buildStr(int n, ...);

#endif