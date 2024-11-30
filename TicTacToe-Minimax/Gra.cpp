﻿#include "Gra.h"
#include <climits>

Gra::Gra(int rozmiar, int warunekWygranej) : okno(sf::VideoMode(800, 600), "Kolko i Krzyyk"), plansza(rozmiar, std::vector<char>(rozmiar, ' '))
{
    this->rozmiar = rozmiar;
    this->warunekWygranej = warunekWygranej;
    this->maksGlebokosc = (100 / (rozmiar * rozmiar)) + 1;
}

void Gra::dzialaj()
{
    while (okno.isOpen()) {
        obslugaZdarzen();
        rysuj();
    }
}

void Gra::obslugaZdarzen()
{
    sf::Event zdarzenie;
    while (okno.pollEvent(zdarzenie)) {
        if (zdarzenie.type == sf::Event::Closed)
            okno.close();
        else if (zdarzenie.type == sf::Event::MouseButtonPressed) {
            if (zdarzenie.mouseButton.button == sf::Mouse::Left) {
                int x = zdarzenie.mouseButton.x;
                int y = zdarzenie.mouseButton.y;
                int wiersz = y / (okno.getSize().y / rozmiar);
                int kolumna = x / (okno.getSize().x / rozmiar);

                if (czyPrawidlowyRuch(wiersz, kolumna)) {
                    plansza[wiersz][kolumna] = 'X';

                    if (czyWygrana('X')) {
                        std::cout << "Gracz wygrywa!" << std::endl;
                    }
                    else if (czyRemis()) {
                        std::cout << "Remis!" << std::endl;
                    }
                    else {
                        ruchAI(plansza, 'O', 'X');
                        if (czyWygrana('O'))
                            std::cout << "AI wygrywa!" << std::endl;
                        if (czyRemis())
                            std::cout << "Remis!" << std::endl;
                    }
                }
            }
        }
    }
}

void Gra::rysuj()
{
    okno.clear(sf::Color::White);

    float szerKomorki = okno.getSize().x / static_cast<float>(rozmiar);
    float wysKomorki = okno.getSize().y / static_cast<float>(rozmiar);
    for (size_t i = 0; i < rozmiar; i++)
    {
        for (size_t j = 0; j < rozmiar; j++) {
            sf::RectangleShape komorka(sf::Vector2f(szerKomorki, wysKomorki));
            komorka.setPosition(j * szerKomorki, i * wysKomorki);
            komorka.setOutlineThickness(2.f);
            komorka.setOutlineColor(sf::Color::Black);
            komorka.setFillColor(sf::Color::Transparent);
            okno.draw(komorka);

            if (plansza[i][j] == 'X') {
                sf::RectangleShape krzyzyk1(sf::Vector2f(szerKomorki / 2, 4.f));
                krzyzyk1.setPosition(j * szerKomorki + szerKomorki / 4, i * wysKomorki + wysKomorki / 4);
                krzyzyk1.setFillColor(sf::Color::Red);
                krzyzyk1.rotate(45.f);
                okno.draw(krzyzyk1);
                sf::RectangleShape krzyzyk2(sf::Vector2f(szerKomorki / 2, 4.f));
                krzyzyk2.setPosition(j * szerKomorki + szerKomorki / 4, i * wysKomorki + (3 * wysKomorki / 4));
                krzyzyk2.setFillColor(sf::Color::Red);
                krzyzyk2.rotate(-45.f);
                okno.draw(krzyzyk2);
            }
            else if (plansza[i][j] == 'O') {
                sf::CircleShape kolko(szerKomorki / 4.f);
                kolko.setPosition(j * szerKomorki + szerKomorki * 0.25f, i * wysKomorki + wysKomorki * 0.25f);
                kolko.setFillColor(sf::Color::Transparent); // Brak wypełnienia
                kolko.setOutlineThickness(4.f);
                kolko.setOutlineColor(sf::Color::Black); // Zmieniono kolor obrysu
                okno.draw(kolko);
            }
        }
    }

    okno.display();
}

bool Gra::czyPrawidlowyRuch(int wiersz, int kolumna)
{
    return wiersz >= 0 && wiersz < rozmiar && kolumna >= 0 && kolumna < rozmiar && plansza[wiersz][kolumna] == ' ';
}

bool Gra::czyWygrana(char znak)
{
    // Sprawdzenie wierszy
    for (size_t i = 0; i < rozmiar; i++)
    {
        int licznik = 0;
        for (size_t j = 0; j < rozmiar; j++)
        {
            if (plansza[i][j] == znak) {
                licznik++;
                if (licznik == warunekWygranej)
                    return true;
            }
            else {
                licznik = 0;
            }
        }
    }

    // Sprawdzenie kolumn
    for (size_t j = 0; j < rozmiar; j++)
    {
        int licznik = 0;
        for (size_t i = 0; i < rozmiar; i++)
        {
            if (plansza[i][j] == znak) {
                licznik++;
                if (licznik == warunekWygranej)
                    return true;
            }
            else {
                licznik = 0;
            }
        }
    }

    // Sprawdzenie przekątnych (w dół i w prawo)
    for (size_t i = 0; i <= rozmiar - warunekWygranej; i++)
    {
        for (size_t j = 0; j <= rozmiar - warunekWygranej; j++) {
            int licznik = 0;
            for (size_t k = 0; k < warunekWygranej; k++)
            {
                if (plansza[i + k][j + k] == znak) {
                    licznik++;
                    if (licznik == warunekWygranej)
                        return true;
                }
                else {
                    licznik = 0;
                }
            }
        }
    }

    // Sprawdzenie przekątnych (w dół i w lewo)
    for (size_t i = 0; i <= rozmiar - warunekWygranej; i++)
    {
        for (size_t j = warunekWygranej - 1; j < rozmiar; j++) {
            int licznik = 0;
            for (size_t k = 0; k < warunekWygranej; k++)
            {
                if (plansza[i + k][j - k] == znak) {
                    licznik++;
                    if (licznik == warunekWygranej)
                        return true;
                }
                else {
                    licznik = 0;
                }
            }
        }
    }

    return false;
}

bool Gra::czyRemis()
{
    for (size_t i = 0; i < rozmiar; i++)
    {
        for (size_t j = 0; j < rozmiar; j++) {
            if (plansza[i][j] == ' ')
                return false;
        }
    }

    return true;
}

void Gra::ruchAI(std::vector<std::vector<char>>& plansza, char znak, char znakPrzeciwnika)
{
    int najlepszyWynik = INT_MIN;
    int najlepszyWiersz = -1;
    int najlepszaKolumna = -1;

    for (size_t i = 0; i < rozmiar; i++) {
        for (size_t j = 0; j < rozmiar; j++) {
            if (czyPrawidlowyRuch(i, j)) {
                plansza[i][j] = znak;
                int wynik = minimax(plansza, 0, false, znak, znakPrzeciwnika, INT_MIN, INT_MAX);
                plansza[i][j] = ' ';
                if (wynik > najlepszyWynik) {
                    najlepszyWynik = wynik;
                    najlepszyWiersz = i;
                    najlepszaKolumna = j;
                }
            }
        }
    }
    if (najlepszyWiersz != -1 && najlepszaKolumna != -1) {
        plansza[najlepszyWiersz][najlepszaKolumna] = znak;
    }
}

int Gra::minimax(std::vector<std::vector<char>>& plansza, int glebokosc, bool maksymalizujacyGracz, char znak, char znakPrzeciwnika, int alfa, int beta)
{
    if (glebokosc == maksGlebokosc || czyWygrana(znak) || czyWygrana(znakPrzeciwnika) || czyRemis()) {
        return ocen(plansza, znak, znakPrzeciwnika);
    }

    int najlepszyWiersz = -1;
    int najlepszaKolumna = -1;

    if (maksymalizujacyGracz) {
        int najlepszyWynik = INT_MIN;
        for (size_t i = 0; i < rozmiar; i++)
        {
            for (size_t j = 0; j < rozmiar; j++) {
                if (czyPrawidlowyRuch(i, j)) {
                    plansza[i][j] = znak;
                    int wynik = minimax(plansza, glebokosc + 1, false, znak, znakPrzeciwnika, alfa, beta);
                    plansza[i][j] = ' ';
                    najlepszyWynik = std::max(najlepszyWynik, wynik);
                    najlepszyWiersz = i;
                    najlepszaKolumna = j;
                    alfa = std::max(alfa, najlepszyWynik);
                    if (alfa >= beta) {
                        break;
                    }
                }
            }
            if (alfa >= beta) {
                break;
            }
        }
        return najlepszyWynik;
    }
    else {
        int najlepszyWynik = INT_MAX;
        for (int i = 0; i < rozmiar; ++i) {
            for (int j = 0; j < rozmiar; ++j) {
                if (czyPrawidlowyRuch(i, j)) {
                    plansza[i][j] = znakPrzeciwnika;
                    int wynik = minimax(plansza, glebokosc + 1, true, znak, znakPrzeciwnika, alfa, beta);
                    plansza[i][j] = ' ';
                    najlepszyWynik = std::min(najlepszyWynik, wynik);
                    beta = std::min(beta, najlepszyWynik);
                    if (alfa >= beta) {
                        break;
                    }
                }
            }
            if (alfa >= beta) {
                break;
            }
        }
        return najlepszyWynik;
    }

}

int Gra::ocen(std::vector<std::vector<char>>& plansza, char znak, char znakPrzeciwnika)
{
    // Sprawdzenie wierszy
    for (size_t i = 0; i < rozmiar; i++) {
        int licznikAI = 0;
        int licznikPrzeciwnika = 0;
        for (size_t j = 0; j < rozmiar; j++) {
            if (plansza[i][j] == znak) {
                licznikAI++;
            }
            else if (plansza[i][j] == znakPrzeciwnika) {
                licznikPrzeciwnika++;
            }
        }
        if (licznikAI == warunekWygranej) {
            return 100;  // AI wygrywa
        }
        else if (licznikPrzeciwnika == warunekWygranej) {
            return -100;  // Przeciwnik wygrywa
        }
    }

    // Sprawdzenie kolumn
    for (size_t j = 0; j < rozmiar; j++) {
        int licznikAI = 0;
        int licznikPrzeciwnika = 0;
        for (size_t i = 0; i < rozmiar; i++) {
            if (plansza[i][j] == znak) {
                licznikAI++;
            }
            else if (plansza[i][j] == znakPrzeciwnika) {
                licznikPrzeciwnika++;
            }
        }
        if (licznikAI == warunekWygranej) {
            return 100;  // AI wygrywa
        }
        else if (licznikPrzeciwnika == warunekWygranej) {
            return -100;  // Przeciwnik wygrywa
        }
    }

    // Sprawdzenie przekątnych
    int licznikAIPrzekatna1 = 0;
    int licznikPrzeciwnikaPrzekatna1 = 0;
    int licznikAIPrzekatna2 = 0;
    int licznikPrzeciwnikaPrzekatna2 = 0;
    for (size_t i = 0; i < rozmiar; i++) {
        if (plansza[i][i] == znak) {
            licznikAIPrzekatna1++;
        }
        else if (plansza[i][i] == znakPrzeciwnika) {
            licznikPrzeciwnikaPrzekatna1++;
        }

        if (plansza[i][rozmiar - i - 1] == znak) {
            licznikAIPrzekatna2++;
        }
        else if (plansza[i][rozmiar - i - 1] == znakPrzeciwnika) {
            licznikPrzeciwnikaPrzekatna2++;
        }
    }
    if (licznikAIPrzekatna1 == warunekWygranej || licznikAIPrzekatna2 == warunekWygranej) {
        return 100;  // AI wygrywa
    }
    else if (licznikPrzeciwnikaPrzekatna1 == warunekWygranej || licznikPrzeciwnikaPrzekatna2 == warunekWygranej) {
        return -100;  // Przeciwnik wygrywa
    }

    return 0;  // Remis lub brak wygranych
}
