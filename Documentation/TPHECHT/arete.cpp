#include "EF2d-base.hpp"
#include <fstream>
#include <vector>

#include <cmath>


using namespace std; 



int main(int argc,const char ** argv)
{
    assert( argc>1);
    Mesh2d Th(argv[1]);
    vector<int>  head(Th.nv,-1),next(Th.nt*3),v0(Th.nt*3),v1(Th.nt*3),ta(Th.nt*3),
    tadj(Th.nt*3,-1);
    int nba =0;
    for(int k=0; k<Th.nt; ++k)
        for(int a=0; a<3; ++a)
            {
                int il0 = (a+1)%3;
                int il1 = (a+2)%3;
                int i0 = Th(k,il0);
                int i1 = Th(k,il1);
                if(i0>i1) swap(i0,i1);
                bool exist = false;
                int na=-1;
                for (na=head[i0];na!= -1;na=next[na])
                {
                    assert( v0[na]==i0 );
                    if(v1[na]==i1) {exist=1; break;}
                }
                if( !exist)
                {// nouvelle arete
                    v0[nba] = i0;
                    v1[nba] = i1;
                    ta[nba] = 3*k +a;
                    next[nba] = head[i0];
                    head[i0] = nba;
                    nba++;
                }
                else
                {
                    int kk = ta[na]/3, aa = ta[na]%3;
                    // k,a  <=> kk, aa
                    tadj[kk*3+aa]=k*3+a;
                    tadj[k*3+a]=kk*3+aa;

                }
            }
    
    cout << " nba =" << nba  << endl;
     return 0;
}
