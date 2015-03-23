#ifndef POLYMER_H
#define POLYMER_H
#include <vector>
#include <string>


//! Klasa reprezentująca polimer.
/*! 
 * Podstawowa klasa reprezentujący pojedynczy łańcuch polimerowy. Konfiguracja polimera jest zdefiniowana poprzez wektory
 * położeń poszczególnych reptonów tworzących łańcuch. Ograniczenie na położenia reptonów polega tylko na zachowaniu ciągłość łańcucha
 * czyli,odległość między sąsiadującymi reptonami musi być 0 lub 1. Zmiana konfiguracji łańcucha polimerowego polega na translacji 
 * wybranego reptonu. Przed wykonaniem translacji, metody sprawdzają czy dana translacja nie powoduje złamania warunku ciągłości łańcucha.
 * 
 * Każda operacja powodująca zmianę konfiguracji, automatycznie pociąga za sobą odpowiednie przeliczenie wektorów reprezentujących linki,
 * ale tylko tych, które sąsiadują z reptonem, który zmienił położenie. Wyjątkiem jest metoda Polymer::set_repton_position. 
 * Metoda ta pozwala na dowolne ułożenie reptonów, bez wzgędu na ich wzajemne odległości -wykorzystywana może być np. do początkowej 
 * konfiguracji położeń z konfiguracji skadającej się z samych linków typu slack.
 * 
 * \todo Można się zastanowić nad jakimś ugólnienem warunku ciągłości łańcucha
 * \todo Przydałoby się napisać jakieś uiwersalne testy sprawdzające klasę i jej metody
 * \todo AKtualnie klasa obsługuje tylko 1 i 2 wymiary. Możnaby rozbudować do 3D
 * 
 */
class Polymer
{
public:
    
    //Tworzenie obiektu 
    
    //! Polimer z ustawionymi reptonami na zerze - same slacki.
    /*!
     * 
     * Pozycje reptonów zapisane są w atrybucie Polymer::positions
     * Po utworzeniu obiektu automatycznie wyliczane są linki polimeru,a ich wektory są trzymane w atrybucie Polymer::links.
     * Dodatkowo tworzony jest wektor Polymer::tmp o wymiarowosći takiej jak podana w konstruktorze. Wektor tworzony jest po to, 
     * aby w trakcie obliczeń związanych z wektorami położeń lub linków nie deklarować (a co za tym idzie rezerwowac pamięci) 
     * za każdym razem nowych wektorów.
     * 
     * \param nreptons liczba reptonów
     * \param dim wymiarowość układu
     */
    
    Polymer(int nreptons, int dim);
    
    //! Polimer stworzony na podstawie przesłanej reprezentacji .
    /*!
     * Oznaczenia linków stosowane w reprezentacji (przykłady dla 2D wraz z pozycjami reptonów):
     * 
     * \b s - slack  - wektor z samymi zerowymi współrzędnymi  - dwa reptony w jednej komórce (np.w 2D  <0,0>, <0,0> )\n
     * \b u - up - wektor jednostkowy zgodny z kierunkiem osi y ( <0,0>, <0,1> )\n
     * \b r - right  - wektor jednostkowy zgodny z kierunkiem osi x ( <0,0>, <1,0> ) \n
     * \b d - down  - wektor jednostkowy, przeciwny do kierunku osi y ( <0,0>, <0,-1> )\n
     * \b l - left  - wektor jednostkowy, przeciwny do kierunko osi x ( <0,0>, <-1,0> )\n
     * 
     * Pozycje reptonów zapisane są w atrybucie Polymer::positions
     * Po utworzeniu obiektu automatycznie wyliczane są linki polimeru,a ich wektory są trzymane w atrybucie Polymer::links.
     * Dodatkowo tworzony jest wektor Polymer::tmp o wymiarowosći takiej jak podana w konstruktorze. Wektor tworzony jest po to, 
     * aby w trakcie obliczeń związanych z wektorami położeń lub linków nie deklarować (a co za tym idzie rezerwowac pamięci) 
     * za każdym razem nowych wektorów.
     * 
     * \param repr aktualna konfiuracja linków w postaci stringu
     * \param dim wymiarowość układu
     */
    
    Polymer(std::string repr, int dim);
    
    //! Metoda sprawdzająca warunek ciągłości łańcucha
    /*!
     * Metoda oblicza odległości między kolejnymi reptonami tworzącymi łańcuch. Jeżli odległość jest większa od 1, metoda 
     * zwaraca 0 sygnalizując niepoprawną konfigurację. W przypadku gdy wszystkie odległości między sąsiadującymi reptonami są 
     * poprawne, metoda zwraca wartość 1
     * \return 1 lub 0 w zależności od spełnienia warunku
     */
    int check_integrity();
    
    //! Metoda zwraca informację o wymiarowości układu.
    /*!
     * Informacja o wymiarowosci ukłądu jest podawana w momencie tworzenia obiektu klasy i zapisywana jest w zmiennej klasy Polymer::dim.
     * Metoda zwraca wartość tej zmiennej, a nie rozmiar wektora opisującego położenie reptonu.
     * 
     * \return Liczba reprezentujący wymiarowośc układu (wartość zmienne Polymer::dim)
     */
    int get_dim();
    
    //! Metoda zwraca informację o ilości reptonów tworzących łańcuchu.
    /*!
     * Informacja o ilości reptonów jest podawana w momencie tworzenia obiektu klasy i zapisywana jest w zmiennej klasy Polymer::nreptons.
     * Metoda zwraca wartość tej zmiennej, a nie rozmiar wektora trzymającego wektory położeń reptonów.
     * 
     * \return Liczba reprezentujący wymiarowośc układu (wartość zmienne Polymer::nreptons)
     */
    int get_nreptons();
    
    //! Metoda zwraca informację o ilości linków występujących w łąńcuchu.
    /*!
     * Ilośc linków (czyli wektorów łączących sąsiadujące reptony) obliczana jest jako ilość reptonów -1.
     * 
     * \return Liczba linków
     */
    int get_nlinks();
    
    //! Metoda zwraca informacje o wektorze pozycji wskazanego reptonu.
    /*!
     * W przypadku podania błędnego indeksu reptonu zostanie wyrzucony wyjątek z biblioteki STL: out_of_range exception
     * 
     * \param idx - numer reptonu liczony od zera
     * 
     * \return wskaźnik do stałego wektora pozycji
     */
    const std::vector<int> * get_repton_position(int idx);
    
    //! Metoda zwraca informacje o wektorach pozycji reptonów tworzących łańcuch polimerowy
    /*!
     * 
     * \return wskaźnik do stałego wektora pozycji
     * 
     */
    const std::vector < std::vector <int> > * get_reptons_positions();
    
    //! Metoda zwraca informacje o wektorze podanego linku 
    /*!
     * 
     * \return wskaźnik do stałego wektora linku
     * 
     */
    const std::vector<int> * get_link_vector(int link_number);
    
    //! Metoda aktualizuje wektor linków połączonych z wskazanym reptonem
    /*!
     * 
     * Translacja pojedynczego reptonu może zmienić stan dwóch najbliżych (i tylko maksymalnie dwóch najbliższych)
     * linków związanych z tym reptonem.W przypadku podania błednego indeksu linku, zostaje wyrzucony wyjątek 
     * z biblioteki STL: out_of_range exception. Metoda ta automatycznie jest wywoływana zawsze po translacji 
     * reptonu prowadzącej do powstania nowej konfiguracji. 
     * 
     * \warning Metoda ta nie jest wywoływana jeśli używana jest metoda Polymer:set_repton_position, która nie zapewnia ciągłości
     * łańcucha, a co za tym idzie - może prowadzić do konfiguracji, dla których nie wystepują zdefiniowane linki.
     * 
     * \param link_number numer linku
     * 
     * \return wskaźnik do stałego wektora linku
     * 
     */
    void update_links(int repton_idx);
    
    //! Metoda obliczająca wszystkie wektory linków dla aktualnej konfiguracji łańcucha polimerowego.
    /*!
     * 
     * Metoda oblicza wszystkie wektory linków dla aktualnej konfiguracji polimeru. Metoda ta jest zawsze wywoływana po stworzeniu polimeru.
     * W wyniku wywołania metody, wektory linków zostają zapisane w Polymer::links. Obiekt klasy vector, który reprezentuje wektory linków, 
     * jest podstawowywm źródłęm informacji dla innych metod zwracających dane dotyczące linków.
     * 
     */
    void calculate_links();
    
    //! Metoda zwracająca informację o wektorach wszytskich linków aktualnej konfiguracji łańcucha.
    /*!
     * 
     * Metoda zwraca wskaźnik do stałego obiektu Polymer::links. Obiekt ten zawiera wektory wszystkich linków 
     * aktualnej konfiguracji łancucha polimerowego.
     * 
     * Jeżli wektory linków są nieaktualne (np. użyto metody Polymer::set_repton_position), należy najpier wywołać metodę
     * Polymer::calculate_links
     * 
     * \return wskaźk do stałego obiektu trzmającego wektory wszytskich linków
     * 
     */
    const std::vector< std::vector <int> > * get_links_vectors();
    
    //! Metoda zwracająca symbol wskazanego linku.
    /*!
     * \param link_number numer linku
     * \return symbol wskazanego linku
     * 
     */
    char get_link_symbol(int link_number);
    
    //! Metoda zwracająca reprezentacje linków aktualnej konfiguracji .
    /*!
     * 
     * \return symbol wskazanego linku
     * 
     */
    std::string get_representation();
    
    //! Metoda sprawdzająca, czy podana translacja wykonana w wskaznym reptonie jest dozwolona.
    /*!
     * 
     * Metoda oblicza nową pozycję wskazanego reptonu uzyskaną w  wyniku zastosowania podanego wektora translacji. 
     * Następnie obliczane są dwa najbliższe linki związane z przesuwanym reptonem. Jeżli długość tych linków jest większa od 1
     * to oznacza, że translac ne jest dozowlona ponieważ prowadzi do rozerwania łańcucha.
     * 
     * \param idx numer reptonu, który zostanie przesunięty
     * \param trans wektor translacji
     * \return 1 - translacja dozwolona, 0 - translacja niedozwolona
     * 
     */
    int check_translation(int idx, std::vector<int> const &trans);
    
    //! Metoda zwracająca nowy polimer powstały w wyniku translacji.
    /*!
     * Metoda zwraca nowy obiekt polimera powstaly przez przesuniecie jednego reptonu o zadaną translację.
     * Jeżeli translacja jest niedozwolona (prowadzi do rozerwania polimeru) to zwracany jest "pusty" polimer, to znaczy polimer, 
     * który składa się z zerowej liczby reptonów. W przypadku zwrócenia poprawnego polimera, automatycznie są w nim obliczone 
     * aktualne wektory linków.
     * 
     * Obiekt z którego powstał nowy polimer pozostaje niezmieniony.
     * 
     * \todo A może lepiej jednak zrobić to na jakiś wyjątkach zamiast zwracać "zerowy" polimer ?
     * 
     * \param idx indeks reptonu podlegającego translacji
     * \param trans wektor translacji
     * \return owy obiket klasy Polymer
     * 
     */
    Polymer get_new_by_translation(int idx, std::vector<int> const &trans);
    
    //! Metoda dokonująca przejścia do nowej konfiguracji poprzez translacje reptonu.
    /*!
     * Metoda dokonuje translacji zadanego reptonu o zadany wektor translacji.
     * Jeżeli translacja jest niepoprawna (zerwanie linku) konfiguracja
     * pozostaje bez zmian, a metoda zwraca wartosc 0, w przeciwnym przypadku łancuch przechodzi do nowej konfiguracji, 
     * a metoda zwraca wartość 1.
     * 
     * Metoda ta powoduje automatyczne odświeżenie informacji o wektorach linków.
     * 
     * \param idx indeks reptonu
     * \param trans wektor translacji
     * \return 0 - translacja nie powiodła się, 1 - translacja powiodła się
     * 
     */
    int translate_repton(int idx, std::vector<int> const &trans);
    
    //! Metoda zwraca następny index reptonu lub -1 jeśli koniec
    //! \param idx index reptonu
    //! \return indeks kolejnego reptonu, lub -1 jeśli wskazany był ostatnim
    int get_next_idx(int idx);
    
    //! Metoda zwraca poprzedni index reptonu lub -1 jeśli brak
    //! \param idx index reptonu
    //! \return indeks poprzedniego reptonu, lub -1 jeśli wskazany był pierwszym (o indeksie 0)
    int get_prev_idx(int idx);
  
    //! Metoda zwraca współrzędne środka masy polimera
    //! \return wektor współrzędnych środka masy
    std::vector <double> get_cms_coord();
    
    //! Metoda ustawiająca aktualną konfigurację zgodnie z podaną reprezentacją
    /*!
     * Metoda ustawiająca aktualną konfigurację łańcucha polimerowego zgdnie z podaną reprezentacją linków.
     * Metoda ta nie zmienia wymiarowości układu, która została ustawione w konstruktorze.
     * \todo chyba powinno byc prywatne, bo mozna walnąc bug-a z tą wymiarowością
     * 
     * \param repr reprezentacja linków
     */
    void set_from_representation(std::string repr);
  
    //! Metoda pozwlająca na dowolne ustawienie wskazanego reptonu.
    /*!
     * 
     * Metoda pozwala na ustawienie dowolnych współrzędnych wskazanemu reptonowi. W związku z tym, że ustawienie może być 
     * dowolne, metoda ta nie sprawdza automatycznie warunku ciągłości łańcucha. Głowne założenie tej metody to wykorzystanie jej
     * do ustawienia wybranej konfiguracji z innej poprzez przestawienie wieleu reptonów. Takie przestawienia powodują chwilowe 
     * rozerwania łańcucha, aż do momentu przestawienia kolejnego reptonu.
     * 
     * \param idx indeks reptonu
     * \param pos pozycja na którą nalezy ustawić wskazny repton
     */
    void set_repton_position(int idx, std::vector<int> const &pos);
    
    //! Metoda ustawiająca reptony wpołożeniach zgodnych z połozeniamu reptonów we wskazanym łańcuchu polimerowym.
    /*!
     * 
     * Metoda pozwala na przekopiowanie pozycji reptonów z innego łańcucha polimerowego - o tej amej długości i wymiarowości.
     * Metoda automatycznie również oblicza nowe wektroy linków
     * 
     * \param p obiekt klasy polimer, którego pozycje reptonów chcemy przekopiować
     * \return  0 - nie udało się przekopiować, 1 - przekopiowano.
     */
    int copy_data(Polymer &p);
    
    //! Metoda ustawiająca łańcuch polimerowy na losowej konfiguracji
    /*!
     * Metoda ustawia łańcuch polimerowy na jednej z mozliwych, wybranych  losowych konfiguracji
     * w zależności od wymiarowości układu
     */
    void set_randomly();
   
private:
    int dim;    //! Wymiarowość systemu
    int nreptons; //! Ilośc reptonów tworzących łańcuch
    
    
    std::vector < std::vector <int> > positions; //! Wektor trzymający pozycje reptonów.
    std::vector <int> tmp; //! wektor pomocniczy, automatycznie ustawiany zgodnie z wymiarowością układu i wypełniany zerami
    std::vector < std::vector <int> > links; //!wektor reprezentujący wektory linków
    

};

#endif