#include "particules_vect.hxx"
#include<fstream>
#include<iomanip>

#pragma region CONSTRUCTEUR

Particule::Particule(double masse, Vecteur position,
                     Vecteur vitesse, int id,
                     int categorie, Vecteur force)
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

Vecteur Particule::getPosition() const {
    return position;
}

void Particule::setPosition(Vecteur p) {
    position = p;
}

Vecteur Particule::getVitesse() const {
    return vitesse;
}
void Particule::setVitesse(Vecteur v) {
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

Vecteur Particule::getForce() const {
    return force;
}
void Particule::setForce(Vecteur f) {
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
            double xi = ps[i].getPosition().getX();
            double xj = ps[j].getPosition().getX();
            double yi = ps[i].getPosition().getY();
            double yj = ps[j].getPosition().getY();
            double zi = ps[i].getPosition().getZ();
            double zj = ps[j].getPosition().getZ();
            double rij = sqrt((xi - xj)*(xi - xj) + (yi - yj)*(yi - yj) + (zi - zj)*(zi - zj));
            Vecteur fi = ps[i].getForce();
            Vecteur fj = ps[j].getForce();


            ps[i].setForce(Vecteur(fi.getX() + mi*mj*(xj-xi) / (rij*rij*rij), fi.getY() + mi*mj*(yj-yi) / (rij*rij*rij), fi.getZ() + mi*mj*(zj-zi) / (rij*rij*rij)));
            ps[j].setForce(Vecteur(fj.getX() + mi*mj*(xi-xj) / (rij*rij*rij), fj.getY() + mi*mj*(yi-yj) / (rij*rij*rij), fj.getZ() + mi*mj*(zi-zj) / (rij*rij*rij)));
        }
    }
}

void stromer_verlet(std::vector<Particule>& ps, double dt, double tend) {
    std::vector<Vecteur> fo;
    fo.resize(ps.size());

    calc_forces(ps);

    std::ofstream fichier("resultats.txt");
    fichier << std::setprecision(10);

    for (double t = dt ; t < tend; t = t + dt) {
        for (std::size_t i=0; i < ps.size(); ++i) { 
            double m = ps[i].getMasse();
            double x = ps[i].getPosition().getX();
            double y = ps[i].getPosition().getY();
            double z = ps[i].getPosition().getZ();
            double vx = ps[i].getVitesse().getX();
            double vy = ps[i].getVitesse().getY();
            double vz = ps[i].getVitesse().getZ();
            double fx = ps[i].getForce().getX();
            double fy = ps[i].getForce().getY();
            double fz = ps[i].getForce().getZ();

            ps[i].setPosition(Vecteur(
                x + dt * (vx + 0.5 * fx * dt / m),
                y + dt * (vy + 0.5 * fy * dt / m),
                z + dt * (vz + 0.5 * fz * dt / m)
            ));

            fo[i] = Vecteur(fx, fy, fz);
        }
    
        calc_forces(ps);

        for (std::size_t i=0; i < ps.size(); ++i) { 
            double m = ps[i].getMasse();
            double vx = ps[i].getVitesse().getX();
            double vy = ps[i].getVitesse().getY();
            double vz = ps[i].getVitesse().getZ();
            double fx = ps[i].getForce().getX();
            double fy = ps[i].getForce().getY();
            double fz = ps[i].getForce().getZ();
            double fox = fo[i].getX();
            double foy = fo[i].getY();
            double foz = fo[i].getZ();

            ps[i].setVitesse(Vecteur(
                vx + dt * 0.5 * (fx + fox) / m , 
                vy + dt * 0.5 * (fy + foy) / m ,
                vz + dt * 0.5 * (fz + foz) / m
            ));
        }
        
        std::cout << "t = " << t << "\n";
        fichier << t << " ";

        double ec = 0.0;
        double ep = 0.0;

        for (std::size_t i=0; i < ps.size(); ++i) {  
            double m = ps[i].getMasse();
            double x = ps[i].getPosition().getX();
            double y = ps[i].getPosition().getY();
            double z = ps[i].getPosition().getZ();
            double vx = ps[i].getVitesse().getX();
            double vy = ps[i].getVitesse().getY();
            double vz = ps[i].getVitesse().getZ();

            ec += 0.5 * m * (vx*vx + vy*vy + vz*vz);
            double ep_i = 0.0;
            for (std::size_t j=i+1; j < ps.size(); ++j) {
                if (i != j) {
                    double xj = ps[j].getPosition().getX();
                    double yj = ps[j].getPosition().getY();
                    double zj = ps[j].getPosition().getZ();
                    double rij = sqrt((x - xj)*(x - xj) + (y - yj)*(y - yj) + (z - zj)*(z - zj));
                    ep_i -= m * ps[j].getMasse() / rij;
                }
            }
            ep += ep_i;

            fichier << x << " " << y << " " << z << " ";
            std::cout << "Particule " << i << ": x = " << x << ", y = " << y << ", z = " << z << "\n";
        }

        double e = ec + ep;
        std::cout << "ENERGIE = " << e << "\n";

        fichier << "\n";
    }
}