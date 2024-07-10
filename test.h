#ifndef TEST_H
#define TEST_H

#include <stdint.h>

#define NAME_LENGTH 15
#define PATH_LENGTH 250
#define ARGS 9
#define DIMMENSIONS 2

typedef struct {
    char name[NAME_LENGTH];
    int32_t r;
    int32_t m;
    int32_t x;
    int32_t y;
    float ax;
    float ay;
    float vx;
    float vy;
} obj2d;

#endif // TEST_H