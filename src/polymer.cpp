#include "../include/polymer.h"
#include "../include/tools.h"

using std::vector;
using std::string;

Polymer::Polymer(int nreptons, int dim)
{
    this->dim = dim;
    this->nreptons=nreptons;
    //ustaw tymczasowy wektor
    this->tmp.assign(dim,0);
    
    vector <int> pos(dim,0);
    //ustaw pozycje retonow na 0
    for(int i=0; i<nreptons; i++)
        this->positions.push_back(pos);
    
    //ustaw linki na 0
    for(int i=0; i<nreptons-1; i++)
        this->links.push_back(pos);
    
    
}

Polymer::Polymer(string repr, int dim)
{
    this->dim = dim;
    this->nreptons = repr.size()+1;
    
    //wyzeruj wektor  tymczasowy
    this->tmp.assign(dim,0);
    
    vector <int> pos(dim,0);
    for(int i=0; i<nreptons; i++)
        this->positions.push_back(pos);
    
    set_from_representation(repr);
    //wypelnij  wektor linkow
    for(int i=0; i<nreptons-1; i++)
        this->links.push_back(pos);
    //policz wektory linkow dla aktualnej konfiguracji
    calculate_links();
}

int Polymer::get_dim()
{   return dim;  }

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
  for(int i=1; i<nreptons; i++)
  {
    if  ( get_square_distance(positions.at(i-1), positions.at(i)) > 1.0 )
        return 0;
  }
  return 1;                         
}

const vector<int> * Polymer::get_repton_position(int idx)
{ return & this->positions.at(idx); }

const vector < vector <int> > * Polymer::get_reptons_positions()
{ return & this->positions; }

void Polymer::set_repton_position( int idx, vector<int> const & pos)
{ 
    for(int i=0; i<this->dim; i++)
        this->positions[idx][i] = pos[i]; 
}

const std::vector<int> * Polymer::get_link_vector(int link_number)
{
    return & this->links.at(link_number);
//     diff(positions.at(link_number+1), positions.at(link_number), tmp);
//     return tmp;
}


void Polymer::calculate_links()
{
    for(int i=0; i<this->get_nlinks(); i++)
    {
        diff(positions.at(i+1), positions.at(i), tmp);
        links.at(i) = tmp;
    }
}

void Polymer::update_links(int repton_idx)
{
    //oblicz indeksy linkow repton = 0  - link 0, repton = 1 , link 0, 1, ...
    
    int start = repton_idx - 1;
    if ( start < 0)
        start = 0;
    
    int end = repton_idx;
    if ( end >= get_nlinks())
        end = get_nlinks() - 1;
        
    for(int i=start; i<=end; i++)
    { 
        diff(positions.at(i+1), positions.at(i), tmp);
        links.at(i) = tmp;     
    }
}

const std::vector< std::vector <int> > * Polymer::get_links_vectors()
{
    return & links;
}
    

char Polymer::get_link_symbol(int link_number)
{
    if (dim == 1)
     {
        if ( links.at(link_number).at(0) == 0 )
            return 's';
        
        if ( links.at(link_number).at(0) == 1 )
            return 'r';
        
        if ( links.at(link_number).at(0) == -1 )
            return 'l';
     }
    
     if (dim == 2)
     {
        if ( links.at(link_number).at(0) == 0 and links.at(link_number).at(1) == 0)
            return 's';
        
        if ( links.at(link_number).at(0) == 0 and links.at(link_number).at(1) == 1 )
            return 'u';
        
        if ( links.at(link_number).at(0) == 1 and links.at(link_number).at(1) == 0)
            return 'r';
        
        if ( links.at(link_number).at(0) == 0 and links.at(link_number).at(1) == -1)
            return 'd';
        
        if ( links.at(link_number).at(0) == -1 and links.at(link_number).at(1) == 0)
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


int Polymer::check_translation(int idx, std::vector<int> const &trans)
{
    int prev_idx, next_idx;
     
    prev_idx = get_prev_idx(idx);
    next_idx = get_next_idx(idx);
 
    add( positions.at(idx), trans, this->tmp);
 
    if (prev_idx >= 0)
     {
        if ( get_distance(this->tmp, positions.at(prev_idx))> 1.1 )
        {
            return 0;
        }
     }
     if (next_idx >= 0)
     {
        if (get_distance(this->tmp, positions.at(next_idx))> 1.1)
            return 0;
     }
     
    return 1;
}

Polymer Polymer::get_new_by_translation(int idx, std::vector<int> const &trans)
{
     
    Polymer p(nreptons, dim);
    if ( check_translation(idx, trans) )
    {
      for(int i=0; i<nreptons; i++)
        p.set_repton_position(i, positions.at(i));
    
      p.set_repton_position(idx, this->tmp);
      p.calculate_links();
      return p;
    }
    //jesli blad zwroc pustego polimera
    return Polymer(0,dim);
}

int Polymer::translate_repton(int idx, std::vector<int> const &trans)
{
    if ( check_translation(idx, trans))
    { 
     for(int i=0; i<dim; i++)
         positions.at(idx).at(i) = tmp.at(i);
     
     update_links(idx); 
     
     return 1;
    }
    
    return 0;
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

int Polymer::copy_data(Polymer &p)
{
    if (this->dim != p.dim)
        return 0;
 
    if (this->nreptons != p.nreptons)
        return 0;
 
    const vector <int> *w; 
    for(int i=0; i<nreptons; i++)
    {
        w = p.get_repton_position(i);
        set_repton_position(i,*w);
    }
    return 1;
}