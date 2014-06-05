#include <iostream>
#include <string>
#include <vector>
#include "include/tools.h"
#include "include/polymer.h"

using namespace std;

void show_vector( const vector <int> *w)
{
   cout <<"<";
   for(int i = 0; i< w->size(); i++)
       cout << w->at(i)<<", ";
   cout <<">"<<endl;
}

void check_polymer(Polymer &p)
{
    
    cout <<"Wymiarowosc  "<<p.get_dim()<<endl;
 cout <<"Reptony " << p.get_nreptons()<<endl;
 cout <<"Linki "<< p.get_nlinks()<<endl;
 //wyswietl pozycje reptonow
 const vector <int> *pos;
 cout <<"POZYCJE reptonow :\n";
 for (int i=0; i<p.get_nreptons(); i++)
 {
     pos = p.get_repton_position(i);
     show_vector(pos);
 }
 
 const vector <vector <int> >*k;
 
 k = p.get_reptons_positions();
 cout <<"Sprawdzamy wyciagniecie wszytskich pozycji na raz \n";
  for(int i=0; i<k->size(); i++)
  {
     pos = & k->at(i);
     show_vector(pos);
  }

  cout <<"Wektory linkow \n";
  for(int i=0; i<p.get_nlinks();i++)
  {
     pos = p.get_link_vector(i)  ;
     show_vector(pos);
  }
  
 k = p.get_links_vectors();
 cout <<"Sprawdzamy wyciagniecie wszytskich linkow na raz \n";
  for(int i=0; i<k->size(); i++)
  {
     pos = & k->at(i);
     show_vector(pos);
  }
  
  cout <<"Reprezentcaja : " <<p.get_representation()<<endl;
  cout <<"Link po linku : ";
  for(int i=0; i<p.get_nlinks(); i++)
      cout <<p.get_link_symbol(i);
  cout <<endl;
}

main()
{
  //same slacki 1D, sprawdzmy 3 reptony, 1D
  Polymer p0(3,1);
 
  cout <<"Test ss"<<endl;
  check_polymer(p0);
  cout <<"**************************************************************\n\n\n";
  
  //z zadanej konfiguracji 1D, 
  Polymer p0_1("lrrsl",1);
 
  cout <<"Test lrrsl"<<endl;
  check_polymer(p0_1);
  cout <<"**************************************************************\n\n\n";
    
  //same slacki 2D, sprawdzmy
  Polymer p1(3,2);
 
  cout <<"Test ss"<<endl;
  check_polymer(p1);
  cout <<"**************************************************************\n\n\n";
  
  //z zadanej konfiguracji D
  Polymer p2("rddlu", 2);
  cout <<"Test rddlu"<<endl;
  check_polymer(p2);
  cout <<"**************************************************************\n\n\n";

  //testy zmiany konfguracji i updateu linkow
  cout <<"Test zmiany konfiguracji\n";
  Polymer p3("rdsdlsl", 2);
  
  cout <<"Start "<<p3.get_representation()<<endl;
  cout <<"Translacja zerowego w lewo - ZABRONIONE ( 0 )"<<endl;
  
  vector <int> trans;
  trans.push_back(-1);
  trans.push_back(0);
  
  cout <<"Wynik = "<<p3.check_translation(0, trans)<<endl;
  
  Polymer p4 = p3.get_new_by_translation(0, trans);
  cout <<"Nowy polimer po translacji (reptony) : "<< p4.get_nreptons() <<endl;
  cout <<"Zmian konfoguracji, wynik = "<<p3.translate_repton(0, trans)<<endl;
  cout << "Aktualna konfiguracja "<< p3.get_representation()<<endl;
  
  cout <<"\nTranslacja zerowego w prawo - OK( 1 )"<<endl;
  
  trans.at(0) = 1;
  trans.at(1) = 0;
  cout <<"Wynik = "<<p3.check_translation(0, trans)<<endl;
  
  p4 = p3.get_new_by_translation(0, trans);
  cout <<"Nowy polimer po translacji (reptony) : "<< p4.get_nreptons() <<endl;
  if (p4.get_nreptons() > 0)
      cout << "Konf: " <<p4.get_representation()<<endl;
  cout <<"Zmian konfiguracji, wynik = "<<p3.translate_repton(0, trans)<<endl;
  cout << "Aktualna konfiguracja "<< p3.get_representation()<<endl;
  
  cout <<"\nTranslacja piatego do gory- ZABRONIONE( 0 )"<<endl;
  trans.at(0) = 0;
  trans.at(1) = 1;
  cout <<"Zmian konfiguracji, wynik = "<<p3.translate_repton(5, trans)<<endl;
  cout << "Aktualna konfiguracja "<< p3.get_representation()<<endl;
  
  cout <<"\nTranslacja piatego w prawo - TAK ( 1 )"<<endl;
  trans.at(0) = 1;
  trans.at(1) = 0;
  cout <<"Zmian konfiguracji, wynik = "<<p3.translate_repton(5, trans)<<endl;
  cout << "Aktualna konfiguracja "<< p3.get_representation()<<endl;
  
  
 return 0;
 }
