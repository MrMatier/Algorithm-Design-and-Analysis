#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Gra
{
public:
    Gra(int rozmiar, int warunekWygranej);
    void dzialaj();

private:
    sf::RenderWindow okno;
    int rozmiar;
    int warunekWygranej;
    int maksGlebokosc;
    std::vector<std::vector<char>> plansza;
    bool graSkonczona;
    std::string wynik;
    sf::Font font;
    sf::Text tekstWyniku;
    void obslugaZdarzen();
    void rysuj();
    bool czyPrawidlowyRuch(int wiersz, int kolumna);
    bool czyWygrana(char znak);
    bool czyRemis();
    void ruchAI(std::vector<std::vector<char>>& plansza, char znak, char znakPrzeciwnika);
    int minimax(std::vector<std::vector<char>>& plansza, int glebokosc, bool maksymalizujacyGracz, char znak, char znakPrzeciwnika, int alfa, int beta);
    int ocen(std::vector<std::vector<char>>& plansza, char znak, char znakPrzeciwnika);
    void resetujGre();
};



