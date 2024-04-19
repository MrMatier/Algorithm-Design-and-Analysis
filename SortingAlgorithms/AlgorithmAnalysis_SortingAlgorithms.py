import csv
import time
import time
import statistics

#plik CSV
plik = 'C:/Users/matiu/Downloads/PAA.projekt1.dane.csv'

with open(plik, 'r', encoding='utf-8') as csvfile:
    csvreader = csv.reader(csvfile)
    next(csvreader, None)

    przetworzone_filmy = []
    filmy_przed = 0  #ile przed filtracją
    start = time.time()  #start pomiar czasu

    for row in csvreader:
        filmy_przed += 1  # ++ licznik dla każdego wiersza
        if len(row) >= 3 and row[2]:
            try:
                #ocena na float
                ocena = float(row[2])
                przetworzone_filmy.append((row[0], row[1], ocena))
            except ValueError:
                #pommiń wiersz jeśli ocena nie liczba
                continue

    koniec = time.time()  #koniec pomiar czasu
    czas_przetwarzania = koniec - start

#wyświetlenie przefiltrowanych danych
#print(f'przefiltrowane filmy: {przetworzone_filmy[:10]}...')  #pierwsze 10
print(f'czas przetwarzania: {czas_przetwarzania} sekund')
print(f'czy wszystkie przefiltrowane filmy mają oceny? {all(isinstance(film[2], (int, float)) for film in przetworzone_filmy)}')
print(f'liczba filmów przed filtracją: {filmy_przed}')  #ile wierszy przed filtracją
print(f'liczba filmów po filtracji: {len(przetworzone_filmy)}\n')  #ile wierszy po filtracji
print('=============================================================================================\n')
#================================================================Struktury danych========================================================================

#ilość danych do struktur
ile_danych = [10000, 100000, 500000, 1000000]

struktury_danych = {}
for ilosc in ile_danych:
    #czy jest wystarczająca liczba filmów
    aktualna_ilosc = min(ilosc, len(przetworzone_filmy))
    struktury_danych[ilosc] = przetworzone_filmy[:aktualna_ilosc]
    print(f"stworzono strukturę z {aktualna_ilosc} elementów (zamierzona ilość: {ilosc}).")

#struktura z maks ilością danych
struktury_danych['max'] = przetworzone_filmy
print(f"stworzono strukturę max z {len(przetworzone_filmy)} elementów.\n")

#pierwsze 10 filmów z każdej struktury dla weryfikacji
# for nazwa, struktura in struktury_danych.items():
#     if isinstance(nazwa, int):
#         print(f"pierwsze 10 elementów w strukturze {nazwa}: {struktura[:10]}")
#     else:
#         print(f"pierwsze 10 elementów w strukturze {nazwa}: {struktura[:10]}")
print('=============================================================================================\n')
#==============================================================Sortowania==========================================================================

def merge_sort(lista):
    if len(lista) <= 1:
        return lista

    #dzielenie listy na połowy
    srodek = len(lista) // 2
    lewa_polowa = merge_sort(lista[:srodek])
    prawa_polowa = merge_sort(lista[srodek:])

    #sccalenie posortowanych połówek
    return merge(lewa_polowa, prawa_polowa)


def merge(lewa, prawa):
    posortowana_lista = []
    lewy_index, prawy_index = 0, 0

    #scalenie dwóch posortowanych list w jedną
    while lewy_index < len(lewa) and prawy_index < len(prawa):
        if lewa[lewy_index][2] <= prawa[prawy_index][2]:  #porównaj oceny
            posortowana_lista.append(lewa[lewy_index])
            lewy_index += 1
        else:
            posortowana_lista.append(prawa[prawy_index])
            prawy_index += 1

    #dodanie pozostałych elementów jeśli jakieś zostały
    posortowana_lista.extend(lewa[lewy_index:])
    posortowana_lista.extend(prawa[prawy_index:])

    return posortowana_lista

def quicksort(lista):
    if len(lista) <= 1:
        return lista

    pivot = lista[len(lista) // 2][2]  #środkowy element jako pivot
    mniejsze = [x for x in lista if x[2] < pivot]
    rowne = [x for x in lista if x[2] == pivot]
    wieksze = [x for x in lista if x[2] > pivot]

    return quicksort(mniejsze) + rowne + quicksort(wieksze)

def insertion_sort(lista, key=lambda x: x):
    for i in range(1, len(lista)):
        aktualny_element = lista[i]
        aktualny_klucz = key(aktualny_element)
        j = i - 1
        while j >= 0 and key(lista[j]) > aktualny_klucz:
            lista[j + 1] = lista[j]
            j -= 1
        lista[j + 1] = aktualny_element
    return lista

def bucket_sort(lista, liczba_kubelkow=10):
    if len(lista) == 0:
        return lista

    #maksymalna i minimalna wartość ocen
    min_value, max_value = min(lista, key=lambda x: x[2])[2], max(lista, key=lambda x: x[2])[2]
    bucket_range = (max_value - min_value) / liczba_kubelkow

    #inicjalizacja kubelków
    buckets = [[] for _ in range(liczba_kubelkow)]

    #przypisanie elementów do odpowiednich kubelków
    for film in lista:
        bucket_index = int((film[2] - min_value) // bucket_range)
        if bucket_index == liczba_kubelkow:
            bucket_index -= 1
        buckets[bucket_index].append(film)

    #sortowanie elementów w każdym kubelku i ich scalanie
    return [film for bucket in buckets for film in insertion_sort(bucket, key=lambda x: x[2])]#sorted


#wywołanie sortowań (można dobrać liczbę kubełków do danych)
sort_scalanie = {nazwa: merge_sort(lista) for nazwa, lista in struktury_danych.items()}

sort_quicksort = {nazwa: quicksort(lista) for nazwa, lista in struktury_danych.items()}

sort_bucket = {nazwa: bucket_sort(lista, liczba_kubelkow=100) for nazwa, lista in struktury_danych.items()}

# #pierwsze 10 posortowanych filmów
# for nazwa, lista in sort_scalanie.items():
#     print(f"pierwsze 10 posortowanych przez scalanie dla '{nazwa}': {lista[:10]}")
#
# for nazwa, lista in sort_quicksort.items():
#     print(f"pierwsze 10 posortowanych quicksort dla '{nazwa}': {lista[:10]}")
#
# for nazwa, lista in sort_bucket.items():
#     print(f"pierwsze 10 posortowanych kubełkowo dla '{nazwa}': {lista[:10]}")

#================================================================Test========================================================================
def test(lista):
    #czy lista pusta lub zawiera jeden element
    if len(lista) < 2:
        return True
    #czy lista posortowana rosnąco według oceny
    return all(lista[i][2] <= lista[i + 1][2] for i in range(len(lista) - 1))

#czy struktury zostały posortowane
for nazwa, lista in sort_scalanie.items():
    print(f"czy lista {nazwa} posortowana przez scalanie? {test(lista)}")

for nazwa, lista in sort_quicksort.items():
    print(f"czy lista {nazwa} posortowana quicksort? {test(lista)}")

for nazwa, lista in sort_bucket.items():
    print(f"czy lista {nazwa} posortowana kubełkowo? {test(lista)}")
print('\n=============================================================================================\n')
#=================================================================Zapisanie do pliku=======================================================================

def zapisz(nazwa_struktury, lista_przed, lista_po):
    #zapisywanie przed sortowaniem
    with open(f'{nazwa_struktury}_przed_sortowaniem.txt', 'w', encoding='utf-8') as plik:
        for film in lista_przed:
            plik.write(f"{film[0]}, {film[1]}, ocena: {film[2]}\n")

    #zapisywanie listy po
    with open(f'{nazwa_struktury}_po_sortowaniu.txt', 'w', encoding='utf-8') as plik:
        for film in lista_po:
            plik.write(f"{film[0]}, {film[1]}, ocena: {film[2]}\n")


# #zapis danych posortowanych
# for nazwa, lista in sort_scalanie.items():
#     zapisz(f'scalanie_{nazwa}', struktury_danych[nazwa], lista)
#
# for nazwa, lista in sort_quicksort.items():
#     zapisz(f'quicksort_{nazwa}', struktury_danych[nazwa], lista)
#
# for nazwa, lista in sort_bucket.items():
#     zapisz(f'bucket_{nazwa}', struktury_danych[nazwa], lista)

#===============================================================Statystyki=========================================================================

#obliczanie średniej i mediany rankingu
def oblicz_statystyki(lista):
    oceny = [film[2] for film in lista]
    srednia = statistics.mean(oceny)
    mediana = statistics.median(oceny)
    return srednia, mediana

#mierzenie czasu sortowania
def czas_sortowania(funkcja_sortujaca, lista):
    start = time.time()
    posortowana_lista = funkcja_sortujaca(lista)
    koniec = time.time()
    ile_sortuje = koniec - start
    return ile_sortuje, posortowana_lista

jakie_sortowanie = {
    'Scalanie': merge_sort,
    'Quicksort': quicksort,
    'Kubełkowe': bucket_sort
}

#słownik na przechowywanie wyników
wyniki = {}

for metoda, funkcja in jakie_sortowanie.items():
    wyniki[metoda] = {}
    for nazwa_struktury, lista in struktury_danych.items():
        ile_sortuje, posortowana_lista = czas_sortowania(funkcja, lista)
        srednia, mediana = oblicz_statystyki(posortowana_lista)
        wyniki[metoda][nazwa_struktury] = {
            'czas sortowania': ile_sortuje,
            'średnia ocena': srednia,
            'mediana oceny': mediana
        }

#wyświetlenie
for metoda, dane in wyniki.items():
    print(f"jakie sortowania: {metoda}")
    for nazwa_struktury, statystyki in dane.items():
        print(f"  struktura danych: {nazwa_struktury}")
        print(f"    czas sortowania: {statystyki['czas sortowania']:.4f} sekund")
        print(f"    średnia ocena: {statystyki['średnia ocena']:.2f}")
        print(f"    mediana oceny: {statystyki['mediana oceny']}\n")
    print('\n=============================================================================================\n')

#===============================================================Mała i duża lista=========================================================================

def merge_sort1(lista):
    if len(lista) <= 1:
        return lista

    #dzielenie listy na połowy
    srodek = len(lista) // 2
    lewa_polowa = merge_sort1(lista[:srodek])
    prawa_polowa = merge_sort1(lista[srodek:])

    #scalenie posortowanych połówek
    return merge1(lewa_polowa, prawa_polowa)

def merge1(lewa, prawa):
    posortowana_lista = []
    lewy_index, prawy_index = 0, 0

    #scalenie dwóch posortowanych list w jedną
    while lewy_index < len(lewa) and prawy_index < len(prawa):
        if lewa[lewy_index] <= prawa[prawy_index]:
            posortowana_lista.append(lewa[lewy_index])
            lewy_index += 1
        else:
            posortowana_lista.append(prawa[prawy_index])
            prawy_index += 1

    #dodanie pozostałych elementów jeśli jakieś zostały
    posortowana_lista.extend(lewa[lewy_index:])
    posortowana_lista.extend(prawa[prawy_index:])

    return posortowana_lista

def quicksort1(lista):
    if len(lista) <= 1:
        return lista

    pivot = lista[len(lista) // 2]  #środkowy element jako pivot
    mniejsze = [x for x in lista if x < pivot]
    rowne = [x for x in lista if x == pivot]
    wieksze = [x for x in lista if x > pivot]

    return quicksort1(mniejsze) + rowne + quicksort1(wieksze)

def bucket_sort1(lista, liczba_kubelkow=10):
    if len(lista) == 0:
        return lista

    min_value, max_value = min(lista), max(lista)
    bucket_range = (max_value - min_value) / liczba_kubelkow + 1

    buckets = [[] for _ in range(liczba_kubelkow)]

    for x in lista:
        bucket_index = int((x - min_value) / bucket_range)
        buckets[bucket_index].append(x)

    return [x for bucket in buckets for x in insertion_sort(bucket)]

import random

#generowanie małej i dużej losowej listy liczb
mala_lista = [random.randint(1, 100) for _ in range(10)]
duza_lista = [random.randint(1, 10000) for _ in range(10000)]

#mała lista
mala_merge = merge_sort1(mala_lista)
mala_quick = quicksort1(mala_lista)
mala_bucket = bucket_sort1(mala_lista, liczba_kubelkow=5)

#duż,a lista
duza_merge = merge_sort1(duza_lista)
duza_quick = quicksort1(duza_lista)
duza_bucket = bucket_sort1(duza_lista, liczba_kubelkow=100)

print("mała lista przed sortowaniem:", mala_lista)
print("mała lista po (merge sort):", mala_merge)
print("mała lista po (quicksort):", mala_quick)
print("mała lista po (bucket sort):", mala_bucket)

print("\nsortowanie dużej listy wykonane, to pierwsze 10 każdego sortowania:")
print("duża lista po (merge sort):", duza_merge[:10])
print("duża lista po (quicksort):", duza_quick[:10])
print("duża lista po (bucket sort):", duza_bucket[:10])