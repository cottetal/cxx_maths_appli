#include "vecteur.hxx"

#include<cmath>
#include<fstream>
#include<iomanip>

#pragma region CONSTRUCTEUR

Vecteur::Vecteur(double x, double y, double z)
    : x(x),
      y(y),
      z(z)
{
}

#pragma endregion

#pragma region METHODES GET SET

void Vecteur::setPosition(double xs, double ys, double zs) {
    x = xs;
    y = ys;
    z = zs;
}

double Vecteur::getX() const {
    return x;
}

void Vecteur::setX(double xset) {
    x = xset;
}

double Vecteur::getY() const {
    return y;
}

void Vecteur::setY(double yset) {
    y = yset;
}

double Vecteur::getZ() const {
    return z;
}

void Vecteur::setZ(double zset) {
    z = zset;
}

double Vecteur::getNorme() const {
    return std::sqrt(x*x + y*y + z*z);
}

#pragma endregion

#pragma region OPERATORS

double Vecteur::dot(const Vecteur& v) const {
    return x*v.x + y*v.y + z*v.z;
}

Vecteur Vecteur::operator-() const {
    return Vecteur(-x, -y, -z);
}

Vecteur& Vecteur::operator+=(const Vecteur& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vecteur& Vecteur::operator-=(const Vecteur& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vecteur& Vecteur::operator*=(double scalaire) {
    x *= scalaire;
    y *= scalaire;
    z *= scalaire;
    return *this;
}

Vecteur& Vecteur::operator/=(double scalaire) {
    x /= scalaire;
    y /= scalaire;
    z /= scalaire;
    return *this;
}

Vecteur operator+(Vecteur a, const Vecteur& b) {
    a += b;
    return a;
}

Vecteur operator-(Vecteur a, const Vecteur& b) {
    a -= b;
    return a;
}

Vecteur operator*(Vecteur v, double scalaire) {
    v *= scalaire;
    return v;
}

Vecteur operator*(double scalaire, const Vecteur& v) {
    return v * scalaire;
}

Vecteur operator/(Vecteur v, double scalaire) {
    v /= scalaire;
    return v;
}

std::ostream& operator<<(std::ostream& os, const Vecteur& v) {
    os << "(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ")";
    return os;
}

#pragma endregion
