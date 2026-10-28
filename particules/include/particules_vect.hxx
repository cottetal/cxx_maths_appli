#include "vecteur.hxx"
#include<set>
#include<list>
#include<deque>
#include<vector>
#include<random>
#include<iostream>

class Particule {
    private:
        Vecteur position;
        Vecteur vitesse;
        double masse; // attribut caché, inaccessible depuis l'extérieur
        int id;
        int categorie;
        Vecteur force;

    public:
        Particule(double masse = 0.0,
            Vecteur position = Vecteur(0.0, 0.0, 0.0),
            Vecteur vitesse = Vecteur(0.0, 0.0, 0.0),
            int id = 0, 
            int categorie = 0, 
            Vecteur force = Vecteur(0.0, 0.0, 0.0)); // constructeur

        double getMasse() const; // accesseur (”getter”)
        void setMasse(double m); // mutateur (”setter”)

        Vecteur getPosition() const;
        void setPosition(Vecteur p);

        Vecteur getVitesse() const;
        void setVitesse(Vecteur v);

        int getID() const;
        void setID(int i);

        int getCategorie() const;
        void setCategorie(int c);

        Vecteur getForce() const;
        void setForce(Vecteur f);
};


void stromer_verlet(std::vector<Particule>& ps, double dt, double tend);