#pragma once
#include "Dijkstra.h"
#include <chrono>

using namespace std;

// Mierzy wydajnoœæ algorytmu Dijkstry na danym grafie
double test(Graph& g, int src, bool useM) {
    Dijkstra dijkstra;
    auto start = chrono::high_resolution_clock::now(); // Start pomiaru czasu
    dijkstra.path(g, src, useM);
    auto end = chrono::high_resolution_clock::now(); // Koniec pomiaru czasu
    chrono::duration<double, milli> elapsed = end - start; // Obliczenie czasu wykonania
    return elapsed.count();
}
