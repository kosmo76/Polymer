#ifndef ANALYSER_H
#define ANALYSER_H

#include <vector>
#include <string>

#include "polymer.h"
#include "system.h"

/************************************
 * klasy bazowe do dziedzczenia 
 * na razie taki zarys idei
 * *********************************/

class Analyser
{
public:
    //czasami analizatory beda potrzebowaly roznych danych, wiec beda przesylane dodatkowe parametry w vektorze double
    //TODO - moze moznaby to jakos sensowniej ?
    
    virtual void analyse(long step, Polymer *old_polymer, Polymer * new_polymer, const std::vector <double> data = std::vector<double>());
    Polymer * actual_polymer;
    Polymer * old_polymer;
    
};


//Przykladowa klasa analizatora 
// zliczajaca prawdopodobiensta stanow dla ukladu 2D i 3 reptony
class StateProbability: public Analyser
{
public:
  StateProbability();
  void analyse(long step, Polymer *old_polymer, Polymer * new_polymer, const std::vector <double> data = std::vector<double>());
  void clear_histogram();
  
  static const int SIZE = 125;
  long counter;
  std::string state;
  int hist[SIZE];
  
  static const std::string states[SIZE];
};

#endif