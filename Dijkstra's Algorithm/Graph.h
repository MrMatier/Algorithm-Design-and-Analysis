#pragma once
#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include <set>

using namespace std;

class Graph {
    int verts;  //ile wierzcho³ków
    vector<list<pair<int, int>>> adjL; //lista s¹siedztwa
    vector<vector<int>> adjM; //macierz s¹siedztwa
    vector<void*> vData; //dane przechowywane w wierzcho³kach

public:
    Graph(int V) : verts(V), adjL(V), adjM(V, vector<int>(V, INT_MAX)), vData(V, nullptr) {
        for (int i = 0; i < V; ++i) {
            adjM[i][i] = 0; //waga 0 dla pêtli w³asnej
        }
    }
    friend class Dijkstra; //dostêp Dijkstra do prywatnych

    //dodaj krawêdŸ do listy s¹siedztwa
    void addEdgeL(int src, int dest, int weight) {
        adjL[src].push_back(make_pair(dest, weight));
    }
    //dodaj krawêdŸ do macierzy s¹siedztwa
    void addEdgeM(int src, int dest, int weight) {
        adjM[src][dest] = weight;
    }
    //dodaj wierzcho³ek z danymi
    void addV(void* data) {
        verts++;
        adjL.push_back(list<pair<int, int>>());
        adjM.push_back(vector<int>(verts, INT_MAX));
        for (auto& row : adjM) {
            row.push_back(INT_MAX);
        }
        vData.push_back(data);
    }
    //usuñ wierzcho³ek
    void rmV(int v) {
        adjL.erase(adjL.begin() + v);
        adjM.erase(adjM.begin() + v);
        for (auto& row : adjM) {
            row.erase(row.begin() + v);
        }
        vData.erase(vData.begin() + v);
        verts--;
    }
    //dodaj krawêdŸ miêdzy wierzcho³kami
    void addE(int v, int w, int weight) {
        addEdgeL(v, w, weight);
        addEdgeM(v, w, weight);
    }
    //usuñ krawêdŸ miêdzy wierzcho³kami
    void rmE(int v, int w) {
        adjL[v].remove_if([w](const pair<int, int>& p) { return p.first == w; });
        adjM[v][w] = INT_MAX;
    }
    //krawêdzie przylegaj¹ce do wierzcho³ka
    list<pair<int, int>>& incE(int v) {
        return adjL[v];
    }
    //wszystkie wierzcho³ki
    vector<void*> vertsList() {
        return vData;
    }
    // Zwraca wszystkie krawêdzie
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
