#include <vector>
#include <cmath>
#include "../include/tools.h"
#include "../include/polymer.h"
#include "../include/translation.h"
#include "../include/dynamic.h"
#include "../include/system.h"
#include "../include/analyser.h"

#include <iostream>

using std::vector;
using std::string;
using std::log;
using std::exp;

void Analyser::analyse(long step, Polymer *old_polymer, Polymer * new_polymer, const std::vector <double> data)
{
  //TODO: tutaj idzie kod ktory ma cos sobie obliczać
 std::cout <<"Krok aktualny "<<step<<" \n";
 std::cout <<"Stara konfig. "<<old_polymer->get_representation()<<"  \n";
 std::cout <<"Nowa konfig.  "<<new_polymer->get_representation()<<"  \n\n\n";
 
}
            
StateProbability::StateProbability()
{
   counter = 0;
   clear_histogram();   
}

void StateProbability::clear_histogram()
{
  for(int i=0; i<SIZE; i++)
      this->hist[i] = 0;
}


void StateProbability::analyse(long step, Polymer *old_polymer, Polymer * new_polymer, const std::vector <double> data)
{
 state = new_polymer->get_representation();
 for(int j=0 ; j< SIZE; j++)
 {
    if (states[j] == state)
    {
      hist[j] = hist[j] + 1;
       break;
    }
  }
 counter = counter + 1;
}

const string StateProbability::states[SIZE] = {"sss", "ssu", "ssr","ssd", "ssl", "sus", "suu", "sur", "sud", "sul",
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
