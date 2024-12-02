#ifndef CONSTANTS_H
#define CONSTANTS_H

extern const int MAX_LINE_LENGTH;

typedef struct {
    char line[128];
} Data;

typedef struct {
    double x;
    double y;
    double z;
} Vector;

#endif
