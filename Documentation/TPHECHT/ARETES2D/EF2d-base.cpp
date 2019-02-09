#include "EF2d-base.hpp"
#include <fstream>

Mesh2d::Mesh2d(const char * filename)
{
  std::ifstream  f(filename); 
  assert( f); 
  int unused, I[4] ; 
  f >> nv >> nt >> unused ;
  assert( f.good());
  t = new Simplex[nt];
  v = new Vertex[nv];
  assert( t && v); 
  double mes =0; 
  for(int i=0;i<nv;++i)
    { 
      f >> v[i] ; 
      assert( f.good());
    }

  for(int k=0;k<nt;++k)
    { 
      for(int i=0;i< 4; ++i)
	f >> I[i] ; 
      assert( f.good());
      t[k].build(v,I,-1);
      mes += t[k].mes; 
    }
  std::cout<< " End read " << nv << " " << nt << " mes =" << mes << std::endl; 
}
