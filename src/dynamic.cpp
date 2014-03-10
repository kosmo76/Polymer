#include "dynamic.h"
#include "tools.h"
#include "polimer.h"

using std::vector;

Dynamic::Dynamic()
{}

void Dynamic::set_rates( std::vector <double> rates)
{
   this->rates = rates;   
}

RouseDynamic::RouseDynamic(double r, double h, double c)
{
    rates.push_back(0.0); //rate dla zabronionego przejsca dla zachowani spojnosci
    rates.push_back(r);
    rates.push_back(h);
    rates.push_back(c);
}

double RouseDynamic::get_transition_rate(int code)
{
   if ( code < rates.size() )
       return rates.at(code);
   return 0;
}

double RouseDynamic::get_reptation_rate()
{ return rates.at(RouseDynamic::REPTATION);}

double RouseDynamic::get_hernia_rate()
{ return rates.at(RouseDynamic::HERNIA);}

double RouseDynamic::get_crossing_rate()
{ return rates.at(RouseDynamic::CROSSING);}

void RouseDynamic::set_reptation_rate(double &r)
{ rates.at(RouseDynamic::REPTATION) = r; }

void RouseDynamic::set_hernia_rate(double &h)
{ rates.at(RouseDynamic::HERNIA) = h; }

void RouseDynamic::set_crossing_rate(double &c)
{ rates.at(RouseDynamic::CROSSING) = c; }

//metoda bazujaca na wektorze polozen reptonow
int RouseDynamic :: get_transition_type( std::vector < std::vector <int> > &start, std::vector < std::vector <int> > &end)
{
    //przygotuj reprezentacja polimera jako linkow a nie reptonow
    vector <  vector <int> > old_links, new_links;
    vector <int> tmp;
    
    //wektor linku to roznica polozen kolejnych reptonow
    for(int i=0; i<start.size()-1; i++)
    {
        tmp = diff(start.at(i+1), start.at(i));
        old_links.push_back(tmp);
    }
    
    for(int i=0; i<end.size()-1; i++)
    {
        tmp = diff(end.at(i+1), end.at(i));
        new_links.push_back(tmp);
    }

    return get_transition_type_by_links(old_links, new_links);
   
}

//metoda bazujaca na obiektach klasy Polymer
int RouseDynamic:: get_transition_type( Polymer &p1, Polymer &p2)
{
    vector < vector <int> > p1_links, p2_links;
    
    p1_links = p1.get_links_vectors();
    p2_links = p2.get_links_vectors();
       
    return get_transition_type_by_links(p1_links, p2_links);
}

// prywatne metody !

//metoda wywolywana TYLKO jesli jeden z koncowych linkow sie zmienil w wyniku translacji
int RouseDynamic::check_end_link(vector <int> &old_link, vector<int> &new_link)
{
  //definicja slacka dla linku w n-wymiarach - (0), (0,0), (0,0,0) etc.
  vector <int> slack(old_link.size(), 0);
  
  //jesli byl slackiem i nie jest lub nie byl i jest teraz slackiem - reptation
  if (is_equal(old_link, slack) or is_equal(new_link, slack) )
      return RouseDynamic::REPTATION; 
  
  // jesli miedzy linkiem nowym i starym jest kat 90 stopni - crossing
  if (dot(old_link, new_link) == 0)
      return RouseDynamic::CROSSING; 
  
return RouseDynamic::FORBIDEN; 
}

int RouseDynamic :: get_transition_type_by_links(std::vector < std::vector <int> > &start_links, std::vector < std::vector <int> > &end_links)
{
    int dim = start_links[0].size();
    vector <int> tmp, slack;
    slack.assign(dim,0);
    
    //znajdz linki ktore zmienily sie wskutek transformacji
    vector <int> change_link_idx;
    
    for(int i=0; i<start_links.size(); i++)
    {
        if ( is_equal(start_links.at(i), end_links.at(i)) )   
            continue;
        change_link_idx.push_back(i);
    }
    
    int size = change_link_idx.size();
   
    //jesli nic sie nie zmienilo lub wiecej niz 2 linki - zabronione
    if( size == 0 or size > 2)
        return RouseDynamic::FORBIDEN;
    
    //jesli zmienil sie tylko jeden to czy koncowy
    if ( size == 1 )
    {
        //Trzeba sprawdzic czy na koncach, bo to moga byc dwie dowolne konfiguracje - nawet bledne !!!
        if(change_link_idx.at(0) == 0 or change_link_idx.at(0) == start_links.size()-1) 
        {
            int idx =  change_link_idx.at(0);
            return check_end_link(start_links.at(idx), end_links.at(idx));
        }
        //TODO tutaj chyba moznaby zrobic wyjscie bo jeden link zmienic sie moze tylko na koncu ?
    }
    
    //jesli zmienily sie dwa linki to czy sasiednie 
    if (change_link_idx.at(0) + 1 != change_link_idx.at(1))
        return RouseDynamic::FORBIDEN;
    
    int idx1 = change_link_idx.at(0);
    int idx2 = change_link_idx.at(1);
    
    //REPTATION
    //jeden jest slackim, drugi nie a po przejsciu zamieniaja sie miejscami
    if( is_equal(start_links.at(idx1),slack) and not is_equal(start_links.at(idx2),slack) and is_equal(start_links.at(idx1), end_links.at(idx2)) and is_equal(start_links.at(idx2), end_links.at(idx1)))
        return RouseDynamic::REPTATION;
    
    if( is_equal(start_links.at(idx2),slack) and not is_equal(start_links.at(idx1),slack) and is_equal(start_links.at(idx1), end_links.at(idx2)) and is_equal(start_links.at(idx2), end_links.at(idx1)))
        return RouseDynamic::REPTATION;

     //HERNIA
    //sa dwa slacki a po tranformacji dwa linki przeciwstawne - Tworzenie herni
    
    if (is_equal(start_links.at(idx1), slack) and is_equal(start_links.at(idx2), slack) and is_opposite(end_links.at(idx1), end_links.at(idx2)))
        return RouseDynamic::HERNIA;
    
    //dwa przeciwstawne a po pzejsciu dwa slacki - Anihilacja herni
    if (is_equal(end_links.at(idx1), slack) and is_equal(end_links.at(idx2), slack) and is_opposite(start_links.at(idx1), start_links.at(idx2)))
        return RouseDynamic::HERNIA;
    
    //CROSSING (ale nie polozona hernia)
    //sa dwa prospodale linki (nie sa slackami) a po przejsciu zamieniaja sie miejscami
    if ( not is_equal(start_links.at(idx1),slack) and not is_equal(start_links.at(idx2),slack) and dot(start_links.at(idx1), start_links.at(idx2)) == 0 and is_equal(start_links.at(idx1), end_links.at(idx2)) and is_equal(start_links.at(idx2), end_links.at(idx1)) )
        return RouseDynamic::CROSSING;
        
    //jesli cos zostalo - zabronione
    return RouseDynamic::FORBIDEN;
}

