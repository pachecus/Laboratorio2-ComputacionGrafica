#include "Camara.h"

Camara::Camara(VEC3D pos, VEC3D lookAt, VEC3D up, double fov, double aspectRatio) {
	this->aspectRatio = aspectRatio;
	this->fov = fov * (M_PI / 180.0);
	this->posicion = pos;
	this->direccion = (lookAt - pos).normalizar();
	this->right = this->direccion.vectorial(up.normalizar()).normalizar();
	this->up = this->right.vectorial(this->direccion).normalizar();
}

Rayo Camara::getRayo(double u, double v) {
	double scale = tan(fov * 0.5);
	VEC3D a = right * (u - 0.5)  * aspectRatio;
	VEC3D dirRayo = (direccion + right * (u - 0.5) * scale * aspectRatio + up * (v - 0.5) * scale).normalizar();
	return Rayo(posicion, dirRayo);
}