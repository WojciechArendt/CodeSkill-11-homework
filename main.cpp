/*
 temat przewodni: Złożoność obliczeniowa

 treść:
 Znajdź pierwszą [licząc od lewej]* brakującą pozytywną liczbę całkowitą w podanej posortowanej tablicy/liście.
 do rozwiązania nie używaj wbudowanych funkcji takich jak (find/search, in itp.).
 Zadanie należy rozwiązać skupiając się na możliwie małej ilości potrzebych operacji oraz pamięci.

 *to moje własne założenie
 
 I kilka przykładów:
 INPUT: [1,2,3,7,8]
 OUTPUT: 4
 
 Pamiętaj, że:
 1. Zbiór może zawierać liczby ujemne i zero lub nawet składać się wyłącznie z nich.
 2. Zbiór może nie zawierać braków np. [1,2,3].
 3. Zbiór może być posortowany rosnąco lub malejąco.
 4. Zbiór może zawierać powtórzenia np. [1,2,2,2,2,2,2,2,4].
 5. Zbiór może być pusty.
 
 Zakładam, że pierwsza brakująca pozytywna liczba w danym zbiorze jest równa...:
 a)...1 gdy zbiór jest pusty
 b)...1 gdy zbiór składa się z jednakowych elementów (lub jednego elementu), a nie są to jedynki (np. [2], [3,3,3,3,3,3,3], [-8,-8,-8,-8])
 c)...2 gdy zbiór składa się z samych jedynek (np. [1,1,1,1])
 d)...1 gdy zbiór jest posortowany rosnąco, a ostatnia liczba zbioru jest mniejsza od 1 (np. [-5,-3,-2])
 e)...1 gdy zbiór jest posortowany malejąco, a pierwsza liczba zbioru jest mniejsza od 1 (np. [-2,-3,-5])
 f)...1 gdy zbiór jest posortowany rosnąco, nie zawiera braków, a pierwsza liczba w zbiorze jest mniejsza od 1 (np. [3,3,4,5])
 g)...ostatniej liczbie w zbiorze +1 gdy zbiór jest posortowany rosnąco i nie zawiera braków pomiędzy liczbami pozytywnymi (np. 6 w [-99,-2,1,2,3,3,4,5])
 h)...pierwszej liczbie w zbiorze +1 gdy zbiór jest posortowany malejąco i nie zawiera braków pomiędzy liczbami pozytywnymi (np. 6 w [5,4,3,3], i również 6 w [5,4,3,3,2,1,-2,-99])
 */

#include <iostream>

using namespace std;

int FindFirstPositiveInteger(int tab[],int size) // niestety w C++ muszę posłużyć się dwoma argumentami: tablicą i jej rozmiarem (tj. ilością elementów tablicy). Jeżeli ktoś wie jak to można zrobić inaczej, to bardzo chętnie się dowiem :)
{
    if (size == 0) return 1; // stosuję założenie "a)"
    
    // w pozostałych przypadkach sprawdzam, czy zbiór jest posortowany rosnąco, malejąco (sprawdzam poprzez porównanie wartości pierwszego indeksu (tj. 0) z ostatnim (tab[size-1]))
    else if (tab[0] < tab[size-1]) // jeżeli tak, to zbiór jest posortowany rosnąco
    {
        if (tab[size-1] < 1) return 1; // stosuję założenie "d)"
        else for (int i=1; i<size; i++) // szukam pierwszej brakującej liczby pozytywnej
        {
            if (tab[i-1]+1 < tab[i] && tab[i] > 1) // jeżeli dana liczba +1 jest mniejsza od kolejnej liczby w zbiorze i jednocześnie kolejna liczba jest większa od 1, to znaczy, że znaleziono brak...
            {
                if (tab[i-1]+1 < 1) return 1; //...i zwracam 1 w przypadku, gdy dana liczba +1 jest mniejsza od 1 (np. [-4,3])...
                else return tab[i-1]+1; //...jeżeli nie jest mniejsza, to zwracam daną liczbę +1
            }
            else if (i == size-1) // (zabezpieczenie przed wychodzeniem poza indeks tablicy) jeżeli "i" będzie równe ostatniemu indeksowi w tablicy (a warunek poprzedniego if'a nie został spełniony), to znaczy, że zbiór nie zawiera braków pomiędzy liczbami pozytywnymi...
            {
                if (tab[0] > 1) return 1; //...i stosuję założenie "f)"...
                else return tab[i]+1; //...lub "g)"
            }
        }
    }
    
    else if (tab[0] > tab[size-1]) // jeżeli tak, to zbiór jest posortowany malejąco
    {
        if (tab[0] < 1) return 1; // stosuję założenie "e)"
        else for (int i=1; i<size; i++) // szukam pierwszej brakującej liczby pozytywnej
        {
            if (tab[i-1]-1 > tab[i]) // jeżeli dana liczba -1 jest większa od kolejnej liczby w zbiorze, to znaczy, że znaleziono brak...
            {
                if (tab[i-1]-1 <1) return tab[0]+1;//...i jeżeli dana liczba -1 jest mniejsza od 1, to zwracam wartość pierwszego indeksu +1...
                else return tab[i-1]-1;//...w innym wypadku zwracam daną liczbę -1
            }
            else if (i == size-1 || tab[i] < 1 ) return tab[0]+1; // (zabezpieczenie przed wychodzeniem poza indeks tablicy) jeżeli "i" będzie równe ostatniemu indeksowi w tablicy (a warunek poprzedniego if'a nie został spełniony) lub gdy kolejna liczba w zbiorze jest mniejsza od 1 to znaczy, że zbiór nie zawiera braków pomiędzy liczbami pozytywnymi i stosuję założenie "h)"
        }
    }
    
    //jeżeli nie jest posortowany ani malejąco, ani rosnąco, to znaczy, że zbiór składa się z jednakowych elementów (lub jednego elementu) i stosuję założenia...
    else if (tab [0] != 1) return 1; //..."b)"...
    else return 2; //...lub "c)"
    
    return -1; // bez return'a poza if'em i else'em nie chce się kompilować. Przynajmniej wiadomo, że jak zwróci -1, to coś jest nie tak, choć do takiego przypadku nie powinno dojść
}

int main() // zestaw testów, na których sprawdzałem poprawność działania algorytmu
{
    //testy założeń:
    int test_a[] = {}; // 1
    int test_b1[] = {2}; // 1
    int test_b2[] = {3,3,3,3,3,3,3}; // 1
    int test_b3[] = {-8,-8,-8,-8}; // 1
    int test_c[] = {1,1,1,1}; // 2
    int test_d[] = {-5,-3,-2}; // 1
    int test_e[] = {-2,-3,-5}; // 1
    int test_f[] = {3,3,4,5}; // 1
    int test_g[] = {-99,-2,1,2,3,3,4,5}; // 6
    int test_h1[] = {5,4,3,3}; // 6
    int test_h2[] = {5,4,3,3,2,1,-2,-99}; // 6
    
    cout<<"Assumptions tests:\n";
    cout<<"Test a, should return 1: "<<FindFirstPositiveInteger(test_a,sizeof(test_a)/sizeof(int))<<endl;
    cout<<"Test b1, should return 1: "<<FindFirstPositiveInteger(test_b1,sizeof(test_b1)/sizeof(int))<<endl;
    cout<<"Test b2, should return 1: "<<FindFirstPositiveInteger(test_b2,sizeof(test_b2)/sizeof(int))<<endl;
    cout<<"Test b3, should return 1: "<<FindFirstPositiveInteger(test_b3,sizeof(test_b3)/sizeof(int))<<endl;
    cout<<"Test c, should return 2: "<<FindFirstPositiveInteger(test_c,sizeof(test_c)/sizeof(int))<<endl;
    cout<<"Test d, should return 1: "<<FindFirstPositiveInteger(test_d,sizeof(test_d)/sizeof(int))<<endl;
    cout<<"Test e, should return 1: "<<FindFirstPositiveInteger(test_e,sizeof(test_e)/sizeof(int))<<endl;
    cout<<"Test f, should return 1: "<<FindFirstPositiveInteger(test_f,sizeof(test_f)/sizeof(int))<<endl;
    cout<<"Test g, should return 6: "<<FindFirstPositiveInteger(test_g,sizeof(test_g)/sizeof(int))<<endl;
    cout<<"Test h1, should return 6: "<<FindFirstPositiveInteger(test_h1,sizeof(test_h1)/sizeof(int))<<endl;
    cout<<"Test h2, should return 6: "<<FindFirstPositiveInteger(test_h2,sizeof(test_h2)/sizeof(int))<<endl;
    
    //pozostałe testy
    int test1[] = {1,2,3,7,8}; // 4
    int test2[] = {8,7,3,2,1}; // 6
    int test3[] = {-8,-3,-2,-1,0}; // 1
    int test4[] = {0,-1,-2,-3,-8}; // 1
    int test5[] = {-3,-1,0,1,3}; // 2
    int test6[] = {-3,-2,0,2,3}; // 1
    int test7[] = {3,1,0,-1,-3}; // 2
    int test8[] = {3,2,0,-2,-3}; // 1
    int test9[] = {-1,1}; // 2
    int test10[] = {1,-1}; // 2
    int test11[] = {0,2}; // 1
    int test12[] = {2,0}; // 1
    int test13[] = {-4,3}; // 1
    int test14[] = {3,-4}; // 2
    
    cout<<"\nOther tests:\n";
    cout<<"Test 1, should return 4: "<<FindFirstPositiveInteger(test1,sizeof(test1)/sizeof(int))<<endl;
    cout<<"Test 2, should return 6: "<<FindFirstPositiveInteger(test2,sizeof(test2)/sizeof(int))<<endl;
    cout<<"Test 3, should return 1: "<<FindFirstPositiveInteger(test3,sizeof(test3)/sizeof(int))<<endl;
    cout<<"Test 4, should return 1: "<<FindFirstPositiveInteger(test4,sizeof(test4)/sizeof(int))<<endl;
    cout<<"Test 5, should return 2: "<<FindFirstPositiveInteger(test5,sizeof(test5)/sizeof(int))<<endl;
    cout<<"Test 6, should return 1: "<<FindFirstPositiveInteger(test6,sizeof(test6)/sizeof(int))<<endl;
    cout<<"Test 7, should return 2: "<<FindFirstPositiveInteger(test7,sizeof(test7)/sizeof(int))<<endl;
    cout<<"Test 8, should return 1: "<<FindFirstPositiveInteger(test8,sizeof(test8)/sizeof(int))<<endl;
    cout<<"Test 9, should return 2: "<<FindFirstPositiveInteger(test9,sizeof(test9)/sizeof(int))<<endl;
    cout<<"Test 10, should return 2: "<<FindFirstPositiveInteger(test10,sizeof(test10)/sizeof(int))<<endl;
    cout<<"Test 11, should return 1: "<<FindFirstPositiveInteger(test11,sizeof(test11)/sizeof(int))<<endl;
    cout<<"Test 12, should return 1: "<<FindFirstPositiveInteger(test12,sizeof(test12)/sizeof(int))<<endl;
    cout<<"Test 13, should return 1: "<<FindFirstPositiveInteger(test13,sizeof(test13)/sizeof(int))<<endl;
    cout<<"Test 14, should return 2: "<<FindFirstPositiveInteger(test14,sizeof(test14)/sizeof(int))<<endl;
    
    return 0;
}
