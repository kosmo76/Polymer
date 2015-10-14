#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <vector>
#include <string>

#include "polymer.h"
#include "system.h"
#include "analyser.h"

/************************************
 * klasy bazowe do dziedzczenia 
 * na razie taki zarys idei
 * *********************************/

class Experiment
{
public:
    void termalize();
    void simulate();
    void run_simulation();
    void save_old_state();
    
    Experiment(SimulationSystem *system, long term_steps, long sim_steps);
    
    SimulationSystem *system;
    long termalization_steps;
    long simulation_steps;
    int nreptons;
    int dim;
    Polymer * old_polymer;

    std::vector <Analyser *> analysers;
};

#endif

