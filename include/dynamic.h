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

#include "polymer.h"
#include "translation.h"

//! Klasa reprezentująca abstrakcyjny model dynamiki polimeru.
/*! 
 * Głównym zadaniem jest uwspólnienie interfejsu dla konkretnych
 * modeli dynamiki bazujących na tej klasie.
 * 
 * Założenie jest takie, że każde przejście z jedenj konfiguracji do drugiej 
 * posiada określony "kod" - typ przejścia i związany z nim "rate"
 */

class Dynamic
{
public:
    //! Konstruktor 
    /*!
     * \param dim wymiarowosći układu
     */
    Dynamic(int dim);
    
    //! Metoda zwracajaca na podstawie podanych dwóch konfiguracji polimerow typ przejścia
    /*!
     * \param p1 obiekt polimera reprezentujący konfigurację początkową
     * \param p2 obiket polimera reprezentujący konfigurację końcową
     * 
     * \return typ przejścia
     */
    virtual int get_transition_type( Polymer &p1, Polymer &p2) = 0;
    
    
    //! Metoda zwracajaca rate przejścia podanego jako typ wywołania
    /*!
     * \param code typ przejścia między dwoma konfiguracjami
     * 
     * \return rate prejścia
     */
    virtual double get_transition_rate(int code) = 0;
    
    //! Metoda pozwlająca ustawić parametry modelu - programowana w klasach potomnych
    /*!
     * \param parameters - paramtery modelu
     * 
     * \todo Zastanowic sie czy potrzebna
     */
    void set_rates( std::vector <double> parameters);
    
protected:
    
    std::vector <double> rates; //!wektor z rate-ami dla danego modelu
    int dim;    //!wymiarowość ukłądu
    std::vector <int> slack; //! wektor definiujący slacka w danej wymiarowości
    
    //!metoda wirtualna sprawdzająca końce łańcucha przy przejściu
    /*!
     * \param old_link wektor linka końcowego (początkowego) dla początkowej konfiguracji
     * \param new_link wektor linka końcowego (początkowego) dla końcowej konfiguracji
     * 
     * \return typ przejścia
     */
    virtual  int check_end_link(const std::vector <int> &old_link, const std::vector<int> &new_link) = 0; 
    
    //!metoda wirtualna zwracająca typ przejścia z jedenj konfiguracjo do drugiej
    /*!
     * \param start_links wektor zawierający wektory linków początkowej konfiguracji
     * \param end_links wektor zawierający wektory linków końcowej konfiguracji
     * 
     * \return typ przejścia
     */
    
    virtual int get_transition_type_by_links(const std::vector < std::vector <int> > &start_links, const std::vector < std::vector <int> > &end_links)=0;
    
};

//! Klasa reprezentująca model dynamiki oparty na reptation + hernia + crossing barrier

class RouseDynamic : public Dynamic
{
public:
     
    //stale definujace mozliwe rodzaje przejsc
    static const int FORBIDEN = 0; //! kod przejścia zabronionego
    static const int REPTATION = 1; //! kod przejścia typu reptation
    static const int HERNIA = 2; //! kod przejścia typu hernia kreacja/anihilacja
    static const int CROSSING = 3; //! kod przejścia typu crossing barrier
    static const int HERNIA_MIGRATION = 4; //! kod przejścia typu migracja herni
    
    //! Model opisujący dynamikę typu Reptation jak również Rouse w zalezności od parametrów
    /*!
     * \todo opisać więcej
     * 
     * \param rept rate dla przejścia typu reptation
     * \param hernia rate dla przejścia typu hernia kreacja/anihilacja
     * \param cross rate dla przejścia typu crossing barrier
     * \param hernia_migration rate dla przejścia typu migracja herni
     * \param dim wymiarowość układu
     */
    RouseDynamic(double rept, double hernia, double cross, double hernia_migration, int dim);
    
    //! Metoda zwracajaca na podstawie podanych dwóch konfiguracji polimerow typ przejścia
    /*!
     * \param p1 obiekt polimera reprezentujący konfigurację początkową
     * \param p2 obiket polimera reprezentujący konfigurację końcową
     * 
     * \return typ przejścia
     */
    int get_transition_type( Polymer &p1, Polymer &p2);

     //! Metoda zwracajaca rate przejścia podanego jako typ wywołania
    /*!
     * \param code typ przejścia między dwoma konfiguracjami
     * 
     * \return rate prejścia
     */
    double get_transition_rate(int code);
    
    double get_reptation_rate(); //! zwraca rate dla reptation
    double get_hernia_rate(); //! zwraca rate dla herni
    double get_crossing_rate(); //! zwraca rate dla crossing barrier
    double get_hernia_migration_rate(); //!zwraca rate dla migracji herni
    
    void set_reptation_rate(double &); //!ustawia rate dla reptation
    void set_hernia_rate(double &); //! ustawia rate dla herni
    void set_crossing_rate(double &); //! ustawia rate dla crossing barrier
    void set_hernia_migration_rate(double &); //! ustawia rate dla migracji herni
    

private:
    //!metoda wirtualna sprawdzająca końce łańcucha przy przejściu
    /*!
     * \param old_link wektor linka końcowego (początkowego) dla początkowej konfiguracji
     * \param new_link wektor linka końcowego (początkowego) dla końcowej konfiguracji
     * 
     * \return typ przejścia
     */
    int check_end_link(const std::vector <int> &old_link, const std::vector<int> &new_link);
    
     
    //!metoda wirtualna zwracająca typ przejścia z jedenj konfiguracjo do drugiej
    /*!
     * \param start_links wektor zawierający wektory linków początkowej konfiguracji
     * \param end_links wektor zawierający wektory linków końcowej konfiguracji
     * 
     * \return typ przejścia
     */
    int get_transition_type_by_links(const std::vector < std::vector <int> > &start_links, const std::vector < std::vector <int> > &end_links);
    
    
};
#endif
