#pragma once
#include "Graph.h"
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Dijkstra {
public:
    // Znajduje najkr�tsze �cie�ki od �r�d�a w grafie u�ywaj�c listy lub macierzy s�siedztwa
    vector<int> path(const Graph& g, int src, bool useM) {
        vector<int> dist(g.verts, INT_MAX); // Dystanse do �r�d�a
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Kolejka priorytetowa

        dist[src] = 0;
        pq.push({ 0, src });

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (useM) { // Przetwarzanie z macierzy s�siedztwa
                for (int v = 0; v < g.verts; ++v) {
                    if (g.adjM[u][v] != INT_MAX && dist[v] > dist[u] + g.adjM[u][v]) {
                        dist[v] = dist[u] + g.adjM[u][v];
                        pq.push({ dist[v], v });
                    }
                }
            }
            else { // Przetwarzanie z listy s�siedztwa
                for (auto& p : g.adjL[u]) {
                    int v = p.first, w = p.second;
                    if (dist[v] > dist[u] + w) {
                        dist[v] = dist[u] + w;
                        pq.push({ dist[v], v });
                    }
                }
            }
        }
        return dist;
    }
};
