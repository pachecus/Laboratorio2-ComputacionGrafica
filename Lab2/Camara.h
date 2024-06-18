#pragma once

#ifndef CAMARA_H
#define CAMARA_H

#include "Vector.h"
#include "Rayo.h"

#define M_PI       3.14159265358979323846   // pi

using namespace std;

class Camara {
private:
    VEC3D posicion;
    VEC3D direccion;
    VEC3D up;
    double fov;
    VEC3D right;
    double aspectRatio;
public:
    // Constructor
    Camara(VEC3D, VEC3D, VEC3D, double, double);
    Rayo getRayo(double u, double v);
};
#endif // CAMARA_H