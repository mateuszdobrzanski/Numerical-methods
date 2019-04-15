#include <iostream>
#include <math.h>
#include <cstdlib>
#include <time.h>
#include <windows.h>

using namespace std;

/* Inicjalizacja funkcji */

void StartCounter();
double GetCounter();

double wzorFunkcji(double x); //Inicjalizacja funkcji, odpowiadajacej za obliczenie wartoœci z wzoru funkcji

void trapezy(double a, double b, int n); //Inicjalizacja funkcji, odpowiadajacej za obliczenie calki metoda trapezow
void simpson(double a, double b, int n); //Inicjalizacja funkcji, odpowiadajacej za obliczenie calki metoda simpsona
void newton(double a, double b, int n); //Inicjalizacja funkcji, odpowiadajacej za obliczenie calki metoda newtona
void monteCarlo(double a, double b, int n); //Inicjalizacja funkcji, odpowiadajacej za obliczenie calki metoda monte carlo
void crudeMonteCarlo(double a, double b, int n); //Inicjalizacja funkcji, odpowiadajacej za obliczenie calki metoda crude monte carlo
void metodaAkceptacjiOdrzucen(double a, double b, double d, int n);

/* Zmienne globalne dla funkcji mierzacych czas */
double PCFreq = 0.0;
__int64 CounterStart = 0;

/* Blok glowny */
int main()
{
    srand(time(NULL)); //Inicjalizacja funkcji, odpowiadajacej za losowanie liczb pseudolosowych

    double wynik, poczatekPrzedzialu, koniecPrzedzialu;
    int d, n, N;

     clock_t startT, endT;

    cout << "Prosze podac poczatek przedzialu calkowania: "; cin >> poczatekPrzedzialu;
    cout << "Prosze podac koniec przedzialu calkowania: "; cin >> koniecPrzedzialu;
    cout << "Prosze podac 'n' dla metody Trapezow, Simpsona oraz Newtona: "; cin >> n;
    cout << "Prosze podac 'N' dla metody Monte Carlo: "; cin >> N;
    cout << "Prosze podac 'd' dla metody Akceptacji Odrzucen: "; cin >> d; cout << endl;


    system("CLS");

/* Wyswietlene wartosci calkowania metodami numerycznymi */

    StartCounter(); // rozpoczecie zliczania czasu pracy dla programu

    trapezy(poczatekPrzedzialu, koniecPrzedzialu, n);
    simpson(poczatekPrzedzialu, koniecPrzedzialu, n);
    newton(poczatekPrzedzialu, koniecPrzedzialu, n);
    monteCarlo(poczatekPrzedzialu, koniecPrzedzialu, N);
    crudeMonteCarlo(poczatekPrzedzialu, koniecPrzedzialu, N);
    metodaAkceptacjiOdrzucen(poczatekPrzedzialu, koniecPrzedzialu, d, N);

    double czas = GetCounter(); // zakonczenie zliczania czasu pracy dla algorytmu
    cout << endl << "Czas pracy algorytmu: " << czas << " ms." << endl << endl;

    system("pause");

    return 0;
}

/* Definicja funkcji */

void StartCounter(){
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
	cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart)/1000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double GetCounter(){
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}

double wzorFunkcji(double x){ //metoda, odpowiedzialna za liczenie wartosci w poszczegolnym punkcie
    return (x);
}

void trapezy(double a, double b, int n){ //metoda trapezow

    StartCounter(); // rozpoczecie zliczania czasu pracy dla algorytmu

    double x0 = wzorFunkcji(a); //wartosc jaka przyjmuje funkcja w poczatkowym punkcie przedzialu
    double xN = wzorFunkcji(b); //wartosc jaka przyjmuje funkcja w koncowym punkcie przedzialu
    double h = (double)((b-a)/n); //obliczenie "wyosoksci" przedzialu
    double wartosc = 0; // zmienna konieczna do przechowywania wartosci

   /* for(int i = 1; i < n; i++){
        if((a + i*h) < xN) wartosc += 2*wzorFunkcji(a + (i*h));
    }
    double wynik = ((x0+xN+wartosc)*h) / 2;*/


    double stop = a+h; //zapoczatkowanie warunku koniecznego do zatrzymania sie petli while
    int i = 0; //zmienna pomocnicza
    while(stop < b){
        i++;
        if((a + (i*h)) < b) wartosc += 2*wzorFunkcji(a + (i*h));
        stop += h; //warunek konieczny do zatrzymania petli
    }

    double wynik = (((x0 + xN + wartosc) * h) / 2); //<----------------|

    double czas = GetCounter(); // zakonczenie zliczania czasu pracy dla algorytmu

    cout << "Przyblizone rozwiazanie metoda Trapezow" << endl;
    cout << "Wynik: " << wynik << endl;
    cout << "Czas pracy algorytmu: " << czas << " ms." << endl << endl;
    cout << "******************************************************" << endl << endl;
}

void simpson(double a, double b, int n){

    StartCounter(); // rozpoczecie zliczania czasu pracy dla algorytmu

    int x0 = wzorFunkcji(a); //wartosc jaka przyjmuje funkcja w poczatkowym punkcie przedzialu
    int xN = wzorFunkcji(b); //wartosc jaka przyjmuje funkcja w koncowym punkcie przedzialu
    double h = (double)(b-a)/(n*2); //obliczenie "wyosoksci" przedzialu
    double wartosc = 0; // zmienna konieczna do przechowywania wartosci
    double stop = a+h; //zapoczatkowanie warunku koniecznego do zatrzymania sie petli while
    int i = 0; //zmienna pomocnicza
    while(stop < b){
        i++;
        if (i%2 != 0) // warunek sprawdzajacy czy i jest nieparzyste, tylko nieparzyste elementy tabelki sa mnozone przez 4 (pierwsza wartosc liczona jest od 0).
            {
                wartosc += 4 * wzorFunkcji(a + i*h);
            }
        else // mno¿one elementy przez dwa gdy okazuje sie, ze pierwszy warunek jest flaszywy
            {
                wartosc += 2 * wzorFunkcji(a + i*h);
            }

        stop += h; //warunek konieczny do zatrzymania petli
    }
    double wynik = ((wartosc + x0 + xN) * h) / 3; // obliczenie i wyswietlenie wyniku

    double czas = GetCounter(); // zakonczenie zliczania czasu pracy dla algorytmu

    cout << "Przyblizone rozwiazanie metoda Simpsona" << endl;
    cout << "Wynik: " << wynik << endl;
    cout << "Czas pracy algorytmu: " << czas << " ms." << endl << endl;
    cout << "******************************************************" << endl << endl;
}

void newton(double a, double b, int n){

    StartCounter(); // rozpoczecie zliczania czasu pracy dla algorytmu

    int x0 = wzorFunkcji(a); //wartosc jaka przyjmuje funkcja w poczatkowym punkcie przedzialu
    int xN = wzorFunkcji(b); //wartosc jaka przyjmuje funkcja w koncowym punkcie przedzialu
    double h = (double)(b-a)/(n*3); //obliczenie "wyosoksci" przedzialu
    double wartosc = 0; // zmienna konieczna do przechowywania wartosci
    double stop = a+h; //zapoczatkowanie warunku koniecznego do zatrzymania sie petli while
    int i = 0; //zmienna pomocnicza
    while(stop < b){
        i++;
        if (i%3 != 0) // warunek sprawdzajacy czy i modulo 3 zostawia reszte, tylko wyrazy zostawiaj¹ce reszte z dzielenia sa mno¿one przez 3
            {
                wartosc += 3 * wzorFunkcji(a + i*h);
            }
        else // mno¿one elementy przez dwa gdy okazuje sie, ze pierwszy warunek jest flaszywy
            {
                wartosc += 2 * wzorFunkcji(a + i*h);
            }
        stop += h; //warunek konieczny do zatrzymania petli
    }
    double wynik = ((3 * h * (x0 + wartosc + xN)) / 8); // obliczenie i wyswietlenie wyniku

    double czas = GetCounter(); // zakonczenie zliczania czasu pracy dla algorytmu

    cout << "Przyblizone rozwiazanie metoda 3/8 Newtona" << endl;
    cout << "Wynik: " << wynik << endl;
    cout << "Czas pracy algorytmu: " << czas << " ms." << endl << endl;
    cout << "******************************************************" << endl << endl;
}

void monteCarlo(double a, double b, int n){

    StartCounter(); // rozpoczecie zliczania czasu pracy dla algorytmu

    double wartosc = 0; // zmienna konieczna do przechowywania wartosci
    double h = b-a; //obliczenie wysokosci przedzialu

    for(int i = 1; i <= n; i++){
        wartosc += wzorFunkcji(a + ((double)rand() / (double)(RAND_MAX + 1) * h)); //generujemy liczbe pseudolosowa, ktora nalezy do przedzialu, nastepnie obliczamy wartosc funkcji w tym przedziale. Otrzymany wynik dodajamey do pozostalych wartosci.
    }
    double wynik = ((h * wartosc) / n); // obliczenie i wyswietlenie wyniku

    double czas = GetCounter(); // zakonczenie zliczania czasu pracy dla algorytmu

    cout << "Przyblizone rozwiazanie metoda Monte Carlo" << endl;
    cout << "Wynik: " << wynik << endl;
    cout << "Czas pracy algorytmu: " << czas << " ms." << endl << endl;
    cout << "******************************************************" << endl << endl;
}

void crudeMonteCarlo(double a, double b, int n){

    StartCounter(); // rozpoczecie zliczania czasu pracy dla algorytmu

    double wartosc = 0; // zmienna konieczna do przechowywania wartosci
    double h = b-a; //obliczenie wysokosci przedzialu
    for(int i = 1; i < n; i++){
        wartosc += wzorFunkcji(a + (double)rand() / (double)(RAND_MAX) * h); //losowanie liczby z aprzedzialu <a,b> oraz obliczenie w danym punkcie wartosci
    }
    double wynik = ((wartosc * h) / n); // obliczenie i wyswietlenie wyniku

    double czas = GetCounter(); // zakonczenie zliczania czasu pracy dla algorytmu

    cout << "Przyblizone rozwiazanie metoda Crude Monte Carlo" << endl;
    cout << "Wynik: " << wynik << endl;
    cout << "Czas pracy algorytmu: " << czas << " ms." << endl << endl;
    cout << "******************************************************" << endl << endl;
}

void metodaAkceptacjiOdrzucen(double a, double b, double d, int n){

    StartCounter(); // rozpoczecie zliczania czasu pracy dla algorytmu

    double wartosc = 0; // zmienna konieczna do przechowywania wartosci
    double h = b-a; //obliczenie wysokosci przedzialu
    int k = 0;
    double x, y;

    for(int i = 1; i < n; i++){
        x = (a + (double)rand() / (double)(RAND_MAX) * h);
        y = (a + (double)rand() / (double)(RAND_MAX) * d);

        if(y < wzorFunkcji(x)) k++;
    }
    wartosc = (double)((k * h * d) / n);

    double czas = GetCounter(); // zakonczenie zliczania czasu pracy dla algorytmu

    cout << "Przyblizone rozwiazanie metoda Akceptacji - Odrzucen " << endl;
    cout << "Wynik: " << wartosc << endl;
    cout << "Czas pracy algorytmu: " << czas << " ms." << endl << endl;
    cout << "******************************************************" << endl << endl;
}
