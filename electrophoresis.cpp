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
  
vector <double> simulate_system( int dim, int nreptons, long term_steps, long steps, 
                                 double rate_r, double rate_h, double rate_c, double rate_m, 
                                 double eps_x, double eps_y)
{
 vector <double> eps;
 eps.push_back(eps_x);
 eps.push_back(eps_y);
 
 //rodzaj translacji
 NearestNeighbour trans_obj(dim);
 RouseDynamic rouse(rate_r, rate_h, rate_c, rate_m, dim);
 KMCInFieldSimulationSystem system(nreptons, &trans_obj, &rouse, eps);
 vector <int> tmp;
 vector <double> cms, start_cms, end_cms;
 //termalizacja
 //ustaw epsilony na zero
 double eps_i = system.epsilon.at(0);
 system.epsilon.at(0)=0.0;
 for(long i=0; i< term_steps; i++)
 { 
   tmp = system.choose_transition();
   system.move_repton(tmp.at(0), tmp.at(1));      
 }
 system.epsilon.at(0) = eps_i;
 //wlasciwa symulacja - zapisujemy do pliku, i przy okazji zliczamy
 double start_time = 0;
 double kmc_time, total_time=0.0;
 
 start_cms = system.polymer->get_cms_coord();
 
 for(long i=0; i< steps; i++)
 { 
   tmp = system.choose_transition();
   system.move_repton(tmp.at(0), tmp.at(1));      
   
   cms = system.polymer->get_cms_coord();
   kmc_time = system.get_mc_time();
   
   total_time = total_time + kmc_time;   
 }
 
 end_cms = cms;
 
 vector <double> velocity;
 //wyswietl na koncu Vdrift
 for(int i = 0; i<dim; i++)
    velocity.push_back((end_cms.at(i) - start_cms.at(i))/total_time);
 
 return velocity;
}


//PARAMETRY
// nreptons, eps_x, steps, runs
main(int argc, char * argv[])
{
 srand(time(NULL));
 int dim = 1;                //wymiarowosc ukladu
 int nreptons = 7;           //ilosc repotonow
//ustaw parametry symulacji
 long term_steps = 100000;   //termalizacja
 long steps = 4000000;      //dlugosc symulacji po termalizacji
  
 //parametry modelu
 double rate_r = 1.0, rate_h=0.0, rate_c=0.0, rate_m=0.0;
 double eps_x = 1.4, eps_y=0;


 steps = atol(argv[3]); 
 eps_x = atof(argv[2]);
 nreptons = atoi(argv[1]);
 vector <double> v_tmp(dim, 0);
    
 int runs = 2000;
 runs = atoi(argv[4]);

 vector < vector <double> > velocity(runs, v_tmp);
 
 for(int i=0; i<runs; i++)
 {
 v_tmp = simulate_system(dim, nreptons, term_steps, steps, rate_r, rate_h, rate_c, rate_m, eps_x, eps_y);
 velocity.at(i) = v_tmp;
 }
 
 cout <<"#Predkosci z poszczegolnych runow"<<endl;
 for(int k=0; k<velocity.size(); k++)
 {
    for(int i=0; i<dim; i++)
        cout << velocity.at(k).at(i)<<"  ";
    cout<<endl;
 }
 
 //policz srednie
 //TODO - jesi wiecej wymiarow to tutaj uwaga
double sum_x = 0, sum_x2 = 0;
for(int k=0; k<velocity.size(); k++)
{
   sum_x = sum_x + velocity.at(k).at(0);
   sum_x2 = sum_x2 + velocity.at(k).at(0)*velocity.at(k).at(0);
}
cout << "\n\nKroki " << steps << "   Runs "<< runs << "  EPS = "<< eps_x<<"  Reptons = "<<nreptons<<endl;
cout << "Wynik " << sum_x/velocity.size() << " sig^2 = "<<sum_x2/velocity.size() - (sum_x/velocity.size())*(sum_x/velocity.size())<<endl;
 return 0;
}


