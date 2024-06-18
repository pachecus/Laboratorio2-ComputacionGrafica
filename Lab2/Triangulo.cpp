#include "Triangulo.h"

Triangulo::Triangulo(VEC3D p1, VEC3D p2, VEC3D p3,string nombre) {
    this->punto1 = p1;
    this->punto2 = p2;
    this->punto3 = p3;
    this->nombre = nombre;
}

string Triangulo::getNombre() {
    return this->nombre;
}

bool Triangulo::interseccion(Rayo rayo, double distancia, VEC3D& nuevoOrigen, VEC3D& normal) {
    VEC3D v1 = punto2 - punto1;
    VEC3D v2 = punto3 - punto1;
    normal = v1.vectorial(v2).normalizar();
      
    VEC3D vdif = punto1 - rayo.getOrigen();
    double vdotn = rayo.getDireccion().escalar(normal); //cos(thetha) angulo entre dir y normal del plano.

    if (fabs(vdotn) < 0.00001) return false; //Rayo paralelo al plano

    double raiz = vdif.escalar(normal) / vdotn;

    if (raiz > distancia || raiz < 0.001) {
        return false;
    }

    bool ret = false;
    nuevoOrigen = rayo.getOrigen() + (rayo.getDireccion() * raiz);
    VEC3D up1 = punto2 - punto1, up2 = punto3 - punto2, up3 = punto1 - punto3;
    VEC3D vp1 = nuevoOrigen - punto1, vp2 = nuevoOrigen - punto2, vp3 = nuevoOrigen - punto3;

    //ACA ES POSIBLE QUE SEA > 0
    if ((up1.vectorial(vp1).escalar(normal) > 0 && (up2.vectorial(vp2).escalar(normal) > 0) && (up3.vectorial(vp3).escalar(normal) > 0))) {
        ret = true;
    }

    if (rayo.getDireccion().escalar(normal) >= 0) {
        normal = normal * (-1);
    }
    return ret;
}

double Triangulo::calcularArea(VEC3D p1, VEC3D p2, VEC3D p3) {
    VEC3D v = p1 - p2;
    VEC3D w = p2 - p3;
    return v.vectorial(w).norma() / 2;
}