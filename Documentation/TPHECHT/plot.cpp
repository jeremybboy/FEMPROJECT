#include "EF2d-base.hpp"
#include <fstream>
#include <vector>
#include <cmath> 
using namespace std; 



int main(int argc,const char ** argv)
{
    assert( argc>1);
    Mesh2d Th(argv[1]);
     {
        ofstream of("gp");
        for(int k=0; k<Th.nt;++k)
        {
            R2 G= ((R2) Th[k][0] + Th[k][1] + Th[k][2])/3.;
            of << G << " "<< k << "\n\n\n";
            for(int ip=0; ip<=3;++ip)
            {
                int i3=ip%3;
                int i = Th(k,i3);
                of << (R2) Th[k][i3] << " " << i << endl;
            }
            of << "\n\n";
        }
    }

     return 0;
}
