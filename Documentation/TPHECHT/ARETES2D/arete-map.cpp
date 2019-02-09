#include "EF2d-base.hpp"
#include <fstream>
#include <vector>
#include <cmath>
#include <map>
#include <set>
using namespace std; 



int main(int argc,const char ** argv)
{
    assert( argc>1);
    Mesh2d Th(argv[1]);
    map< pair<int,int>,int > lesaretes;
    int nba =0;
    for(int k=0; k<Th.nt; ++k)
        for(int a=0; a<3; ++a)
            {
                int il0 = (a+1)%3;
                int il1 = (a+2)%3;
                int i0 = Th(k,il0);
                int i1 = Th(k,il1);
                if(i0>i1) swap(i0,i1);
               
                pair<int,int> p(i0,i1);
                if(lesaretes.find(p)==lesaretes.end() )
                {
                    lesaretes.insert(make_pair(p,nba));
                    lesaretes[p] = nba; // Attention p est toujour insert dans la map. 
                     cout << nba++ << " " << k << " " << a << " : "<< i0 << " "<< i1 <<endl;
                }
            }
    cout << " nba =" << nba << " " <<lesaretes.size() << endl; 
     return 0;
}
