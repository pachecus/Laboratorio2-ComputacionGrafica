#include "Plano.h"

Plano::Plano(VEC3D p1, VEC3D p2, VEC3D p3, VEC3D p4, material m,string nombre) {
    this->punto1 = p1; // sup der
    this->punto2 = p2; // sup izq
    this->punto3 = p3; // inf izq
    this->punto4 = p4; // inf der
    this->mat = m;
    this->nombre = nombre;
}

string Plano::getNombre() {
    return this->nombre;
}

bool Plano::interseccion(Rayo rayo, double distanciaMinima, VEC3D& nuevoOrigen, VEC3D& normal) {
    double raiz = 0;
    VEC3D v1 = punto2 - punto1;
    VEC3D v2 = punto3 - punto1;
    normal = v1.vectorial(v2).normalizar();
    if (normal.escalar(rayo.getDireccion()) != 0)
        raiz = normal.escalar(punto1 - rayo.getOrigen()) / normal.escalar(rayo.getDireccion());
    else    
        return false;

    bool ret = false;
    nuevoOrigen = rayo.getOrigen() + (rayo.getDireccion() * raiz);

    if (raiz > distanciaMinima || raiz < 0.001) {
        return false;
    }

    if (punto1.getX() == punto2.getX() && punto1.getX() == punto3.getX() && punto1.getX() == punto4.getX()) { // la coordenada X es la que se comparte
        if (nuevoOrigen.getY() <= punto1.getY() && nuevoOrigen.getY() >= punto3.getY() && nuevoOrigen.getZ() <= punto1.getZ() && nuevoOrigen.getZ() >= punto3.getZ()) // el punto esta en los limites del plano
            ret = true;
    }
    else if (punto1.getY() == punto2.getY() && punto1.getY() == punto3.getY() && punto1.getY() == punto4.getY()) { // la coordenada X es la que se comparte
        if (nuevoOrigen.getX() <= punto1.getX() && nuevoOrigen.getX() >= punto3.getX() && nuevoOrigen.getZ() <= punto1.getZ() && nuevoOrigen.getZ() >= punto3.getZ()) // el punto esta en los limites del plano
            ret = true;
    }
    else if (punto1.getZ() == punto2.getZ() && punto1.getZ() == punto3.getZ() && punto1.getZ() == punto4.getZ()) { // la coordenada X es la que se comparte
        if (nuevoOrigen.getY() <= punto1.getY() && nuevoOrigen.getY() >= punto3.getY() && nuevoOrigen.getX() <= punto1.getX() && nuevoOrigen.getX() >= punto3.getX()) // el punto esta en los limites del plano 
            ret = true;
    }
    if (rayo.getDireccion().escalar(normal) >= 0) {
        normal = normal * (-1);
    }
    return ret;
}

material Plano::getMaterial() {
    return this->mat;
}