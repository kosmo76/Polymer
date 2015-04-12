#include <vector>
#include <cmath>
#include "../include/tools.h"
#include "../include/polymer.h"
#include "../include/translation.h"
#include "../include/dynamic.h"
#include "../include/system.h"

#include <iostream>

using std::vector;
using std::string;
using std::log;
using std::exp;

SimulationSystem::SimulationSystem(int nreptons, Translation *trans, Dynamic * model)
{
    if ( model->get_dim() != trans->get_dim() )
        throw "Dynamic and Translation dim is not equal !!!";
    
    this->polymer = new Polymer(nreptons, model->get_dim());
    this->translation = trans;
    this->model = model;
    
    this->initialize_polymer();
    this->initialize_matrix();

}

SimulationSystem::SimulationSystem(string representation, Translation *trans, Dynamic * model)
{
    if ( model->get_dim() != trans->get_dim() )
        throw "Dynamic and Translation dim is not equal !!!";
    
    this->polymer = new Polymer(representation, model->get_dim());
    
    this->translation = trans;
    this->model = model;
    this->initialize_matrix();

}

int SimulationSystem::get_transition_type(int repton_id, int trans_id)
{
   return matrix.at(repton_id).at(trans_id);   
}

std::vector < std::vector <int> > SimulationSystem::get_matrix()
{
  return matrix;   
}

void SimulationSystem::move_repton(int repton_idx, int trans_idx)
{
    if ( matrix.at(repton_idx).at(trans_idx) != 0)
    {
        const vector <int> *w = polymer->get_repton_position(repton_idx);
        vector <int> v = translation->get_translation(trans_idx);
        vector <int> z(v.size(), 0);
        add(*w,v, z);
        polymer->set_repton_position(repton_idx, z);
        polymer->update_links(repton_idx);
        update_matrix(repton_idx);
    }
}

void SimulationSystem::initialize_polymer()
{
 polymer->set_randomly();
}

void SimulationSystem::initialize_matrix()
{
    //stworz macierz translacji z zerami - kolumny to numery translacji, wiersze to reptony
    vector <int> tmp (translation->get_nvectors(),0.0);
    matrix.clear();
    matrix.resize(polymer->get_nreptons(), tmp);
    
    //Zainicjuj macierz translacji zgodnie z aktualmnym stanem polimeru
    //do tego celu musimy miec obiket reprezentujacy polimer po przejsciu bo 
    //nie mozemy zmienic aktualnego polimeru bo musimu znalezc wszystkei przejscia z niego
    Polymer new_polymer(polymer->get_nreptons(), 0) ;
    vector <int> w;
    
    int nreptons = polymer->get_nreptons();
    int nvectors = translation->get_nvectors();
    int type;
    
    for(int repton = 0; repton < nreptons; repton++)
    {
     for(int trans = 0; trans < nvectors; trans++)
     {
       w = translation->get_translation(trans);
       new_polymer = polymer->get_new_by_translation(repton, w);
       if (new_polymer.get_nreptons() == 0)
           continue;
           
       type = model->get_transition_type(*polymer, new_polymer);
       matrix.at(repton).at(trans) = type;
     }
    }
}

void SimulationSystem::update_matrix(int repton_idx, int range)
{
 Polymer new_polymer(polymer->get_nreptons(), 0) ;
 vector <int> w;
 int type;
 int start = repton_idx - range;
 int end = repton_idx + range;
 
 vector <int> tmp(translation->get_nvectors(),0);
 
 if (start < 0)
     start = 0;
 
 if (end >= polymer->get_nreptons())
     end = polymer->get_nreptons() - 1;
 
 for(int repton = start; repton<=end; repton++)
 {    
    for(int trans=0; trans<translation->get_nvectors(); trans++)
    {
       w = translation->get_translation(trans);
       new_polymer = polymer->get_new_by_translation(repton, w);
       if (new_polymer.get_nreptons() == 0)
           matrix.at(repton).at(trans) = 0;
        else
        {   
            type = model->get_transition_type(*polymer, new_polymer);
            matrix.at(repton).at(trans) = type;
        }
    }
 }
}

/***************************************************
 * MEtody klasy TESTOWEJ
 ***************************************************/
TestSimulationSystem::TestSimulationSystem( int nreptons, Translation *trans, Dynamic * model): SimulationSystem(nreptons, trans, model)
{}

TestSimulationSystem::TestSimulationSystem( string rep, Translation *trans, Dynamic * model): SimulationSystem(rep, trans, model)
{}

void TestSimulationSystem::prepare_transision_list()
{
   transitions.clear();
   
   vector <int> tmp;
   int nreptons = polymer->get_nreptons();
   int ntrans = translation->get_nvectors();
   
   for(int rep_idx = 0; rep_idx < nreptons; rep_idx++)
   {
       for(int trans_idx = 0; trans_idx < ntrans; trans_idx++)
       {
          if(matrix.at(rep_idx).at(trans_idx) != 0)
          {  tmp.clear();
             tmp.push_back(rep_idx);
             tmp.push_back(trans_idx);
             transitions.push_back(tmp);
          }
       }
   }
}

vector <int> TestSimulationSystem::choose_transition()
{
   int k;
   prepare_transision_list();
   k = (int)(frand()*transitions.size());
   return transitions.at(k);
}


/**********************************************
 * Kinetic MOnte Carlo
 * *******************************************/
 KMCSimulationSystem::KMCSimulationSystem(int nreptons, Translation *trans, Dynamic * model): SimulationSystem(nreptons, trans,model)
 {}
 
  KMCSimulationSystem::KMCSimulationSystem(string repr, Translation *trans, Dynamic * model): SimulationSystem(repr, trans,model)
 {}

 double KMCSimulationSystem::get_rate_modifier(int repton_idx, int trans_idx)
{ return 1.0; }

void KMCSimulationSystem::prepare_transision_list()
{
   transitions.clear();
   rates_cum_sum.clear();
   double sum =0;
   
   vector <int> tmp;
   int nreptons = polymer->get_nreptons();
   int ntrans = translation->get_nvectors();
   int val;
   double trate;
   double factor;
   
   for(int rep_idx = 0; rep_idx < nreptons; rep_idx++)
   {
       for(int trans_idx = 0; trans_idx < ntrans; trans_idx++)
       {
          val = matrix.at(rep_idx).at(trans_idx);
          if( val != 0)
          {  tmp.clear();
             tmp.push_back(rep_idx);
             tmp.push_back(trans_idx);
             transitions.push_back(tmp);
             trate = model->get_transition_rate(val);
             factor = get_rate_modifier(rep_idx, trans_idx);
             trate = trate * factor;
             sum += trate;
             rates_cum_sum.push_back(sum);
          }
       }
   }
}

vector <int> KMCSimulationSystem::choose_transition()
{
   int k = rates_cum_sum.size()-1;
   prepare_transision_list();
   double f;
   //drabinka prawdopodobienst
   
   double max = rates_cum_sum.at(rates_cum_sum.size()-1);
   
   f = frand()* max;
   
   //szukaj
   for(int i=0; i<rates_cum_sum.size(); i++)
   {
     if (f < rates_cum_sum.at(i))
     {
       k=i;
       break;
     }
   }
   return transitions.at(k);
}

double KMCSimulationSystem:: get_mc_time()
{
  double max = rates_cum_sum.at(rates_cum_sum.size()-1);
  double f = frand();
  
  return -log(f)/max;
}
//TODO do wywalenia
std::vector <double> KMCSimulationSystem::get_rates_cum_sum()
{
  return rates_cum_sum;   
}


 KMCInFieldSimulationSystem::KMCInFieldSimulationSystem(int nreptons, Translation *trans, Dynamic * model, std::vector <double> eps):KMCSimulationSystem(nreptons, trans, model)
 {
  int dim = trans->get_dim();
  epsilon.assign(dim,0);
  for(int i=0; i<eps.size() && i<dim; i++)
    epsilon.at(i) = eps.at(i);
 }
 
 KMCInFieldSimulationSystem::KMCInFieldSimulationSystem(std::string rep, Translation *trans, Dynamic * model, std::vector <double> eps):KMCSimulationSystem(rep, trans, model)
 {
  int dim = trans->get_dim();
  epsilon.assign(dim,0);
  for(int i=0; i<eps.size() && i<dim; i++)
    epsilon.at(i) = eps.at(i);
}

double KMCInFieldSimulationSystem::get_rate_modifier(int repton_idx, int trans_idx)
{
   vector<int> w = translation->get_translation(trans_idx);
   
   double tmp = 0;
   
   for(int i=0; i<epsilon.size(); i++)
        tmp += w.at(i)*epsilon.at(i);
   
   return exp(0.5*tmp);
}