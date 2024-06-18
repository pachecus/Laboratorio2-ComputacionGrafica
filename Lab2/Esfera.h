#pragma once

#ifndef ESFERA_H
#define ESFERA_H
#include "Objeto.h"
#include "Vector.h"

// Clase para representar una esfera
class Esfera : public Objeto {
private:
    double radio;
    VEC3D centro;
    material mat;
    string nombre;
public:
    Esfera(double, VEC3D, material, string);
    string getNombre();
    bool interseccion(Rayo rayo, double distanciaMinima, VEC3D& nuevoOrigen, VEC3D& normal);
    material getMaterial();
};

#endif