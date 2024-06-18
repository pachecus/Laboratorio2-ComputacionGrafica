#pragma once

#ifndef MESA_H
#define MESA_H

#include "Objeto.h"
#include "Vector.h"
#include "Triangulo.h"
#include <set>

class Mesa : public Objeto {
private:
    set<Triangulo*> triangulos;
    material mat;
    string nombre;
public:
    Mesa(material, set<Triangulo*>, string);
    string getNombre();

    bool interseccion(Rayo rayo, double distancia, VEC3D& nuevoOrigen, VEC3D& normal);
    material getMaterial();
};

#endif // MESA_H