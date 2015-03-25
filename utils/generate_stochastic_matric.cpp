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


int get_state_number( string actual, vector <string> &states)
{
    
   for(int i=0; i<states.size(); i++)
   {
     if (states.at(i) == actual)
         return i;
   }
   return -1;
}
void check_trans(Polymer &p, vector <string> &states, double reptation, double hernia, double cross, double migration, int print_type)
{
    SecondNearestNeighbour trans_obj(p.get_dim());
    RouseDynamic rouse(reptation, hernia, cross, migration, p.get_dim());
 
    Polymer p_tmp(p.get_nreptons(), 0);
    vector< int>  tmp;
    
    int type;
    if (print_type==1)
        cout<<"Start : "<<p.get_representation()<<endl;
    else
        cout <<get_state_number(p.get_representation(), states)<<":";
    
    for(int r=0; r<p.get_nreptons(); r++)
    {
        for(int idx = 0; idx < trans_obj.get_nvectors(); idx++)
        {
            tmp = trans_obj.get_translation(idx);
            p_tmp = p.get_new_by_translation(r,tmp);
            if (p_tmp.get_nreptons() != 0)
            {
                type =  rouse.get_transition_type(p, p_tmp);
                if ( type != 0 )
                    if (print_type == 1)
                        cout <<"  --- > :  "<<p_tmp.get_representation()<<"  "<<type<<"   "<< rouse.get_transition_rate(type) << endl;
                    else
                        cout <<" "<<get_state_number(p_tmp.get_representation(), states)<<"-"<<rouse.get_transition_rate(type);
            }
        }
    }
    if(print_type==0)
        cout <<endl;
}


//Ponizsze dwie funkcje sa napisane na szybko i nie nadaja sie do wiekszej dlugosci polimerow !!!
vector <string> get_states_from_state( string base, string init)
{
  vector <string> tmp;
  string state = init;
  for(int i=0; i<base.size(); i++)
  {
     state.push_back(base.at(i));
     tmp.push_back(state);
     state = init;
  }
  return tmp;    
}

vector <string> generate_all_states(int nlink, int dim)
{
  string start="", base;
  switch (dim)
  {
      case 1:
            base="srl";
            break;
      case 2:
            base="surdl";
            break;
      default:
            base="srl";
  }

  vector <string> result;
  result = get_states_from_state(base, start);
  if ( nlink == 1 )
      return result;
      
  vector <string> tmp_result, tmp;
  
  for(int l = 0; l < nlink-1; l++)
  {
   for( int i=0; i<result.size(); i++)
   {
    tmp = get_states_from_state(base, result.at(i));
    //przepisz 
    for( int j=0; j<tmp.size(); j++)
        tmp_result.push_back(tmp.at(j));
   }
   result = tmp_result;
   tmp_result.clear();
  }
  return result;
  
}


void generowanie_macierzy_test(int nlinks, int dim, double reptation, double hernia, double cross, double migration, int print_type)
{
    vector <string> test;
    test = generate_all_states(nlinks, dim);
    
    
    for(int i=0; i< test.size(); i++)
    {
        Polymer p(test.at(i), dim);
        check_trans(p, test, reptation, hernia, cross, migration, print_type);
    }
    
}

  
main()
{
 srand(time(NULL));
 double reptation=1.0;
 double hernia=0.2;
 double cross=0.2;
 double migration=0.2;
 int links=2;
 int dim = 2;
 int print_type = 0; //0 - dla macierzy w pythnie, 1 do czytania 
 
 generowanie_macierzy_test(links, dim, reptation, hernia, cross, migration, print_type);
 return 0;
}


