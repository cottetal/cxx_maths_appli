#pragma once
#include<iostream>

class Vecteur {
    private:
        double x;
        double y;
        double z; 

    public:
        Vecteur(double x = 0.0,
            double y = 0.0,
            double z = 0.0); // constructeur

        void setPosition(double xs, double ys, double zs);

        double getX() const; // accesseur (”getter”)
        void setX(double xset); // mutateur (”setter”)

        double getY() const; // accesseur (”getter”)
        void setY(double yset); // mutateur (”setter”)

        double getZ() const; // accesseur (”getter”)
        void setZ(double zset); // mutateur (”setter”)

        double getNorme() const;

        double dot(const Vecteur& v) const; // produit scalaire

        Vecteur operator-() const; // opposé

        Vecteur& operator+=(const Vecteur& v);
        Vecteur& operator-=(const Vecteur& v);
        Vecteur& operator*=(double scalaire);
        Vecteur& operator/=(double scalaire);
};

Vecteur operator+(Vecteur a, const Vecteur& b);
Vecteur operator-(Vecteur a, const Vecteur& b);
Vecteur operator*(Vecteur v, double scalaire);
Vecteur operator*(double scalaire, const Vecteur& v);
Vecteur operator/(Vecteur v, double scalaire);

std::ostream& operator<<(std::ostream& os, const Vecteur& v);