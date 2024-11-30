#include <iostream>
#include "Gra.h"

int main()
{
    int rozmiar, warunekWygranej;

    /*std::cout << "Rozmiar planszy: ";
    std::cin >> rozmiar;
    std::cout << "\nWarunek wygranej (liczba znaków w rzędzie): ";
    std::cin >> warunekWygranej;*/

    Gra gra(3, 3);
    gra.dzialaj();

    return 0;
}
