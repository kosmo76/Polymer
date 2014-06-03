/*********************************************
 * Kilka przydatnych funkcji wykorzystywanych
 * w programie do symulacji polimerow
 ********************************************/

/*! 
 * Jakis sobie opis pliku
 */
#ifndef TOOLS_H
#define TOOLS_H

#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <iostream>

/*****************************************
 * RANDOM NUMBERS
 *****************************************/

//TODO przydaloby sie zrobic to na jakims Mersen-Twister abo cos pdobnego
double frand();

/******************************************************
 * Funkcje pomocnicze przy obliczeniach na std::vector
 * W przypadku niezgodności rozmiarów wektora zostanie
 * wyrzucony wyjatek const char *
 * ****************************************************/

//czy dwa wektory są równe w sensie zawartości
int is_equal(const std::vector <int>  &w, const std::vector < int> &v);

//czy dwa wektory mają przeciwne zwroty
int is_opposite(const std::vector <int>  &w, const std::vector < int> &v);

//zwróć kwadratową odległość między punktami wskazywanymi przez wektor w i v
double get_square_distance( const std::vector <int>  &w, const std::vector < int> &v );

//zwróć odległość między punktami wskazanymi poprzez wektory w i v
double get_distance(const std::vector <int>  &w, const std::vector < int> &v);

//iloczyn skalarny dwóch wektorów

double dot(const std::vector <int>  &w, const std::vector <int> &v);


//dodaj dwa wektory i wynik zapisz w trzecim przesłanym przez referencje
void add( const std::vector <int>  &w, const std::vector <int> &v, std::vector <int> &result);
//odejmnij dwa wektory w - v i wynik zapisz w trezcim przesłanym przez referencje
void diff(const std::vector <int>  &w, const std::vector <int> &v, std::vector <int> &result);

#endif
