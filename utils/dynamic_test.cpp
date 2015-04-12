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


void check_trans(Polymer &p)
{
    NearestNeighbour trans_obj(p.get_dim());
    RouseDynamic rouse(0.1, 0.2, 0.3, 0.4, p.get_dim());
 
    Polymer p_tmp(p.get_nreptons(), 0);
    vector< int>  tmp;
    
    int type;
    cout <<"Start : "<<p.get_representation()<<endl;
    
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
                  cout <<"  --- > :  "<<p_tmp.get_representation()<<"  " <<type<<"   "<< rouse.get_transition_rate(type) << endl;
            }
        }
    }
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

vector <string> generate_all_states(int nlink)
{
  string base="srudl", start="";
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


void generowanie_macierzy_test(int nlinks)
{
    vector <string> test;
    test = generate_all_states(nlinks);
    
    
    for(int i=0; i< test.size(); i++)
    {
        Polymer p(test.at(i), 1);
        check_trans(p);
    }
    
}

int  test_system(int dim)
{
  NearestNeighbour trans_obj(dim);
  RouseDynamic rouse(0.1, 0.2, 0.3, 0.4, dim);
  
  //TestSimulationSystem s1(3, &trans_obj, &rouse);
  TestSimulationSystem s1("ssrlslr", &trans_obj, &rouse);
  
  cout <<s1.polymer->get_representation()<<endl;
  
  vector < vector <int> > matrix;
  vector <int> tmp;
  matrix = s1.get_matrix();
  
  tmp = trans_obj.get_translation(0);
  cout <<tmp.at(0)<<endl;
  tmp = trans_obj.get_translation(1);
  cout <<tmp.at(0)<<endl;
  
  for(int i=0; i<matrix.size(); i++)
  {
    cout <<i<<"  : ";
    for(int j=0; j<matrix.at(0).size(); j++)
    {
       cout  <<matrix.at(i).at(j)<<"  ";
    }
    cout <<endl;
  }
 
 int rep_id, trans_id;
 cout <<"Podaj numer reptonu "<<endl;
 cin >> rep_id;
 cout <<"Podaj numer trans "<<endl;
 cin >> trans_id;
 s1.move_repton(rep_id, trans_id);
 
 matrix = s1.get_matrix();
  
 cout <<s1.polymer->get_representation()<<endl; 
  for(int i=0; i<matrix.size(); i++)
  {
    cout <<i<<"  : ";
    for(int j=0; j<matrix.at(0).size(); j++)
    {
       cout  <<matrix.at(i).at(j)<<"  ";
    }
    cout <<endl;
  }
 
  string rep  = s1.polymer->get_representation();
  TestSimulationSystem s2(rep, &trans_obj, &rouse);
  matrix = s2.get_matrix();
  cout <<"--------"<<endl; 
  for(int i=0; i<matrix.size(); i++)
  {
    cout <<i<<"  : ";
    for(int j=0; j<matrix.at(0).size(); j++)
    {
       cout  <<matrix.at(i).at(j)<<"  ";
    }
    cout <<endl;
  }
  
 
}

void test_system_transition(int dim)
{
  NearestNeighbour trans_obj(dim);
  RouseDynamic rouse(0.1, 0.2, 0.3, 0.4, dim);
  
  TestSimulationSystem s1("srr", &trans_obj, &rouse);
  s1.prepare_transision_list();
  cout <<s1.polymer->get_representation()<<endl;
  vector <vector <int> > transitions;
  vector<int> tmp;
  transitions = s1.transitions;
  cout <<"R"<<"  "<<"T"<<endl;
  for(int i=0; i<transitions.size(); i++)
  {
       tmp = transitions.at(i);
       cout << tmp.at(0)<<"  "<<tmp.at(1)<<endl;
  }
  cout <<endl<<endl;
  vector < vector <int> > matrix;
  matrix = s1.get_matrix();
  
  for(int i=0; i<matrix.size(); i++)
  {
    cout <<i<<"  : ";
    for(int j=0; j<matrix.at(0).size(); j++)
    {
       cout  <<matrix.at(i).at(j)<<"  ";
    }
    cout <<endl;
  }
 
  tmp = s1.choose_transition();
  cout << tmp.at(0)<<"  "<<tmp.at(1)<<endl;
  s1.move_repton(tmp.at(0), tmp.at(1));
  cout <<s1.polymer->get_representation()<<endl;
  
}

void test_KMC(int dim)
{
  SecondNearestNeighbour trans_obj(dim);
  RouseDynamic rouse(1.0, 0.2, 0.2, 0.2, dim);
  KMCSimulationSystem s1("sss", &trans_obj, &rouse);
  
  int size = 81;

  /*string stany[] = {"ssss", "sssr", "sssl", "ssrs", "ssrr", "ssrl", "ssls", "sslr", "ssll",
                    "srss", "srsr", "srsl", "srrs", "srrr", "srrl", "srls", "srlr", "srll",
                    "slss", "slsr", "slsl", "slrs", "slrr", "slrl", "slls", "sllr", "slll",
                    "rsss", "rssr", "rssl", "rsrs", "rsrr", "rsrl", "rsls", "rslr", "rsll",
                    "rrss", "rrsr", "rrsl", "rrrs", "rrrr", "rrrl", "rrls", "rrlr", "rrll",
                    "rlss", "rlsr", "rlsl", "rlrs", "rlrr", "rlrl", "rlls", "rllr", "rlll",
                    "lsss", "lssr", "lssl", "lsrs", "lsrr", "lsrl", "lsls", "lslr", "lsll",
                    "lrss", "lrsr", "lrsl", "lrrs", "lrrr", "lrrl", "lrls", "lrlr", "lrll",
                    "llss", "llsr", "llsl", "llrs", "llrr", "llrl", "llls", "lllr", "llll"
                    };
 */
  size = 125;
  string stany[] = {"sss", "ssu", "ssr","ssd", "ssl", "sus", "suu", "sur", "sud", "sul",
                    "srs", "sru", "srr","srd", "srl", "sds", "sdu", "sdr", "sdd", "sdl",
                    "sls", "slu", "slr","sld", "sll",
                    "uss", "usu", "usr","usd", "usl", "uus", "uuu", "uur", "uud", "uul",
                    "urs", "uru", "urr","urd", "url", "uds", "udu", "udr", "udd", "udl",
                    "uls", "ulu", "ulr","uld", "ull",
                    "rss", "rsu", "rsr","rsd", "rsl", "rus", "ruu", "rur", "rud", "rul",
                    "rrs", "rru", "rrr","rrd", "rrl", "rds", "rdu", "rdr", "rdd", "rdl",
                    "rls", "rlu", "rlr","rld", "rll",
                    "dss", "dsu", "dsr","dsd", "dsl", "dus", "duu", "dur", "dud", "dul",
                    "drs", "dru", "drr","drd", "drl", "dds", "ddu", "ddr", "ddd", "ddl",
                    "dls", "dlu", "dlr","dld", "dll",
                    "lss", "lsu", "lsr","lsd", "lsl", "lus", "luu", "lur", "lud", "lul",
                    "lrs", "lru", "lrr","lrd", "lrl", "lds", "ldu", "ldr", "ldd", "ldl",
                    "lls", "llu", "llr","lld", "lll"};
    
  int hist[size];
  for(int i=0; i<size; i++)
      hist[i]= 0;
      
  vector <int> tmp;
  
  for(int i=0; i<62000; i++)
  {
    tmp = s1.choose_transition();
    s1.move_repton(tmp.at(0), tmp.at(1));
  }
  long iter=4000000;
  string stan ;
  for(long i=0; i<iter; i++)
  {
    stan = s1.polymer->get_representation();
    
    for(int j=0 ; j< size; j++)
    {
        if (stany[j] == stan)
            hist[j] = hist[j] + 1;
    }    
        
    tmp = s1.choose_transition();
    s1.move_repton(tmp.at(0), tmp.at(1));
  }
  
  for(int i=0; i<size; i++)
  {
    cout << stany[i]<<"   "<<double(hist[i])/iter<<endl;
  }
}
  
main()
{
 srand(time(NULL));
 //test_system(1);
 //test_system_transition(1);
 test_KMC(2);
 return 0;
}


