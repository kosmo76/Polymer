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
using namespace std;

void difusion_KMC(int dim, int nreptons, long mc_steps, double eps_x, double eps_y, int runs = 1)
{
  NearestNeighbour trans_obj(dim);
  RouseDynamic rouse(1.0, 0., 0., 0., dim);
  
  long steps = mc_steps; //generalnie chyb apowinno byc * nreptons
  vector <double> pos_start, pos_end;
  
  vector <double> eps;
  eps.push_back(eps_x);
  eps.push_back(eps_y);
  
  KMCInFieldSimulationSystem s1(nreptons, &trans_obj, &rouse, eps);
  
  double dt; 
  double time, time_start, time_end, delta_time;
  vector <int> tmp;
  
  //termalizacja
  for(long i=0; i<nreptons*nreptons*nreptons; i++)
  {
    tmp = s1.choose_transition();
    s1.move_repton(tmp.at(0), tmp.at(1));
  }
  
  for(int run = 0; run < runs; run++)
  {
      time = 0;
      //wypisz polozenie wybranego reptonu
      pos_start = s1.polymer->get_cms_coord();
      time_start = time;
      
      long iter=steps;
      for(long i=0; i<iter; i++)
      {
        tmp = s1.choose_transition();
        s1.move_repton(tmp.at(0), tmp.at(1));
        dt = s1.get_mc_time();
        time = time + dt;
      }
      pos_end = s1.polymer->get_cms_coord();
      time_end = time;
      delta_time = time_end - time_start;
      cout <<delta_time<<"  ";
      for(int i=0; i<pos_start.size(); i++)
        cout <<(pos_end.at(i) - pos_start.at(i))/delta_time<<" ";
      cout <<endl;
      
  }
}
  
main()
{
 srand(time(NULL));
 cout <<"START !!!"<<endl;
 difusion_KMC(2,10,100000,0.001,0.0,10);
 return 0;
}


