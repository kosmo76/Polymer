#include "../include/translation.h"
#include <iostream>

using std::vector;

using namespace std;

Translation::Translation(int dim)
{
  this->dim = dim;
  initialize();
}
vector <int> Translation::get_translation(int idx)
{
   return trans_vect.at(idx);   
}
    
int Translation::get_dim()
{
   return dim;   
}

int Translation::get_nvectors()
{
   return nvectors;   
}

void Translation::initialize()
{
}



NearestNeighbour::NearestNeighbour(int dim) : Translation(dim)
{ initialize();}

void NearestNeighbour::initialize()
{
    vector <int> tmp;
    if ( dim == 1 )
    {
        tmp.push_back(1);
        trans_vect.push_back(tmp);
        tmp[0]=-1;
        trans_vect.push_back(tmp);
        nvectors = trans_vect.size();
        return;
    }
    
    if ( dim == 2 )
    {   tmp.push_back(0);
        tmp.push_back(1);
        trans_vect.push_back(tmp);
        tmp[0]=1;
        tmp[1]=0;
        trans_vect.push_back(tmp);
        
        tmp[0]=0;
        tmp[1]=-1;
        trans_vect.push_back(tmp);
        
        tmp[0]=-1;
        tmp[1]=0;
        trans_vect.push_back(tmp);
        
        nvectors = trans_vect.size();
        return;
    }
    
      
}

std::vector < std::vector <int> >  NearestNeighbour::get_initial_translations()
{
  return  trans_vect;   
}


SecondNearestNeighbour::SecondNearestNeighbour(int dim) : Translation(dim)
{ initialize();}

void SecondNearestNeighbour::initialize()
{
    vector <int> tmp;
    if ( dim == 1 )
    {
        tmp.push_back(1);
        trans_vect.push_back(tmp);
        tmp[0]=-1;
        trans_vect.push_back(tmp);
        nvectors = trans_vect.size();
        return;
    }
    
    if ( dim == 2 )
    {
        tmp.push_back(0);
        tmp.push_back(1);
        trans_vect.push_back(tmp);
        tmp[0]=1;
        tmp[1]=0;
        trans_vect.push_back(tmp);
        
        tmp[0]=0;
        tmp[1]=-1;
        trans_vect.push_back(tmp);
        
        tmp[0]=-1;
        tmp[1]=0;
        trans_vect.push_back(tmp);
   
        tmp[0]=1;
        tmp[1]=1;
        trans_vect.push_back(tmp);
   
        tmp[0]=1;
        tmp[1]=-1;
        trans_vect.push_back(tmp);
   
        tmp[0]=-1;
        tmp[1]=-1;
        trans_vect.push_back(tmp);
   
        tmp[0]=-1;
        tmp[1]=1;
        trans_vect.push_back(tmp);
   
        nvectors = trans_vect.size();
        return;
    }
    
      
}

std::vector < std::vector <int> > SecondNearestNeighbour::get_initial_translations()
{
    if (dim == 1)
        return trans_vect;   
    
    if (dim == 2)
    {
        vector< vector <int> > tmp(trans_vect.begin(), trans_vect.begin() + 4);
        return tmp;
    }
}