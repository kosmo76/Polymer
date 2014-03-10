#ifndef POLYMER_H
#define POLYMER_H
#include <vector>
#include <string>

/*TODO
 * Aktulanie klasa obsluguje tylko 1 i 2 wymiary
 */

class Polymer
{
public:
    //pusty polimer - zero reptonow - czasami sie przydaje, choc nie jestem przekonany
    Polymer();
    //polimer z ustawionymi reptonami na zerze
    Polymer(int nreptons, int dim);
    //polimer z ustawionymi reptonami zgodnie z konfiguracja
    //np. udllrdss
    // u - up, d - down, l - left, r - right, s - slack
    Polymer(std::string, int dim);
    // sprawdza spojnosc polimeru - zalozone jest ze odleglosc miedzy reptonami to 0 lub 1
    int check_integrity();
    //zwroc wymiarowosc ukladu
    int get_ndim();
    //zwroc ilosc reptonow
    int get_nreptons();
    //zwroc ilosc linkow  = nreptons - 1
    int get_nlinks();
    //zwraca wspolrzedne danego reptonu
    std::vector<int>  get_repton_position(int idx);
    //zwaraca wszystkie położenia reptonów
    std::vector < std::vector <int> > get_reptons_positions();
    //zwraca współrzedne wektora linku
    //linki nie sa trzymane w klasie, wiec je liczy i zwaraca wektor
    std::vector<int> get_link_vector(int link_number);
    //zwraca wektory linkow polimera
    std::vector< std::vector <int> > get_links_vectors();
    //zwraca symbol wskazanego linku 
    char get_link_symbol(int link_number);
    //zwraca reprezentacje aktualnej konfiguracji
    std::string get_representation();
    //zwraca nowy obiekt polimera powstaly przez przesuniecie jednego reptonu o zadana translacje
    //jezeli translacja jest niedozwolona to zwracany jest polimer o reptonach = 0
    //raczej dosc kiepskie rozwiazanie, moze lepiej wyjatki 
    Polymer get_new_by_translation(int idx, std::vector<int> trans);
    //zwraca następny index reptonu lub -1 jesli koniec
    int get_next_idx(int idx);
    //zwraca poprzedni numer reptonu lub -1 jesli początek
    int get_prev_idx(int idx);
    //zwraca srodek masy polimeru
    std::vector <double> get_cms_coord();
    
    //metoda ustawiajac zdefiniowany polimer zgodnie z podana konfiguracja
    // wymiarowosc jest ustawiona w konstruktorze !
    void set_from_representation(std::string);
  
    //metoda ustawiajaca wspolrzedne danego reptonu
    //TODO aktualnie nie jest sprawdzana poprawnosc nowej pozycji, zeby moza sobie ukldac polimer z samych slackow
    void set_repton_position(int idx, std::vector<int> pos);
    
   
private:
    int dim;
    int nreptons;
    
    std::vector < std::vector <int> > positions;
    

};

#endif