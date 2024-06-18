#include "Mesa.h"

Mesa::Mesa(material m, set<Triangulo*> t,string nombre) {
    this->mat = m;
    this->triangulos = t;
    this->nombre = nombre;
}

string Mesa::getNombre() {
    return this->nombre;
}

bool Mesa::interseccion(Rayo rayo, double distancia, VEC3D& nuevoOrigen, VEC3D& normal) {
    VEC3D origen, norm;
    bool intersecta = false;
    for (Triangulo* objeto : this->triangulos) {
        if (objeto->interseccion(rayo, distancia, origen, norm)) {
            distancia = (rayo.getOrigen() - origen).norma();
            nuevoOrigen = origen;
            normal = norm;
            intersecta = true;
        }
    }
    return intersecta;
}

material Mesa::getMaterial() {
    return this->mat;
}