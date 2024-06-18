#pragma once

#ifndef RAYO_H
#define RAYO_H

#include "Vector.h"
class Rayo {
private:
    VEC3D origen;
    VEC3D direccion;
public:


    // Constructor
    Rayo() {
        this->origen = VEC3D(0, 0, 0);
        this->direccion = VEC3D(0, 0, 0);
    }
    Rayo(VEC3D origen, VEC3D direccion) {
        this->origen = origen;
        this->direccion = direccion;
    }

    VEC3D getOrigen() {
        return origen;
    }
    VEC3D getDireccion() {
        return direccion;
    }
    void setOrigen(VEC3D o) {
        origen = o;
    }
    void setDireccion(VEC3D d) {
        direccion = d;
    }
};

#endif