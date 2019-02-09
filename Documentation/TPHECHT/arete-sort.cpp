#include "EF2d-base.hpp"
#include <fstream>
#include <vector>
#include <list>
#include <cmath>


using namespace std; 



int main(int argc,const char ** argv)
{
    assert( argc>1);
    Mesh2d Th(argv[1]);
    vector<pair<int,int> > lesaretes;
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
                lesaretes.push_back(p);
            }
    
    sort(lesaretes.begin(),lesaretes.end());
    int k=1;
    for(int i=1; i<lesaretes.size(); ++i )
        if( lesaretes[i]!=lesaretes[i-1])
            lesaretes[k++]=lesaretes[i];
    lesaretes.resize(k);
    for(auto i=lesaretes.begin(); i!=lesaretes.end();++i)
        cout << i-lesaretes.begin() << " "<< (*i).first << " " << i->second<<endl;
    cout << " nba =" << nba << " " <<lesaretes.size() << endl; 
     return 0;
}
