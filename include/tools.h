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

double frand();

/******************************************************
 * Funkcje pomocnicze przy obliczeniach na std::vector
 * ****************************************************/

int is_equal(std::vector <int>  &w, std::vector < int> &v);
int is_opposite(std::vector <int>  &w, std::vector < int> &v);
double get_square_distance( std::vector <int>  &w, std::vector < int> &v );
double get_distance(std::vector <int>  &w, std::vector < int> &v);
std::vector<int> add(std::vector <int>  &w, std::vector <int> &v);
std::vector<int> diff(std::vector <int>  &w, std::vector <int> &v);
double dot(std::vector <int>  &w, std::vector <int> &v);

/*****************************************
 * print vectora dla debuga
 * powinien byc template, ale nie pamietalem 
 * jak to lecialo :-)
 * **************************************/
void show_vector(std::vector <double>  &w, std::string str);
void show_vector(std::vector <int>  &w, std::string str);

#endif
