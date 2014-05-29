#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include "../include/tools.h"

/*****************************************
 * RANDOM NUMBERS
 *****************************************/

 //TODO - pomyśleć nad zmianą generatora na cos
 //sensownego - Mersen-Twisster lub cos podobny
double frand()
{
   return std::rand()/(RAND_MAX+1.0);
}

/*******************************************
 * Funkcje pomocne przy liczeniu wsp
 * **************************************/

int is_equal( std::vector <int>  &w, std::vector < int> &v)
{
    if ( w.size() != v.size() )
        return 0;
    
    for(int i=0; i < w.size(); i++)
    {
      if ( w.at(i) != v.at(i))
          return 0;
    }
    
    return 1;
    
}

int is_opposite(std::vector <int>  &w, std::vector < int> &v)
{
    if ( w.size() != v.size() )
        return 0;
    
    for(int i=0; i< w.size(); i++)
    {
      if ( w.at(i) != -1*v.at(i))
          return 0;
    }
    
    return 1;
    
}

double get_square_distance( std::vector <int>  &w, std::vector < int> &v )
{
  double sum = 0;
  double dx;
  for(int i=0; i<w.size(); i++)
  {
        dx = w.at(i) - v.at(i);
        sum = sum + dx*dx;
  }
  
  return sum;
}

double get_distance(std::vector <int>  &w, std::vector < int> &v)
{
   return std::sqrt(get_square_distance(w, v));
}

void add(std::vector <int>  const &w, std::vector <int> const &v, std::vector <int> &tmp)
{
    for(int i=0; i<w.size(); i++)
    {
      tmp[i] =  w.at(i) + v.at(i);
    }
}

void diff(std::vector <int>  const &w, std::vector <int> const &v, std::vector <int> &tmp)
{
    for(int i=0; i<w.size(); i++)
    {
      tmp[i] =  w.at(i) - v.at(i);
    }
}

double dot(std::vector <int>  &w, std::vector <int> &v)
{
  double sum = 0;
  for(int i=0; i< w.size(); i++)
      sum += w.at(i)*v.at(i);
  return sum;
}


