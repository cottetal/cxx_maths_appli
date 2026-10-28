#include "vecteur.hxx"

int main() {
    Vecteur a(1, 2, 3);
    Vecteur b(4, 5, 6);

    std::cout << "a + b = " << a + b << "\n";
    std::cout << "a - b = " << a - b << "\n";
    std::cout << "2 * a = " << 2.0 * a << "\n";
    std::cout << "a * 2 = " << a * 2.0 << "\n";
    std::cout << "a . b = " << a.dot(b) << "\n";
    std::cout << "|a|   = " << a.getNorme() << "\n";
    std::cout << "-a    = " << -a << "\n";
    return 0;
}