#include <iostream>
#include <vector>
#include "include/translation.h"

using namespace std;


void show_vector(vector <int> &w)
{
  cout <<"<";
   for(int i=0; i< w.size(); i++)
       cout <<w.at(i)<<", ";
   cout << ">"<<endl;
}

void test(Translation *trans)
{
  vector <int> w;
  vector < vector <int> > k;
  cout <<"*******************************"<<endl;
  cout <<"Wymiarowosc :"<< trans->get_dim()<<endl;
  cout <<"Ile wektorow :"<< trans->get_nvectors()<<endl;
  cout <<"Wektory pojedynczo : "<<endl;
  for(int i=0; i< trans->get_nvectors(); i++)
  {
    w = trans->get_translation(i);
    show_vector(w);
  }
  cout <<"Wektory poczatkowe:"<<endl;
  k = trans->get_initial_translations();
  for(int i=0; i< k.size(); i++)
  {
     w = k.at(i);
     show_vector(w);
  }
}

main()
{
  NearestNeighbour trans_1(1);
  test(&trans_1);

  NearestNeighbour trans_2(2);
  test(&trans_2);
  
  SecondNearestNeighbour trans_3(2);
  test(&trans_3);
  

  

 return 0;
}