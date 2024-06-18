#pragma once

#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <iostream>
#include <string>

using namespace std;

struct color_RR {
    double r;
    double g;
    double b;
    double alpha;
};

struct material {
    double kA; // coefRefleccionAmbiente
    double kD; // coefRefleccionDifusa
    double kS; // coefRefleccionEspecular
    double eN; // exponenteEspecular
    double kT; // coefTransmision
    double iR; // indiceRefraccion
    color_RR color; // colorMaterial
    color_RR colorD; // colorDisfuso Material
    color_RR colorE; // colorEspecular Material
};

class VEC3D {
private:
    double x;
    double y;
    double z;
public:

    VEC3D();
    VEC3D(double x, double y, double z);

    // Sobrecarga del operador suma para vectores
    VEC3D operator+(const VEC3D& v) const;

    // Sobrecarga del operador resta para vectores
    VEC3D operator-(const VEC3D& v) const;

    // Multiplicar vector por escalar
    VEC3D operator*(double scalar) const;

    // Sobrecarga del operador igual para vectores
    bool operator==(const VEC3D& other) const;

    // Norma de Vector
    float norma() const;

    // Normalizar vector
    VEC3D normalizar() const;

    // Producto Escalar
    float escalar(const VEC3D& v) const;

    // Producto Vectorial
    VEC3D vectorial(const VEC3D& v) const;

    //Setters
    void setX(double x);
    void setY(double y);
    void setZ(double z);

    // Getters
    double getX();
    double getY();
    double getZ();
};

#endif