#include "EF2d-base.hpp"
#include <fstream>
#include "GC.hpp"
#include <vector>
#include <cmath> 
using namespace std; 

struct MatLap : public MatVirt
{
    const Mesh2d & Th;
    const double alpha, beta;
    
    MatLap(Mesh2d & TTh,R a, R b):MatVirt(TTh.nv),Th(TTh),alpha(a), beta(b)
    {}
    double * addmatmul(double *x,double *Ax) const {
        R2 g[3];
        double alpha12= alpha/12.;
        for(int k=0; k< Th.nt;++k)
        {
            const  Simplex & K= Th[k];
            K.GradLambdaK(g);
            double mes = K.mes;
            int iK[3]={Th(K[0]),Th(K[1]),Th(K[2])};
            for(int ip=0; ip<3;++ip)
                for(int jp=0; jp<3;++jp)
                {  double aKij = mes*(  alpha12*(1+(ip==jp))
                                      + beta*(g[ip],g[jp]) ) ;
                    int i = iK[ip], j=iK[jp];
                    if( ! K[ip].OnGamma())
                        Ax[i] += aKij*x[j];
                    
                }
        }
        return Ax;}
};
R aa = M_PI*1, bb= M_PI*2;
R ue(R2 & P) {return sin(aa*P.x)*sin(bb*P.y);}
R f(R2 &P){return (aa*aa+bb*bb)*sin(aa*P.x)*sin(bb*P.y);}
R g(R2 &P){return 0;}

int main(int argc,const char ** argv)
{
    assert( argc>1);
    Mesh2d Th(argv[1]);
    // Voila la fin du program++
    // avec verification
    int n = Th.nv;
    MatLap A(Th,0,1);
    MatLap M(Th,1,0);
    MatIdentite Id(n);
    vector<double> u(n),b(n),fh(n),ueh(n);
    for(int i=0; i<n; ++i)
        fh[i] = f(Th.v[i]);
    for(int i=0; i<n; ++i)
        ueh[i] = ue(Th.v[i]);
    for(int i=0; i<n; ++i)
        if( Th.v[i].OnGamma() )
            u[i] = g(Th.v[i]);
        else
            u[i]=0;
    
    ProduitMatVec(M,&fh[0],&b[0]);
    int ok=GradientConjugue(A,Id,&b[0], &u[0], n, 1e-8, 10);
    cout << " Ok = " << ok << endl;
    {
        ofstream of("gp");
        for(int k=0; k<Th.nt;++k)
        {
            for(int ip=0; ip<=3;++ip)
            {
                int i3=ip%3;
                int i = Th(k,i3);
                of << (R2) Th[k][i3] << " "<< u[i] << " "<< ueh[i] << endl;
            }
            of << "\n\n";
        }
    }
    return 0;
}
