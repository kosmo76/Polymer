#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <vector>
#include <string>

//Klasa abstrakcyjna dostarczajaca wspolnej funkcjonalnosci
class Translation
{
public:
    //konstruktor pobiera wymiarowosc
    Translation(int dim);
    //zwraca wektor translacji o indeksie idx
    std::vector <int> get_translation(int idx);
    int get_dim();
    //zwraca liczbe wektorow translacji
    int get_nvectors();
    //czesc transacji moze sie nie nadawac do tworzenia konfiguracji startowej, dlatego 
    //kazda klasa MUSI zwracac translacje pozwalajace na ulozenie poprawnej konfiguracji
    virtual std::vector < std::vector <int> > get_initial_translations() = 0;
    
protected:
    //metoda sluzaca do zainicjowania - wywolywana w konstruktorze
    virtual void initialize();
    std::vector < std::vector <int> > trans_vect;
    int dim;
    int nvectors;
};

//KLasa reprezentujaca siec kadratowa z translacjami prawo, lewo, gora, dol
class NearestNeighbour : public Translation
{
public:
    NearestNeighbour(int dim);
    std::vector < std::vector <int> > get_initial_translations();
    
protected:
    void initialize();
    
};

//Klasa reprezentujaca siec kwadratowa z translacjami lewo, prawo, gora, dol, lewo gora, lewo dol, prawo gora, prawo dol
class SecondNearestNeighbour : public Translation
{
public:
    SecondNearestNeighbour(int dim);
    std::vector < std::vector <int> > get_initial_translations();
    
    
protected:
    void initialize();
    
};
#endif
