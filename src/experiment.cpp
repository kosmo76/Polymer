#include <vector>
#include <cmath>
#include "../include/tools.h"
#include "../include/polymer.h"
#include "../include/translation.h"
#include "../include/dynamic.h"
#include "../include/system.h"
#include "../include/analyser.h"
#include "../include/experiment.h"


#include <iostream>

using std::vector;
using std::string;
using std::log;
using std::exp;


Experiment:: Experiment(SimulationSystem *system, long term_steps, long sim_steps)
{
   this->system = system;
   termalization_steps = term_steps;
   simulation_steps = sim_steps;
   
   nreptons = system->polymer->get_nreptons();
   dim = system->model->get_dim();
   
   old_polymer=new Polymer(nreptons, dim);
}

void Experiment::save_old_state()
{
   old_polymer->copy_data(*system->polymer);
}
void Experiment::termalize()
{
 vector <int> tmp;
 for(long step=0; step < termalization_steps; step++)
 {
    tmp = system->choose_transition();
    system->move_repton(tmp.at(0), tmp.at(1));   
 }
}

void Experiment::simulate()
{
 vector <int> tmp;
 for(long step=0; step < simulation_steps; step++)
 {
    save_old_state();
    tmp = system->choose_transition();
    system->move_repton(tmp.at(0), tmp.at(1));
    //polec po analizatorach
    for(int i=0; i<analysers.size(); i++)
    {
      analysers.at(i)->analyse(step, old_polymer, system->polymer);
    }
 }    
}

void Experiment::run_simulation()
{
    termalize();
    simulate();
}
    