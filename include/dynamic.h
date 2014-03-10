/************************************************
 * Klasa reprezentująca model dynamiki polimeru
 * Jej podstawowym działaniem jest sprawdzenie
 * czy dwie konfiguracje polimera moga zostac 
 * uzyskane jedna z drugiej zgodnie z zaplanowanymi 
 * regulami
 * TODO wymyslilem, ze powinno zwracac "kod" przejscia
 * np. 0 - zabronione, 1 - reptation,  2- hernia
 * 3 - crosssing barrier etc.
 * Wydaje mi sie, ze Rouse dynamics jest najbardziej 
 * oglne reszt to dodatkowe restrykcje np:
 * h=c=0 - daje rouse
 * mozna tez od raz dodac scisliwosc C = n-1 = ogolne
 * mzna tez od razu pomyslec, ze nie moze byc wiecej niz 
 * o jednych wspolrzednych, ale nie wiem jeszcze jak
 * albo jednak zrobci trzy odzielne klasyz tym samym kodem ?
 * **************************************************/

#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <vector>
#include <cmath>
#include <utility>

#include "polimer.h"
#include "translation.h"


class Dynamic
{
public:
    
    Dynamic();
    //metoda zwracajaca na podstawie podanych vewktorow polozen reptonow w dwoch stanach kod przejscia z stanu start do stanu end
    virtual int get_transition_type( std::vector < std::vector <int> > &start, std::vector < std::vector <int> > &end) = 0;
    virtual int get_transition_type( Polymer &p1, Polymer &p2) = 0;
    
    
    //metoda zwracajaca wartosc przejscia okreslonego przez podany kod
    virtual double get_transition_rate(int code) = 0;
    
    //funkcja umozliwiajaca ustawienie parametrow modelu - kolejnosc i znaczenie to logika programowalna w konkretnych klasach
    void set_rates( std::vector <double> parameters);
    
protected:
    std::vector <double> rates;
    virtual  int check_end_link(std::vector <int> &old_link, std::vector<int> &new_link) = 0;
    virtual int get_transition_type_by_links(std::vector < std::vector <int> > &start_links, std::vector < std::vector <int> > &end_links)=0;
    
};

class RouseDynamic : public Dynamic
{
public:
     
    //stale definujace mozliwe rodzaje przejsc
    static const int FORBIDEN = 0;
    static const int REPTATION = 1;
    static const int HERNIA = 2;
    static const int CROSSING = 3;
    
    
    RouseDynamic(double rept, double hernia, double cross);
    
    int get_transition_type( std::vector < std::vector <int> > &start, std::vector < std::vector <int> > &end);
    int get_transition_type( Polymer &p1, Polymer &p2);
    double get_transition_rate(int code);
    
    double get_reptation_rate();
    double get_hernia_rate();
    double get_crossing_rate();
    
    void set_reptation_rate(double &);
    void set_hernia_rate(double &);
    void set_crossing_rate(double &);
    

private:
    int check_end_link(std::vector <int> &old_link, std::vector<int> &new_link);
    
    int get_transition_type_by_links(std::vector < std::vector <int> > &start_links, std::vector < std::vector <int> > &end_links);
    
    
};
#endif
