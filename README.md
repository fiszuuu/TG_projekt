# Metoda Ford-Fulkersona
Powyższy jest projektem zaliczeniowym z teorii grafów w drugim semestrze studiów na AGH (ISI).
Znajduje on maksymalny przepływ w sieci przepływowej reprezentowanej przez graf za pomocą [metody Forda-Fulkersona](https://pl.wikipedia.org/wiki/Metoda_Forda-Fulkersona).
Program przyjmuje plik w postaci **_macierzy wartości_**.

## Macierz Wartości
Macierz wartości jest moim autorskim pomysłem reprezentacji grafu skierowanego. Macierz ma wymiary nxn, gdzie n to liczba wierzchołków grafu. Numer wiersza reprezentuje początkowy wierzchołek krawędzi, natomiast numer kolumny końcowy, a wartość na tej pozycji wagę krawędzi. Na przykład gdy mamy na pozycji (1,3) wartość 4 to oznacza, że krawędzi z wierzchołka 1 do 3 ma wagę 4. Poniważ program jest napisany pod metodę Forda-Fulkersona zakładam że wagi krawędzi są dodatnie i 0 sygnalizuje, że dana krawędź nie istnieje.![Graf, na którym domyślnie działa program](https://github.com/fiszuuu/TG_projekt/blob/main/graf_domy%C5%9Blny.pdf)
