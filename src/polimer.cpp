#include "polimer.h"
#include "tools.h"
using std::vector;
using std::string;

Polymer::Polymer()
{
  dim = 0;   
  nreptons = 0;
}

Polymer::Polymer(int nreptons, int dim)
{
    this->dim = dim;
    this->nreptons=nreptons;
    vector <int> pos(dim,0);
    for(int i=0; i<nreptons; i++)
        this->positions.push_back(pos);
}

Polymer::Polymer(string repr, int dim)
{
    this->dim = dim;
    this->nreptons = repr.size()+1;
    vector <int> pos(dim,0);
    for(int i=0; i<nreptons; i++)
        this->positions.push_back(pos);
    set_from_representation(repr);
}

int Polymer::get_ndim()
{
   return dim;   
}

void Polymer::set_from_representation(std::string repr)
{
    vector <int> zero(dim,0);
    //ustaw pierwszego
    this->positions[0] = zero;
    
    if (dim == 1)
    {
        for(int i=0; i<repr.size(); i++)
        {
        switch (repr[i])
        {
            case 's':
                this->positions[i+1][0] = this->positions[i][0];
                break;
                
            case 'r':
                this->positions[i+1][0] = this->positions[i][0] + 1;
                break;
                
            case 'l':
                this->positions[i+1][0] = this->positions[i][0] - 1;
                break;
        }
        }
     }
     
    if (dim == 2)
    {
        for(int i=0; i<repr.size(); i++)
        {
        switch (repr[i])
        {
            case 's':
                this->positions[i+1][0] = this->positions[i][0];
                this->positions[i+1][1] = this->positions[i][1];
                break;
                
            case 'r':
                this->positions[i+1][0] = this->positions[i][0] + 1;
                this->positions[i+1][1] = this->positions[i][1];
                break;
                
            case 'l':
                this->positions[i+1][0] = this->positions[i][0] - 1;
                this->positions[i+1][1] = this->positions[i][1];
                break;
                
            case 'u':
                this->positions[i+1][0] = this->positions[i][0];
                this->positions[i+1][1] = this->positions[i][1] + 1;
                break;
                
            case 'd':
                this->positions[i+1][0] = this->positions[i][0];
                this->positions[i+1][1] = this->positions[i][1] - 1;
                break;
        }
        }
     }
}

int Polymer::get_nreptons()
{ return this->nreptons;}

int Polymer::get_nlinks()
{ return this->get_nreptons() - 1;}

int Polymer::check_integrity()
{ 
  vector <int> first, last;
  
  for(int i=1; i<nreptons; i++)
  {
    if  ( get_square_distance(positions.at(i-1), positions.at(i)) > 1.0 )
        return 0;
  }
  return 1;                         
}

vector<int> Polymer::get_repton_position(int idx)
{ return this->positions.at(idx); }

vector < vector <int> > Polymer::get_reptons_positions()
{ return this->positions; }

void Polymer::set_repton_position( int idx, vector<int> pos)
{ this->positions[idx] = pos; }

std::vector<int> Polymer::get_link_vector(int link_number)
{
    vector <int> repton_1, repton_2, link;
    
    repton_1 = positions.at(link_number);
    repton_2 = positions.at(link_number+1);
    return diff(repton_2, repton_1);
}

std::vector< std::vector <int> > Polymer::get_links_vectors()
{
    vector < vector <int> > w;
    
    for(int i=0; i<this->get_nlinks(); i++)
        w.push_back(this->get_link_vector(i));
    
    return w;
}

char Polymer::get_link_symbol(int link_number)
{
    vector <int> repton_1, repton_2, link;
    
    repton_1 = positions.at(link_number);
    repton_2 = positions.at(link_number+1);
    link = diff(repton_2, repton_1);
    
     if (dim == 1)
     {
        if ( link.at(0) == 0 )
            return 's';
        
        if ( link.at(0) == 1 )
            return 'r';
        
        if ( link.at(0) == -1 )
            return 'l';
     }
    
     if (dim == 2)
     {
        if ( link.at(0) == 0 and link.at(1) == 0)
            return 's';
        
        if ( link.at(0) == 0 and link.at(1) == 1 )
            return 'u';
        
        if ( link.at(0) == 1 and link.at(1) == 0)
            return 'r';
        
        if ( link.at(0) == 0 and link.at(1) == -1)
            return 'd';
        
        if ( link.at(0) == -1 and link.at(1) == 0)
            return 'l';
     }
}

std::string Polymer::get_representation()
{
  std::string tmp="";
  char c;
  
  for(int i=0; i<nreptons-1;i++)
  {   c = get_link_symbol(i);
      tmp.push_back(c);
  }
  return tmp;
}

int Polymer::get_next_idx(int idx)
{
    int next_idx = idx + 1;
    if (next_idx >= nreptons)
        return -1;
    return next_idx;
}

int Polymer::get_prev_idx(int idx)
{
  int prev_idx = idx -1;
  if (prev_idx < 0)
      return -1;
  return prev_idx;
}


Polymer Polymer::get_new_by_translation(int idx, std::vector<int> trans)
{
     vector <int> first, middle, last, tmp, r;
     int prev_idx, next_idx;
     
     prev_idx = get_prev_idx(idx);
     next_idx = get_next_idx(idx);
     middle = get_repton_position(idx);
     middle = add(middle, trans);
     if (prev_idx >= 0)
     {
        first = get_repton_position(prev_idx);
        if (get_distance(middle, first)> 1.1 )
            return Polymer(0,dim);
     }
     if (next_idx >= 0)
     {
        last = get_repton_position(next_idx);
        if (get_distance(middle, last)> 1.1)
            return Polymer(0,dim);
     }
    
    Polymer p(nreptons, dim);
    for(int i=0; i<nreptons; i++)
        p.set_repton_position(i, positions.at(i));
    p.set_repton_position(idx, middle);
    
    return p;
}

vector <double> Polymer::get_cms_coord()
{
   vector <double> tmp(dim, 0.);
   
   //reptony bezmasowe wiec pokrywa sie ze srodkiem geometrycznym
   
   for(int i=0; i<dim; i++)
   {
       for(int j=0; j<nreptons; j++)
           tmp[i] += positions[j][i];
   }
 
   for(int i=0; i<dim; i++)
           tmp[i] = tmp[i]/nreptons;
 
   return tmp;
}