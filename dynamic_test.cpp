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



void test_KMC(int dim, long steps)
{
  //testujemy wszystkei mozliwe translacje 
  SecondNearestNeighbour trans_obj(dim);
  // parametry pisują "rate" przejść
  // pierwszy - reptation
  // drugi - hernia
  // rzeci - crossing barrier
  // czwarty - hernia migration
  RouseDynamic rouse(1.0, 0.2, 0.2, 0.2, dim);
  //rodzaj symulacji - pste, zwykłe Kinetic MC, zaczynamy od konfiguraji "sss" - bo niezależna od wymiarowości 1D czy 2D
  
  KMCSimulationSystem s1("sss", &trans_obj, &rouse);
  
  //predefiniowane stany do testow
   int size = 81;

  //81 stanów - 1D dla  4 linków, czyli 5 repronów
  // UWAGA !!!! - trzeba zmenić wtedy stan początkowy  w KMCSimulationSystem !!!!!!!!!!!!
   
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
  // 125 stanow - 2D dla 3 linków - 4 reptony
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
    
  //tablica pelniaca role histogramu
  int hist[size];
  for(int i=0; i<size; i++)
      hist[i]= 0;
      
  vector <int> tmp;
  
  //termalizacja -  162 000 krokow wybrane tak sobei bez zadnej argumentacji
  long term_steps = 162000;
  //petla termalizacyjna - proste trzy operacje - 
  // 1. wybierz (wylosuj zgodnie z KMC) dopuszczalną translacje
  // 2. przesun repron zgodnie z wylosowanymi parametram
  // 3. wroc do pkt.1
  for(long i=0; i<term_steps; i++)
  { 
    tmp = s1.choose_transition();
    s1.move_repton(tmp.at(0), tmp.at(1));
  }
  
  //zasadnicze KMC po termalizacji
  long iter=steps;
  //potrezbujemy reprezentacji stanu żeby zliczać prawdopodobieństwa
  string stan ;
  //petla analogiczna jak przy termalizacjia, ale zliczamy pojawiające sie stany
  for(long i=0; i<iter; i++)
  {
    stan = s1.polymer->get_representation();
    for(int j=0 ; j< size; j++)
    {
       if (stany[j] == stan)
       {
           hist[j] = hist[j] + 1;
           break;
       }
    }    
        
    tmp = s1.choose_transition();
    s1.move_repton(tmp.at(0), tmp.at(1));
  }
  
  //wypisza satni i ich prawdopodobienstwa na ekran
  for(int i=0; i<size; i++)
  {
    cout << stany[i]<<"   "<<double(hist[i])/iter<<endl;
  }
}
  
main()
{
 srand(time(NULL));
 long steps = 4000000;
 //UWAGA tutaj pierszy parametr to wymiarowoc ukladu ! Musi to byc dobrze zgrane z kodem w funkcji bo 
 //nic automatycznie sie tem nie dzieje, wiec zmian atutaj powoduje koniecznosc reczbych zmian tam
 test_KMC(2, steps);
 return 0;
}


