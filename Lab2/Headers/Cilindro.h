#pragma once

#ifndef CILINDRO_H
#define CILINDRO_H

#include "Objeto.h"
#include "Vector.h"

// Clase para representar un cilindro
class Cilindro : public Objeto {
private:
    double radio;
    double altura;
    VEC3D centro;
    material mat;
    string nombre;
public:
    Cilindro(double, double, VEC3D, material, string);
    string getNombre();
    bool interseccion(Rayo rayo, double distancia, VEC3D& nuevoOrigen, VEC3D& normal);
    material getMaterial();
};

#endif // CILINDRO_H