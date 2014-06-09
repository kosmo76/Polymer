#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <vector>
#include <string>

//! Klasa abstrakcyjna definiująca interfejs dla klas reprezentujących translacje
/*! 
 * Zakładamy, że współrzędne wektorów translacji są liczbami całkowitymi
 */
class Translation
{
public:
    
    //! Ustawienie wymiarowości i zainicjowanie obiketu.
    /*!
     * Konstruktor ustawia wymiarowośc układu Translation::dim oraz wywołuje metodę initialize, która
     * w klasie bazowej jest netodą wirtualną
     * 
     * \param dim wymiarowość układu
     */
    Translation(int dim);
    
    //! Metoda zwracająca wektor translacji o podanym indeksie.
    /*!
     * 
     * \param idx indeks vektora translacji
     * \return wskaźnik do stałego wektora translacji (wspólrzędne są liczbami int)
     */
    std::vector <int> get_translation(int idx);
    
    //! Metoda zwracająca wymiarowość.
    /*!
     * \return liczba określająca wymiarowość układu (ilość współrzędnych wektora translacji)
     */
    int get_dim();
    
    //! Metoda zwracająca ilośc wektorów translacji.
    /*!
     * \return liczba określająca ilość wektorów translacji zdefiniowanych w danej klasie
     */
    int get_nvectors();
    
    //! Metoda abstrakcyjna zwracająca wektory translacji, z których można ułożyć poprawną konfigurację polimera
    /*!
     * W związku z warunkiem ciagłości łańcucha polimerowego (czyli odległość między repronami wynosi 0 lub 1) 
     * nie każda translacja jest dozwolona przy tworzenu łańcucha polimerowego - np. <-1, 1>.
     * Metoda ta ma zwrócić wektory translacji, z których można utworzyć łańcuch polimerowy startując z konfiguracji
     * samych slacków - czyli wszystkie reptony w pozycjo <0,0>. 
     * 
     * \return wektor zawierającey wektory translacji
     */
  
    virtual std::vector < std::vector <int> >  get_initial_translations() = 0;
    
protected:
  
    //! Metoda wywoływana z konstruktora i mająca za zadanie zainicjowanie obiektu
    virtual void initialize();
    
    std::vector < std::vector <int> > trans_vect; //! wektor trzymający wektory translacji
    int dim; //! wymiarowosć
    int nvectors;  //! ilosc wektorów translacji
};

//! Klasa definiująca translacje do najbliższych sąsiadów na sieci kwadratowej w 1D i 2D
/*! 
 * Zakładamy, że współrzędne wektorów translacji są liczbami całkowitymi.
 * 
 * W przypadku 1D wektory translacji to <-1>, <1>
 * 
 * W przypadku 2D wektory translacji to <0,1>, <1,0>, <0,-1>, <-1, 0>
 * 
 */
class NearestNeighbour : public Translation
{
public:
    NearestNeighbour(int dim);
     std::vector < std::vector <int> >  get_initial_translations();
    
protected:
    //! Metoda wywoływana z konstruktora i mająca za zadanie zainicjowanie obiektu - ustawienie wektorów translacji
    void initialize();
    
};

//! Klasa definiująca translacje do najbliższych i kolejnych najbliższych sąsiadów na sieci kwadratowej w 1D i 2D
/*! 
 * Zakładamy, że współrzędne wektorów translacji są liczbami całkowitymi.
 * 
 * W przypadku 1D wektory translacji to <-1>, <1>
 * 
 * W przypadku 2D wektory translacji to <0,1>, <1,0>, <0,-1>, <-1, 0>, <1,1>, <1, -1>, <-1, -1> , <-1,1>
 * 
 */
class SecondNearestNeighbour : public Translation
{
public:
    SecondNearestNeighbour(int dim);
    std::vector < std::vector <int> > get_initial_translations();
    
    
protected:
    //! Metoda wywoływana z konstruktora i mająca za zadanie zainicjowanie obiektu - ustawienie wektorów translacji
    void initialize();
    
};
#endif
