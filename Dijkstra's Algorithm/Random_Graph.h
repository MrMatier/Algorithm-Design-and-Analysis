#pragma once
#include "Graph.h"
#include <climits>
#include <set>
#include <ctime>

using namespace std;

//losowy graf z zadan� g�sto�ci� i liczno�ci� wierzcho�k�w
void randG(Graph& g, int V, double dens, bool useM) {
    srand(time(0)); //generator liczb losowych
    int maxE = V * (V - 1) / 2;
    int numE = static_cast<int>(maxE * dens);

    set<pair<int, int>> addedE; //zbi�r dodanych kraw�dzi by unikn�� powt�rek

    while (addedE.size() < numE) {
        int u = rand() % V, v = rand() % V;
        if (u != v && addedE.find({ u, v }) == addedE.end()) {
            int w = rand() % 100 + 1;
            if (useM) {
                g.addEdgeM(u, v, w);
                g.addEdgeM(v, u, w);
            }
            else {
                g.addEdgeL(u, v, w);
                g.addEdgeL(v, u, w);
            }
            addedE.insert({ u, v });
            addedE.insert({ v, u });
        }
    }
}
