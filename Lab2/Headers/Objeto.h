#pragma once

#ifndef OBJETO_H
#define OBJETO_H
#include "Vector.h"
#include "Rayo.h"

using namespace std;
// Clase base para objetos tridimensionales
class Objeto {
public:
    virtual ~Objeto() {} // Destructor virtual para permitir la destrucci�n polim�rfica

    // M�todo virtual puro para obtener el volumen del objeto
    virtual bool interseccion(Rayo rayo, double distanciaMinima, VEC3D& nuevoOrigen, VEC3D& normal) = 0;
    virtual material getMaterial() = 0;
    virtual string getNombre() = 0;
};

#endif // OBJETO3D_H