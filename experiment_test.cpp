#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

#include "include/tools.h"
#include "include/polymer.h"
#include "include/translation.h"
#include "include/dynamic.h"
#include "include/system.h"
#include "include/analyser.h"
#include "include/experiment.h"

using namespace std;
  
main()
{
 srand(time(NULL));

 //ustaw parametry symulacji
 long term_steps = 100000;   //termalizacja
 long steps = 40000000;      //dlugosc symulacji po termalizacji
 
 int dim = 2;                //wymiarowosc ukladu
 int nreptons = 3;           //ilosc repotonow
 
 //parametry modelu
 double rate_r = 1.0, rate_h=0.2, rate_c=0.2, rate_m=0.2;
 //rodzaj translacji
 SecondNearestNeighbour trans_obj(dim);
 RouseDynamic rouse(rate_r, rate_h, rate_c, rate_m, dim);
 KMCSimulationSystem s1("sss", &trans_obj, &rouse);

 //obiekt reprezentujacy pojedynczy eksperymnet
 Experiment ex1(&s1, term_steps, steps);

 //jakis przykladowy analizator wpinany do experymenty - tutaj prawdopodobienstwa stanow dla 2D - 3 repton
 StateProbability *analyser = new StateProbability();

 ex1.analysers.push_back(analyser);

 //cala symulacja
 ex1.simulate();

 //wyniki pobrane z analizatora i wysietlone na ekranie
 for(int i=0; i<analyser->SIZE; i++)
 {
   cout << analyser->states[i] <<"   "<< analyser->hist[i]/double(analyser->counter)<<endl;   
 }

 return 0;
}


