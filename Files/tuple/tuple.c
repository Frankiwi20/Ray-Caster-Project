#include "tuple.h"
#include <math.h>

unsigned int is_point(Tuple t) {
    return (t.w == 1.0);
}

unsigned int is_vector(Tuple t) {
    return (t.w == 0.0);
}

Tuple tuple(double x, double y, double z, double w) {
    Tuple t;
    t.x = x;
    t.y = y;
    t.z = z;
    t.w = w;
    return t;
}

Tuple point(double x, double y, double z) {
    return tuple(x, y, z, 1.0);
}

Tuple vector(double x, double y, double z) {
    return tuple(x, y, z, 0.0);
}

Tuple addTuples(Tuple a, Tuple b) {
    return tuple(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

Tuple subTuples(Tuple a, Tuple b) {
    return tuple(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

Tuple negateTuple(Tuple t) {
    return tuple(-t.x, -t.y, -t.z, -t.w);
}

Tuple scalarMultTuple(double scalar, Tuple t) {
    return tuple(scalar * t.x, scalar * t.y, scalar * t.z, scalar * t.w);
}

Tuple scalarDivideTuple(Tuple t, double divisor) {
    return tuple(t.x / divisor, t.y / divisor, t.z / divisor, t.w / divisor);
}

double magnitudeOfVector(Tuple v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Tuple normalizeVector(Tuple v) {
    double mag = magnitudeOfVector(v);
    if (mag == 0.0) {
        return vector(0.0, 0.0, 0.0); // Handle zero vector case
    }
    return scalarDivideTuple(v, mag);
}

double dotProduct(Tuple a, Tuple b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Color color(double r, double g, double b) {
    Color c;
    c.red = r;
    c.green = g;
    c.blue = b;
    return c;
}

Color addColors(Color a, Color b) {
    Color result;
    result.red = a.red + b.red;
    result.green = a.green + b.green;
    result.blue = a.blue + b.blue;
    return result;
}

Color subColors(Color a, Color b) {
    Color result;
    result.red = a.red - b.red;
    result.green = a.green - b.green;
    result.blue = a.blue - b.blue;
    return result;
}

Color scalarMultColor(double scalar, Color c) {
    Color result;
    result.red = scalar * c.red;
    result.green = scalar * c.green;
    result.blue = scalar * c.blue;
    return result;
}

Color multColors(Color a, Color b) {
    Color result;
    result.red = a.red * b.red;
    result.green = a.green * b.green;
    result.blue = a.blue * b.blue;
    return result;
}
