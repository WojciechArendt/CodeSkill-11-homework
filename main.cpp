/*
 temat przewodni: Złożoność obliczeniowa
 
 [6:02]
 treść:
 Znajdź pierwszą brakującą pozytywną liczbę całkowitą w podanej posortowanej tablicy/liście.
 do rozwiązania nie używaj wbudowanych funkcji takich jak (find/search, in itp.).
 Zadanie należy rozwiązań skupiając się na możliwie małej ilości potrzebych operacji oraz pamięci.
 
 
 [6:02]
 I kilka przykładów:
 INPUT: [1,2,3,7,8]
 OUTPUT: 4
 
 
 [6:03]
 Żeby nie było za pięknie, przesyłamy drobre kruczki
 1. co jeśli zbiór zawiera nie tylko liczby dodatnie?
 2. co jeśli zbiór nie zawiera braków np. [1,2,3]?
 */

#include <iostream>

using namespace std;

int FindFirstPositiveInteger(int tab[],int size) // niestety w C++ muszę posłużyć się dwoma argumentami: tablicą i jej rozmiarem (tj. ilością elementów tablicy). Jeżeli kotś wie jak to można zrobić inaczej, to bardzo chętnie się dowiem :)
{
    if (size == 0) return 1; // Przyjąłem, że pusta tablica zwróci 1. Coś z takim fantem trzeba zrobić.
    if (size == 1) // jeżeli tablica zawiera jedną liczbę...
    {
        if (tab[0]+1 < 1) return 1; //...i ta liczba +1 jest mniejsza od 1, to zwracam 1...
        else return tab[0]+1; //...w przeciwnym wypadku zwracam tę liczbę zwiększoną o 1
    }
    else // pozostałą część działa dla tablic posiadających 2 i więcej elementów
    {
        for (int i=1; i<size; i++)
        {
            if (tab[i-1]+1 != tab[i] && tab[i] > 1) // jeżeli dana liczba +1 jest różna od kolejnej liczby w ciągu (to znaczy, że jest przerwa wciągu) i jednocześnie kolejna liczba jest większa od 1...
            {
                if (tab[i-1]+1 < 1) return 1; //...to zwracam 1 w przypadku, gdy dana liczba +1 jest mniejsza od 1...
                else return tab[i-1]+1; //...jeżeli nie jest mniejsza, to zwracam daną liczbę +1
            }
            else if (i == size-1) // (zabezpieczenie przed wychdzeniem poza indeks tablicy) jeżeli i będzie równe ostatniemu indeksowi w tablicy (a warunek poprzedniego if'a nie został spełniony)...
            {
                if (tab[i]+1 < 1) return 1; //...to zwracam 1 jeżeli wartość ostatniego indeksu +1 jest mniejsza od 1...
                else return tab[i]+1; //...w przeciwnym wypadku zwracam wartość ostatniego indeksu +1
            }
        }
    }
    return -1; // bez return'a poza if'em i else'em nie chce się kompilować. Przynajmniej wiadomo, że jak zwróci -1, to coś jest nie tak
}

int main() // zestaw testów, na których sprawdzałem poprawność działania algorytmu
{
    int test1[] = {1,2,3,7,8}; // 4
    int test2[] = {1,2,3,4,5}; // 6
    int test3[] = {-8,-4,-3,-2,-1}; // 1
    int test4[] = {-5,-4,-3,-2,-1}; // 1
    int test5[] = {-8,-5,-4,-3,-2}; // 1
    int test6[] = {-6,-5,-4,-3,-2}; // 1
    int test7[] = {-4,-3,-2,-1,0}; // 1
    int test8[] = {-8,-3,-2,-1,0}; // 1
    int test9[] = {-3,-1,0,1,3}; // 2
    int test10[] = {-3,-2,0,2,3}; // 1
    int test11[] = {1,1,1}; // 2
    int test12[] = {-1,-1,-1}; // 1
    int test13[] = {0,0,0}; // 1
    int test14[] = {3,3,3}; // 4
    int test15[] = {-3,-3,-3}; // 1
    int test16[] = {-2}; // 1
    int test17[] = {0}; // 1
    int test18[] = {2}; // 3
    int test19[] = {-1,1}; // 2
    int test20[] = {0,2}; // 1
    int test21[] = {-4,2}; // 1
    
    cout<<"Test 1, should return 4: "<<FindFirstPositiveInteger(test1,sizeof(test1)/sizeof(int))<<endl;
    cout<<"Test 2, should return 6: "<<FindFirstPositiveInteger(test2,sizeof(test2)/sizeof(int))<<endl;
    cout<<"Test 3, should return 1: "<<FindFirstPositiveInteger(test3,sizeof(test3)/sizeof(int))<<endl;
    cout<<"Test 4, should return 1: "<<FindFirstPositiveInteger(test4,sizeof(test4)/sizeof(int))<<endl;
    cout<<"Test 5, should return 1: "<<FindFirstPositiveInteger(test5,sizeof(test5)/sizeof(int))<<endl;
    cout<<"Test 6, should return 1: "<<FindFirstPositiveInteger(test6,sizeof(test6)/sizeof(int))<<endl;
    cout<<"Test 7, should return 1: "<<FindFirstPositiveInteger(test7,sizeof(test7)/sizeof(int))<<endl;
    cout<<"Test 8, should return 1: "<<FindFirstPositiveInteger(test8,sizeof(test8)/sizeof(int))<<endl;
    cout<<"Test 9, should return 2: "<<FindFirstPositiveInteger(test9,sizeof(test9)/sizeof(int))<<endl;
    cout<<"Test 10, should return 1: "<<FindFirstPositiveInteger(test10,sizeof(test10)/sizeof(int))<<endl;
    cout<<"Test 11, should return 2: "<<FindFirstPositiveInteger(test11,sizeof(test11)/sizeof(int))<<endl;
    cout<<"Test 12, should return 1: "<<FindFirstPositiveInteger(test12,sizeof(test12)/sizeof(int))<<endl;
    cout<<"Test 13, should return 1: "<<FindFirstPositiveInteger(test13,sizeof(test13)/sizeof(int))<<endl;
    cout<<"Test 14, should return 4: "<<FindFirstPositiveInteger(test14,sizeof(test14)/sizeof(int))<<endl;
    cout<<"Test 15, should return 1: "<<FindFirstPositiveInteger(test15,sizeof(test15)/sizeof(int))<<endl;
    cout<<"Test 16, should return 1: "<<FindFirstPositiveInteger(test16,sizeof(test16)/sizeof(int))<<endl;
    cout<<"Test 17, should return 1: "<<FindFirstPositiveInteger(test17,sizeof(test17)/sizeof(int))<<endl;
    cout<<"Test 18, should return 3: "<<FindFirstPositiveInteger(test18,sizeof(test18)/sizeof(int))<<endl;
    cout<<"Test 19, should return 2: "<<FindFirstPositiveInteger(test19,sizeof(test19)/sizeof(int))<<endl;
    cout<<"Test 20, should return 1: "<<FindFirstPositiveInteger(test20,sizeof(test20)/sizeof(int))<<endl;
    cout<<"Test 21, should return 1: "<<FindFirstPositiveInteger(test21,sizeof(test21)/sizeof(int))<<endl;
    
    return 0;
}
