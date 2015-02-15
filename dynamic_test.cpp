#include <iostream>
#include <vector>

#include "include/tools.h"
#include "include/polymer.h"
#include "include/translation.h"
#include "include/dynamic.h"

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

main()
{
    
    
 Polymer tab[] = {Polymer("ss",1), Polymer("sr",1), Polymer("sl",1),
                  Polymer("rs",1), Polymer("rr",1), Polymer("rl",1), 
                  Polymer("ls",1), Polymer("lr",1),Polymer("ll",1)};
 
for(int i=0; i< 9; i++)
    check_trans(tab[i]); 
 
 return 0;
}


