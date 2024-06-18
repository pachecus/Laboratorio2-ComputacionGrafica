#pragma once

#ifndef LUZ_H
#define LUZ_H


#include "Vector.h"


class Luz {
private:
    // Datos de la c?mara
    VEC3D posicion;
    double intensidad;

public:
    // Constructor
    Luz(VEC3D, double);
    VEC3D getPosicion();
    double getIntensidad();


};
#endif // LUZ_H