/*********************************************
 * Kilka przydatnych funkcji wykorzystywanych
 * w programie do symulacji polimerow
 ********************************************/

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
 * ****************************************************/
int is_equal(std::vector <int>  &w, std::vector < int> &v);
int is_opposite(std::vector <int>  &w, std::vector < int> &v);
double get_square_distance( std::vector <int>  &w, std::vector < int> &v );
double get_distance(std::vector <int>  &w, std::vector < int> &v);

//ze wzgledu na szybkosc(?) wynik jest umieszcany w wektorze wrzuconym przez referencje
void add(std::vector <int>  const &w, std::vector <int> const &v, std::vector <int> &result);
void diff(std::vector <int>  const &w, std::vector <int> const &v, std::vector <int> &result);

double dot(std::vector <int>  &w, std::vector <int> &v);

#endif
