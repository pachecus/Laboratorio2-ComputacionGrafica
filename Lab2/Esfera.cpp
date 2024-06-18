#include "Esfera.h"

Esfera::Esfera(double r, VEC3D c, material m, string nombre) {
    this->centro = c;
    this->radio = r;
    this->mat = m;
    this->nombre = "esfera";
}

string Esfera::getNombre() {
    return this->nombre;
}

bool Esfera::interseccion(Rayo rayo, double distanciaMinima, VEC3D& nuevoOrigen, VEC3D& normal) {
    
    VEC3D dirOrigenCentro = rayo.getOrigen() - centro;

    double a = rayo.getDireccion().escalar(rayo.getDireccion());
    double b = 2 * rayo.getDireccion().escalar(dirOrigenCentro);
    double c = dirOrigenCentro.escalar(dirOrigenCentro) - pow(radio, 2);

    double disc = pow(b, 2) - (4 * a * c);

    if (disc < 0) {
        return false;
    }

    double sqrtDisc = sqrt(disc);
    double i1 = (-b - sqrtDisc) / (2 * a);
    double i2 = (-b + sqrtDisc) / (2 * a);

    if (i1 < 0.001 || i1 > distanciaMinima) {
        if (i2 < 0.001 || i2 > distanciaMinima) {
            return false; //ninguna sirve.
        }
        i1 = i2;
    }
    if (i2 < i1) {
        i1 = i2;
    }

    nuevoOrigen = rayo.getOrigen() + rayo.getDireccion() * i1;
    normal = ((nuevoOrigen - centro) * (1 / radio)).normalizar();

    if (rayo.getDireccion().escalar(normal) >= 0) {
        normal = normal * (-1);
    }

    return true;
}

material Esfera::getMaterial() {
    return this->mat;
}