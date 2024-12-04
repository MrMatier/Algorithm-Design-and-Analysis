#include "Graph.h"
#include "Dijkstra.h"
#include "Random_Graph.h"
#include "Test.h"
#include <iostream>

using namespace std;

int main() {
    //  Graph g(5);  //graf z 5 wierzcholkami
    //g.addEdgeL(0, 1, 10);
    //g.addEdgeL(0, 2, 3);
    //g.addEdgeL(1, 2, 1);
    //g.addEdgeL(1, 3, 2);
    //g.addEdgeL(2, 3, 8);
    //g.addEdgeL(3, 4, 7);
    //
    //Dijkstra dijkstra;
    //vector<int> dist = dijkstra.path(g, 0, false);  //lista sasiedztaw
    //
    //cout << "Odleglosci od wierzcholka 0:" << endl;
    //for (int i = 0; i < dist.size(); ++i) {
    //    cout << i << ": " << dist[i] << endl;
    //}
    int verts[] = { 10, 50, 100, 500, 1000 };
    double dens[] = { 0.25, 0.5, 0.75, 1.0 };

    for (int V : verts) {
        for (double density : dens) {
            double avglist = 0.0, avgmatrix = 0.0;
            for (int i = 0; i < 100; ++i) {
                Graph g(V);
                randG(g, V, density, false);
                avglist += test(g, 0, false);

                Graph gM(V);
                randG(gM, V, density, true);
                avgmatrix += test(gM, 0, true);
            }

            avglist /= 100;
            avgmatrix /= 100;
            cout << "V=" << V << "|| Density=" << density * 100 << "% || Avg List: " << avglist << " ms || Avg Matrix: " << avgmatrix << " ms" << endl;
            cout << "========================================================================================" << endl;
        }
    }

    return 0;
}
