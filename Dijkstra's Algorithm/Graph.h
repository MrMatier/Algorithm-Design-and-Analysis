#pragma once
#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include <set>

using namespace std;

class Graph {
    int verts;  // Ilo�� wierzcho�k�w
    vector<list<pair<int, int>>> adjL; // Lista s�siedztwa
    vector<vector<int>> adjM; // Macierz s�siedztwa
    vector<void*> vData; // Dane przechowywane w wierzcho�kach

public:
    Graph(int V) : verts(V), adjL(V), adjM(V, vector<int>(V, INT_MAX)), vData(V, nullptr) {
        for (int i = 0; i < V; ++i) {
            adjM[i][i] = 0; // Waga 0 dla p�tli w�asnej
        }
    }
    friend class Dijkstra; // Dost�p klasy Dijkstra do prywatnych sk�adowych

    // Dodaje kraw�d� do listy s�siedztwa
    void addEdgeL(int src, int dest, int weight) {
        adjL[src].push_back(make_pair(dest, weight));
    }

    // Dodaje kraw�d� do macierzy s�siedztwa
    void addEdgeM(int src, int dest, int weight) {
        adjM[src][dest] = weight;
    }

    // Dodaje wierzcho�ek z danymi
    void addV(void* data) {
        verts++;
        adjL.push_back(list<pair<int, int>>());
        adjM.push_back(vector<int>(verts, INT_MAX));
        for (auto& row : adjM) {
            row.push_back(INT_MAX);
        }
        vData.push_back(data);
    }

    // Usuwa wierzcho�ek
    void rmV(int v) {
        adjL.erase(adjL.begin() + v);
        adjM.erase(adjM.begin() + v);
        for (auto& row : adjM) {
            row.erase(row.begin() + v);
        }
        vData.erase(vData.begin() + v);
        verts--;
    }

    // Dodaje kraw�d� mi�dzy wierzcho�kami
    void addE(int v, int w, int weight) {
        addEdgeL(v, w, weight);
        addEdgeM(v, w, weight);
    }

    // Usuwa kraw�d� mi�dzy wierzcho�kami
    void rmE(int v, int w) {
        adjL[v].remove_if([w](const pair<int, int>& p) { return p.first == w; });
        adjM[v][w] = INT_MAX;
    }

    // Zwraca kraw�dzie przylegaj�ce do wierzcho�ka
    list<pair<int, int>>& incE(int v) {
        return adjL[v];
    }

    // Zwraca wszystkie wierzcho�ki
    vector<void*> vertsList() {
        return vData;
    }

    // Zwraca wszystkie kraw�dzie
    vector<pair<int, pair<int, int>>> edgesList() {
        vector<pair<int, pair<int, int>>> allE;
        for (int i = 0; i < verts; ++i) {
            for (auto& e : adjL[i]) {
                if (e.first > i) {
                    allE.push_back({ e.second, {i, e.first} });
                }
            }
        }
        return allE;
    }
};
