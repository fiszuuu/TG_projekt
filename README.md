# Metoda Ford-Fulkersona
Powyższy jest projektem zaliczeniowym z teorii grafów w drugim semestrze studiów na AGH (ISI).
Znajduje on maksymalny przepływ w sieci przepływowej reprezentowanej przez graf za pomocą [metody Forda-Fulkersona](https://pl.wikipedia.org/wiki/Metoda_Forda-Fulkersona), ale ma też inne funkcjonalności np. znajdowanie macierzy incydencji na podstawie listy sąsiedztwa. 
Program przyjmuje plik w postaci **_macierzy wartości_**.

## Macierz Wartości
Macierz wartości jest moim autorskim pomysłem reprezentacji grafu skierowanego. Macierz ma wymiary nxn, gdzie n to liczba wierzchołków grafu. Numer wiersza reprezentuje początkowy wierzchołek krawędzi, natomiast numer kolumny końcowy, a wartość na tej pozycji wagę krawędzi. Na przykład gdy mamy na pozycji (1,3) wartość 4 to oznacza, że krawędzi z wierzchołka 1 do 3 ma wagę 4. Ponieważ program jest napisany pod metodę Forda-Fulkersona zakładam że wagi krawędzi są dodatnie, więc 0 sygnalizuje, że dana krawędź nie istnieje.![Graf, na którym domyślnie działa program](https://github.com/fiszuuu/TG_projekt/blob/main/graf_domy%C5%9Blny.png)

## Zastosowanie
Tak jak pisałem wyżej program znajduje maksymalny przepływ w grafie (reprezentujący jakąś sieć przepływową). Przykłady wykorzystania same się nasuwają. Po za tymi oczywistymi jak, sieć kanalizacyjna czy natężenie ruchu w miastach po oszacowaniu przepustowości rur (lub dróg w drugim przypadku), są też problemy mniej „namacalne” jak przepływ sieci internetowej lub prądu. W zasadzie wszędzie, gdzie chcemy coś przetransportować z punktu A do punktu B i sieć połączeń staje się bardziej skomplikowana metoda Forda-Fulkersona znajdzie swoje zastosowanie. Dlatego też stosowana jest ona do teraz, a dokładniej [algorytmu Edmondsa-Karpa](https://pl.wikipedia.org/wiki/Algorytm_Edmondsa-Karpa), który jest szczególną jej realizacją. 

## Obsługa programu
Nie zmieniwszy nic po uruchomieniu programu, będzie on wyświetlał ścieżki oraz maksymalny przepływ dla grafu zmieszczonego powyżej. Aby podać inny graf należy:
- zmienić zawartość pliku _value_matrix_ford_3_ lub
- w pliku _tests.h_ w funkcji _Ford_printing_paths_ (linia 196) podać inny plik, na którym chcemy działać (PROGRAM OCZEKUJE MACIERZY WARTOŚCI).
### Uwaga
Na ten moment program nie radzi sobie z grafami, w których pajawiają się cykle, ale dla praktycznego użycia metody Forda-Fulkersona nie jest to problem
