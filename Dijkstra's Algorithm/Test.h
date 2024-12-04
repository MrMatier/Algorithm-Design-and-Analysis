#pragma once
#pragma once
#include "Dijkstra.h"
#include <chrono>

using namespace std;

//mierzy wydajnoœæ Dijkstry na danym grafie
double test(Graph& g, int src, bool useM) {
    Dijkstra dijkstra;
    auto start = chrono::high_resolution_clock::now(); //start 
    dijkstra.path(g, src, useM);
    auto end = chrono::high_resolution_clock::now(); //koniec
    chrono::duration<double, milli> elapsed = end - start; 
    return elapsed.count();
}
