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
    //polimer z ustawionymi reptonami na zerze
    Polymer(int nreptons, int dim);
    
    //polimer z ustawionymi reptonami zgodnie z konfiguracja
    //np. udllrdss
    // u - up, d - down, l - left, r - right, s - slack
    Polymer(std::string, int dim);
    
    // sprawdza spojnosc polimeru - zalozone jest ze odleglosc miedzy reptonami to 0 lub 1
    int check_integrity();
    
    //zwroc wymiarowosc ukladu
    int get_dim();
    
    //zwroc ilosc reptonow
    int get_nreptons();
    
    //zwroc ilosc linkow  = nreptons - 1
    int get_nlinks();
    
    /// \brief zwraca wskaznik do wspolrzednych danego reptonu
    std::vector<int> * get_repton_position(int idx);
    
    /// \brief zwaraca wskaznik do położen reptonów
    std::vector < std::vector <int> > * get_reptons_positions();
    
    //zwraca współrzedne wektora linku
    //linki nie sa trzymane w klasie, wiec je liczy i zwaraca wektor
    std::vector<int> get_link_vector(int link_number);
    
    //metoda uaktualnia wektory linkow na lewo i prawo od reptonu 
    void update_links(int repton_idx);
    
    void calculate_links();
    //zwraca wektory linkow polimera
    std::vector< std::vector <int> > get_links_vectors();
    std::vector< std::vector <int> > * get_links_vectors_as_pointer();
    
    //zwraca symbol wskazanego linku 
    char get_link_symbol(int link_number);
    
    //zwraca reprezentacje aktualnej konfiguracji
    std::string get_representation();
    
    //sprawdzamy czy dana translacja jest dozwolona czyli nie rozrywa polimeru - to jest zupelnie bazowe zalozenie
    int check_translation(int idx, std::vector<int> const &trans);
    
    //zwraca nowy obiekt polimera powstaly przez przesuniecie jednego reptonu o zadana translacje
    //jezeli translacja jest niedozwolona to zwracany jest polimer o reptonach = 0
    //raczej dosc kiepskie rozwiazanie, moze lepiej wyjatki ?
    Polymer get_new_by_translation(int idx, std::vector<int> const &trans);
    
    //dokonuje translacji zadanego reptonu o zadany wektor translacji
    //jezeli translacja jest niepoprawna (zerwanie linku) konfiguracja
    //pozostaje bez zmian, a metoda zwraca wartosc 0, w przeciwnym przypadku 1
    int translate_repton(int idx, std::vector<int> const &trans);
    
    //zwraca następny index reptonu lub -1 jesli koniec
    int get_next_idx(int idx);
    
    //zwraca poprzedni numer reptonu lub -1 jesli początek
    int get_prev_idx(int idx);
    
    //zwraca srodek masy polimeru
    std::vector <double> get_cms_coord();
    
    //metoda ustawiajac zdefiniowany polimer zgodnie z podana konfiguracja
    // wymiarowosc jest ustawiona w konstruktorze !
    //TODO chyba powinno byc prywatne
    void set_from_representation(std::string);
  
    //metoda ustawiajaca wspolrzedne danego reptonu
    //TODO aktualnie nie jest sprawdzana poprawnosc nowej pozycji, zeby moza sobie ukldac polimer z samych slackow
    void set_repton_position(int idx, std::vector<int> const &pos);
    
    int copy_data(Polymer &p);
   
private:
    int dim;
    int nreptons;
    
    std::vector < std::vector <int> > positions;
    
    //vector pomocniczy, zeby nie deklarowac dynamicznie pamieci w metodach
    //atomatycznie jest ustawiany na wilkosci dim i wypelnianay zerami w konstruktorze
    std::vector <int> tmp;
    //vector reprezentujacy linki 
    std::vector < std::vector <int> > links;
    

};

#endif