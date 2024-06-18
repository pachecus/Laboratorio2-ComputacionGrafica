#pragma once

#ifndef OPCIONES_H
#define OPCIONES_H
struct Opciones {
    double alto;
    double ancho;
    double profundidad;
    double c1;
    double c2;
    double c3;
    double iA; // intensidad Luz Ambiente
    double cantRayos;
};

//void setRGB(color_RR& color, double r, double g, double b, double alpha) {
//    color.r = r;
//    color.g = g;
//    color.b = b;
//    color.alpha = alpha;
//}

#endif


//struct color_RR {
//    double r;
//    double g;
//    double b;
//    double alpha;
//};