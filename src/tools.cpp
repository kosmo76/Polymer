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

/**************************************************
 * Funkcje pomocne przy obliczeniach na vectorach
 * ***********************************************/

int is_equal( const std::vector <int>  &w, const std::vector < int> &v)
{
    if ( w.size() != v.size())
        throw "Wrong vector size";
    
    for(int i=0; i < w.size(); i++)
    {
      if ( w.at(i) != v.at(i))
          return 0;
    }
    
    return 1;    
}

int is_opposite(const std::vector <int>  &w, const std::vector < int> &v)
{
    if ( w.size() != v.size())
        throw "Wrong vector size";
        
    for(int i=0; i< w.size(); i++)
    {
      if ( w.at(i) != -1*v.at(i))
          return 0;
    }
    
    return 1;
}

double get_square_distance( const std::vector <int>  &w, const std::vector < int> &v )
{
  if ( w.size() != v.size())
        throw "Wrong vector size";

  double sum = 0;
  double dx;
  for(int i=0; i<w.size(); i++)
  {
        dx = w.at(i) - v.at(i);
        sum = sum + dx*dx;
  }
  
  return sum;
}

double get_distance(const std::vector <int>  &w, const std::vector < int> &v)
{
    if ( w.size() != v.size())
        throw "Wrong vector size";
    
   return std::sqrt(get_square_distance(w, v));
}

double dot(const std::vector <int>  &w, const std::vector <int> &v)
{
  double sum = 0;
  for(int i=0; i< w.size(); i++)
      sum += w.at(i)*v.at(i);
  return sum;
}

void add(const std::vector <int>  &w, const std::vector <int> &v, std::vector <int> &tmp)
{
    if ( w.size() != v.size() or w.size() != tmp.size())
        throw "Wrong vector size";
    for(int i=0; i<w.size(); i++)
    {
      tmp[i] =  w.at(i) + v.at(i);
    }    
}

void diff(const std::vector <int>  &w, const std::vector <int> &v, std::vector <int> &tmp)
{ 
    if ( w.size() != v.size() or w.size() != tmp.size())
        throw "Wrong vector size";
    
    for(int i=0; i<w.size(); i++)
    {
      tmp[i] =  w.at(i) - v.at(i);
    }
}
