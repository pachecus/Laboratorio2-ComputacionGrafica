#include "../Headers/Cilindro.h"

Cilindro::Cilindro(double h, double r, VEC3D c, material m,string nombre) {
    this->altura = h;
    this->centro = c;
    this->radio = r;
    this->mat = m;
    this->nombre = nombre;
}

string Cilindro::getNombre() {
    return this->nombre;
}

bool Cilindro::interseccion(Rayo rayo, double distanciaMinima, VEC3D& nuevoOrigen, VEC3D& normal) {
    double a = pow(rayo.getDireccion().getX(), 2) + pow(rayo.getDireccion().getY(), 2);
    double b = 2.f * (rayo.getDireccion().getX() * (rayo.getOrigen().getX() - centro.getX()) + rayo.getDireccion().getY() * (rayo.getOrigen().getY() - centro.getY()));
    double c = pow(rayo.getOrigen().getX() - centro.getX(), 2) + pow(rayo.getOrigen().getY() - centro.getY(), 2) - (radio*radio);

    double disc = pow(b, 2) - (4 * a * c);
    if (disc < 0) { // No tiene raices reales
        return false;
    }

    double i1 = (-b + sqrt(disc)) / (2 * a); // Punto de interseccion 1
    double i2 = (-b - sqrt(disc)) / (2 * a); // Punto de interseccion 2

    double raizCercana = i1;
    double raizLejana = i2;
    double raiz = 0;
    if (i1 > i2) {
        raizCercana = i2;
        raizLejana = i1;
    }
    //double h = raizCercana;


    if (raizCercana < 0.001 && raizLejana < 0.001) {
        return false;
    }

    if ((rayo.getOrigen() + rayo.getDireccion() * raizCercana).getZ() > centro.getZ() + altura) { // si la raizCercana esta sobre la tapa superior
        if ((rayo.getOrigen() + rayo.getDireccion() * raizLejana).getZ() <= centro.getZ() + altura) { // si la raizLejana esta debajo de la tapa superior
            raiz = (centro.getZ() + altura - rayo.getOrigen().getZ()) / rayo.getDireccion().getZ();
            nuevoOrigen = rayo.getOrigen() + (rayo.getDireccion() * raiz); // origen del nuevo rayo
            //considerando que el cilindro esta parado la normal de la tapa superior es (0,0,1)
            normal = (nuevoOrigen + VEC3D(0, 0, 1)).normalizar();
        }
        else
            return false;
    }
    else if ((rayo.getOrigen() + rayo.getDireccion() * raizCercana).getZ() <= centro.getZ()) { // si la raizCercana esta debajo de la tapa inferior
        if ((rayo.getOrigen() + rayo.getDireccion() * raizLejana).getZ() >= centro.getZ()) { // si la raizLejana esta sobre la tapa inferior
            raiz = (centro.getZ() - rayo.getOrigen().getZ()) / rayo.getDireccion().getZ();
            nuevoOrigen = rayo.getOrigen() + (rayo.getDireccion() * raiz); // origen del nuevo rayo
            //considerando que el cilindro esta parado la normal de la tapa inferior es (0,0,-1)
            normal = (nuevoOrigen + VEC3D(0, 0, -1)).normalizar();
        }
        else {
            return false;
        }
    }
    else { // No hay interseccion con las tapas, solo con el cilindro
        raiz = raizCercana;
        nuevoOrigen = rayo.getOrigen() + (rayo.getDireccion() * raiz);
        normal = (nuevoOrigen - centro).normalizar();
        if (rayo.getDireccion().escalar(normal) >= 0) {
            normal = normal * (-1);
        }
    }

    if (raiz > distanciaMinima)
        return false;

    return true;
}

material Cilindro::getMaterial() {
    return this->mat;
}
