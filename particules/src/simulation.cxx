#include "particules.hxx"


int main() {
    Particule soleil(1.0, {0.0, 0.0}, {0.0, 0.0}, 0, 0, {0.0, 0.0});
    Particule terre(3.0e-6, {0.0, 1.0}, {-1.0, 0.0}, 1, 0, {0.0, 0.0});
    Particule jupiter(9.55e-4, {0.0, 5.36}, {-0.425, 0.0}, 2, 0, {0.0, 0.0});
    Particule halley(1.0e-14, {34.75, 0}, {0.0, 0.0296}, 3, 0, {0.0, 0.0});

    std::vector<Particule> systeme = {soleil, terre, jupiter, halley};

    stromer_verlet(systeme, 0.015, 468.5);
}