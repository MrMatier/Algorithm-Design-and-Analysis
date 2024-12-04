#include <iostream>
#include "Granie.h"

int main()
{
    int rozmiar, warunekWygranej;
    while (1) {
        std::cout << "Rozmiar planszy: ";
        std::cin >> rozmiar;
        std::cout << "\nIle znakow w rzedzie: ";
        std::cin >> warunekWygranej;
        Gra gra(rozmiar, warunekWygranej);
        gra.dzialaj();
    }


    return 0;
}
