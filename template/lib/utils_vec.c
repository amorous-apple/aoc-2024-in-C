#include "utils_vec.h"

// Defining a function for 3D vector addition
Vector vec_add(Vector vec1, Vector vec2) {
    Vector sum;
    sum.x = vec1.x + vec2.x;
    sum.y = vec1.y + vec2.y;
    sum.z = vec1.z + vec2.z;
    return sum;
}

// Defining a function for 3D vector subtraction
Vector vec_sub(Vector vec1, Vector vec2) {
    Vector diff;
    diff.x = vec1.x - vec2.x;
    diff.y = vec1.y - vec2.y;
    diff.z = vec1.z - vec2.z;
    return diff;
}
// Defining a function for 3D vector multiplication by a scalar
Vector vec_scalProd(double num, Vector vec) {
    Vector scalProd;
    scalProd.x = num * vec.x;
    scalProd.y = num * vec.y;
    scalProd.z = num * vec.z;
    return scalProd;
}

// Calculating the distance between two vectors
double vec_sepDist(Vector vec1, Vector vec2) {
    Vector temp = vec_sub(vec1, vec2);
    double separation = vec_mag(temp);
    return separation;
}

// Calculating vector magnitude
double vec_mag(Vector vec) {
    double mag = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    return mag;
}

// Calculating the unit vector of a vector
Vector vec_unit(Vector vec) {
    double mag = vec_mag(vec);
    Vector unit = vec_scalProd(1 / mag, vec);
    return unit;
}

// Calculating the cross product of two vectors
Vector vec_cross(Vector vec1, Vector vec2) {
    Vector cross;
    cross.x = vec1.y * vec2.z - vec1.z * vec2.y;
    cross.y = vec1.z * vec2.x - vec1.x * vec2.z;
    cross.z = vec1.x * vec2.y - vec1.y * vec2.x;
    return cross;
}
