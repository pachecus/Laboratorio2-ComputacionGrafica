#include "../Headers/Vector.h"

VEC3D::VEC3D() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}
VEC3D::VEC3D(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

VEC3D VEC3D::operator+(const VEC3D& v) const {
    return VEC3D(x + v.x, y + v.y, z + v.z);
}

VEC3D VEC3D::operator-(const VEC3D& v) const {
    return VEC3D(x - v.x, y - v.y, z - v.z);
}

VEC3D VEC3D::operator*(double scalar) const {
    return VEC3D(x * scalar, y * scalar, z * scalar);
}

bool VEC3D::operator==(const VEC3D& other) const {
    int a = x - other.x;
    int b = y - other.y;
    int c = z - other.z;

    return (a == 0 && b == 0 && c == 0);
}

float VEC3D::norma() const {
    return sqrt(x * x + y * y + z * z);
}

VEC3D VEC3D::normalizar() const {
    float len = norma();
    if (len > 0) {
        return VEC3D(x / len, y / len, z / len);
    }
    else {
        return VEC3D(0, 0, 0);
    }
}

float VEC3D::escalar(const VEC3D& v) const {
    return x * v.x + y * v.y + z * v.z;
}

VEC3D VEC3D::vectorial(const VEC3D& v) const {
    return VEC3D(
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    );
}

double VEC3D::getX() {
    return x;
}

double VEC3D::getY() {
    return y;
}

double VEC3D::getZ() {
    return z;
}

void VEC3D::setX(double x) {
    this->x = x;
}
void VEC3D::setY(double y) {
    this->y = y;

}
void VEC3D::setZ(double z) {
    this->z = z;

}