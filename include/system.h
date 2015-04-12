#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <string>


class Translation;
class Dynamic;
class Polymer;

//! Klasa reprezentująca abstrakcyjny model symulacji jednego polimeru.
/*! 
 * Głównym zadaniem jest uwspólnienie interfejsu dla konkretnych
 * modeli systemów i symulacji bazujących na tej klasie. W obecnej chwili
 * modele będą bazować na prostym KMC i symulacji jednego polimeru.
 */

class SimulationSystem
{
  public:
      SimulationSystem(int nreptons, Translation *trans, Dynamic * model);
      SimulationSystem(std::string representation, Translation *trans, Dynamic * model);
    
      Polymer *polymer;
      Translation *translation;
      Dynamic *model;

      //zwroc kod przejscia z macierzy przejsc
      int get_transition_type(int repton_id, int trans_id);
      
      //zwroc kopie calej macierzy przejsc
      std::vector < std::vector <int> > get_matrix();
      
      //ruch reptonu o dana translacje + update macierzy przejsc
      void move_repton(int repton_idx, int trans_idx);
      
      //metoda zwracajaca vektor w postaci (numer_rep, numer_trans) 
      virtual std::vector <int>  choose_transition() = 0;
      
  protected:
      
      void initialize_polymer();
      void initialize_matrix();
      void update_matrix(int repton_idx, int range=1);
      
      std::vector < std::vector <int> > matrix;
};

class TestSimulationSystem: public SimulationSystem
{
public:
    TestSimulationSystem(int nreptons, Translation *trans, Dynamic * model);
    TestSimulationSystem(std::string rep, Translation *trans, Dynamic * model);
    std::vector <int>  choose_transition();
    
public:
    std::vector <std::vector <int> > transitions;
    std::vector <double> rates_cum_sum;    
    
    //lista w postaci par (repton_id, trans_id) dozwolonych ruchów - potrzebna do losowania przejscia
    void prepare_transision_list();
    
};



class KMCSimulationSystem: public SimulationSystem
{
public:
    KMCSimulationSystem(int nreptons, Translation *trans, Dynamic * model);
    KMCSimulationSystem(std::string rep, Translation *trans, Dynamic * model);
    std::vector <int>  choose_transition();
    double get_mc_time();
    
    virtual double get_rate_modifier(int repton_idx, int trans_idx);
    //TODO do wywalenia to ponizej
    std::vector <double> get_rates_cum_sum();
    
    int poszedl;
    double rate;
    //TODO CHyba prywatne
public:
    std::vector <std::vector <int> > transitions;
    std::vector <double> rates_cum_sum;
    void prepare_transision_list();
    
};

class KMCInFieldSimulationSystem: public KMCSimulationSystem
{
public:
    KMCInFieldSimulationSystem(int nreptons, Translation *trans, Dynamic * model, std::vector <double> eps);
    KMCInFieldSimulationSystem(std::string rep, Translation *trans, Dynamic * model, std::vector <double> eps);
    double get_rate_modifier(int repton_idx, int trans_idx);
    
public:
    std::vector <double> epsilon;
};
#endif

