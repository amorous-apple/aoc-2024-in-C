#ifndef UTILS_VEC_H
#define UTILS_VEC_H

#include <math.h>

#include "constants.h"

Vector vec_add(Vector vec1, Vector vec2);
Vector vec_sub(Vector vec1, Vector vec2);
Vector vec_scalProd(double num, Vector vec);
double vec_sepDist(Vector vec1, Vector vec2);
double vec_mag(Vector vec);
Vector vec_unit(Vector vec);
Vector vec_cross(Vector vec1, Vector vec2);

#endif
