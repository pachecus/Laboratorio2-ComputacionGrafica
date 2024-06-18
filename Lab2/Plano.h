#pragma once

#ifndef PLANO_H
#define PLANO_H

#include "Objeto.h"
#include "Vector.h"

// Clase para representar una esfera
class Plano : public Objeto {
private:
    VEC3D punto1;
    VEC3D punto2;
    VEC3D punto3;
    VEC3D punto4;
    material mat;
    string nombre;


public:
    Plano(VEC3D, VEC3D, VEC3D, VEC3D, material, string);
    string getNombre();

    // Implementaci�n del m�todo virtual para obtener el volumen de la esfera
    bool interseccion(Rayo rayo, double distanciaMinima, VEC3D& nuevoOrigen, VEC3D& normal);

    material getMaterial();
};

#endif // ESFERA_H