#include "Luz.h"

Luz::Luz(VEC3D p, double i) {
	this->posicion = p;
	this->intensidad = i;
}

VEC3D Luz::getPosicion() {
	return this->posicion;
}

double Luz::getIntensidad() {
	return this->intensidad;
}