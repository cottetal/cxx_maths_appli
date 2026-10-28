#include "particules.hxx"
#include<fstream>
#include<iomanip>

#pragma region CONSTRUCTEUR

Particule::Particule(double masse, std::vector<double> position,
                     std::vector<double> vitesse, int id,
                     int categorie, std::vector<double> force)
    : position(position),
      vitesse(vitesse),
      masse(masse),
      id(id),
      categorie(categorie),
      force(force)
{
}

#pragma endregion

#pragma region METHODES GET SET

double Particule::getMasse() const {
    return masse;
}

void Particule::setMasse(double m) {
    masse = m;
}

std::vector<double> Particule::getPosition() const {
    return position;
}

void Particule::setPosition(std::vector<double> p) {
    position = p;
}

std::vector<double> Particule::getVitesse() const {
    return vitesse;
}
void Particule::setVitesse(std::vector<double> v) {
    vitesse = v;
}

int Particule::getID() const {
    return id;
}
void Particule::setID(int i) {
    id = i;
}

int Particule::getCategorie() const {
    return categorie;
}
void Particule::setCategorie(int c) {
    categorie = c;
}

std::vector<double> Particule::getForce() const {
    return force;
}
void Particule::setForce(std::vector<double> f) {
    force = f;
}

#pragma endregion

void calc_forces(std::vector<Particule>& ps) {
    for (std::size_t i=0; i < ps.size(); ++i) {
        ps[i].setForce({0.0, 0.0});
    }
    for (std::size_t i=0; i < ps.size(); ++i) {
        for (std::size_t j=i+1; j < ps.size(); ++j) {
            double mi = ps[i].getMasse();
            double mj = ps[j].getMasse();
            double xi = ps[i].getPosition()[0];
            double xj = ps[j].getPosition()[0];
            double yi = ps[i].getPosition()[1];
            double yj = ps[j].getPosition()[1];
            double rij = sqrt((xi - xj)*(xi - xj) + (yi - yj)*(yi - yj));
            std::vector<double> fi = ps[i].getForce();
            std::vector<double> fj = ps[j].getForce();


            ps[i].setForce({fi[0] + mi*mj*(xj-xi) / (rij*rij*rij), fi[1] + mi*mj*(yj-yi) / (rij*rij*rij)});
            ps[j].setForce({fj[0] + mi*mj*(xi-xj) / (rij*rij*rij), fj[1] + mi*mj*(yi-yj) / (rij*rij*rij)});
        }
    }
}

void stromer_verlet(std::vector<Particule>& ps, double dt, double tend) {
    std::vector<std::vector<double>> fo;
    fo.resize(ps.size());

    calc_forces(ps);

    std::ofstream fichier("resultats.txt");
    fichier << std::setprecision(10);

    for (double t = dt ; t < tend; t = t + dt) {
        for (std::size_t i=0; i < ps.size(); ++i) { 
            double m = ps[i].getMasse();
            double x = ps[i].getPosition()[0];
            double y = ps[i].getPosition()[1];
            double vx = ps[i].getVitesse()[0];
            double vy = ps[i].getVitesse()[1];
            double fx = ps[i].getForce()[0];
            double fy = ps[i].getForce()[1];

            ps[i].setPosition({
                x + dt * (vx + 0.5 * fx * dt / m),
                y + dt * (vy + 0.5 * fy * dt / m)
            });

            fo[i] = {fx, fy};
        }
    
        calc_forces(ps);

        for (std::size_t i=0; i < ps.size(); ++i) { 
            double m = ps[i].getMasse();
            double vx = ps[i].getVitesse()[0];
            double vy = ps[i].getVitesse()[1];
            double fx = ps[i].getForce()[0];
            double fy = ps[i].getForce()[1];
            double fox = fo[i][0];
            double foy = fo[i][1];

            ps[i].setVitesse({
                vx + dt * 0.5 * (fx + fox) / m , 
                vy + dt * 0.5 * (fy + foy) / m 
            });
        }
        
        std::cout << "t = " << t << "\n";
        fichier << t << " ";

        double ec = 0.0;
        double ep = 0.0;

        for (std::size_t i=0; i < ps.size(); ++i) {  
            double m = ps[i].getMasse();
            double x = ps[i].getPosition()[0];
            double y = ps[i].getPosition()[1];
            double vx = ps[i].getVitesse()[0];
            double vy = ps[i].getVitesse()[1];

            ec += 0.5 * m * (vx*vx + vy*vy);
            double ep_i = 0.0;
            for (std::size_t j=i+1; j < ps.size(); ++j) {
                if (i != j) {
                    double xj = ps[j].getPosition()[0];
                    double yj = ps[j].getPosition()[1];
                    double rij = sqrt((x - xj)*(x - xj) + (y - yj)*(y - yj));
                    ep_i -= m * ps[j].getMasse() / rij;
                }
            }
            ep += ep_i;

            fichier << x << " " << y << " ";
            std::cout << "Particule " << i << ": x = " << x << ", y = " << y << "\n";
        }

        double e = ec + ep;
        std::cout << "ENERGIE = " << e << "\n";

        fichier << "\n";
    }
}