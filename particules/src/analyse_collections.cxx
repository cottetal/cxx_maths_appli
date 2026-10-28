#include "particules.hxx"
#include<chrono>

int main() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    std::list<Particule> listeParticule;

    auto start = std::chrono::steady_clock::now();
    for (int i=0; i<1048576; ++i)
        std::cout << dist(mt) << "\n";
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

}