#pragma once

#ifndef TRIANGULO_H
#define TRIANGULO_H

#include "Objeto.h"
#include "Vector.h"

class Triangulo {
private:
    VEC3D punto1;
    VEC3D punto2;
    VEC3D punto3;
    string nombre;
public:
    Triangulo(VEC3D, VEC3D, VEC3D, string);
    double calcularArea(VEC3D p1, VEC3D p2, VEC3D p3);
    bool interseccion(Rayo rayo, double distancia, VEC3D& nuevoOrigen, VEC3D& normal);
    string getNombre();
};

#endif // TRIANGULO_H