#ifndef LAIKAS_H
#define LAIKAS_H

#include <chrono>

class Laikmatis {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
public:
    Laikmatis() : start{ std::chrono::high_resolution_clock::now() } {}
    void reset() {
        start = std::chrono::high_resolution_clock::now();
    }
    double elapsed() const {
        return std::chrono::duration<double>(
            std::chrono::high_resolution_clock::now() - start
        ).count();
    }
};

#endif
