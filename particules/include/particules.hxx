#include<set>
#include<list>
#include<deque>
#include<vector>
#include<random>
#include<iostream>

class Particule {
    private:
        std::vector<double> position;
        std::vector<double> vitesse;
        double masse; // attribut caché, inaccessible depuis l'extérieur
        int id;
        int categorie;
        std::vector<double> force;

    public:
        Particule(double masse = 0.0,
            std::vector<double> position = {0.0, 0.0},
            std::vector<double> vitesse = {0.0, 0.0},
            int id = 0, 
            int categorie = 0, 
            std::vector<double> force = {0.0, 0.0}); // constructeur

        double getMasse() const; // accesseur (”getter”)
        void setMasse(double m); // mutateur (”setter”)

        std::vector<double> getPosition() const;
        void setPosition(std::vector<double> p);

        std::vector<double> getVitesse() const;
        void setVitesse(std::vector<double> v);

        int getID() const;
        void setID(int i);

        int getCategorie() const;
        void setCategorie(int c);

        std::vector<double> getForce() const;
        void setForce(std::vector<double> f);
};


void stromer_verlet(std::vector<Particule>& ps, double dt, double tend);