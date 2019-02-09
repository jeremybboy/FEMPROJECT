#include "R2.hpp"
#include <cassert>

class Label {
public:
  int lab; 
  int  OnGamma() const { return lab;}
  Label(int l=0) : lab(l) {} 
};

class Vertex :public R2,public  Label
{
 public:
  Vertex() {}   
};

inline std::ostream& operator <<(std::ostream& f, const  Vertex & P )
{ return  f << P.x << ' ' << P.y  << ' ' << P.lab << ' ' ;}
inline  std::istream& operator >>(std::istream& f,  Vertex & P)
{ return f >>  P.x >>  P.y >> P.lab ;  }

class Simplex {
public: 
  static const int nbv =3; 
  Vertex * v[nbv]; 
  double mes;
  Simplex(){ (v[0]=(v[1]=(v[2]=0)));}
  void build(Vertex *v0,int * I,int offset=0)
  {// I array of vertex number  
    for(int i=0; i < nbv; ++i) 
      v[i] =  v0 + I[i]+offset; 
    mes = det(*v[0], *v[1], *v[2]) * 0.5; 
    assert(mes>0) ;
  } 
  void GradLambdaK(R2 *G) const
  {
    double K2 = mes*2; 
    G[0] = R2(*v[1],*v[2]).perp()/K2;
    G[1] = R2(*v[2],*v[0]).perp()/K2;
    G[2] = R2(*v[0],*v[1]).perp()/K2;
  }
  
  Vertex & operator[](int i) { assert(i>=0 && i < nbv); return *(v[i]); }
  const Vertex & operator[](int i) const { assert(i>=0 && i < nbv); return *(v[i]); }

};  

class Mesh2d 
{
public:
  int nv,nt; 
  Vertex * v; 
  Simplex *t;
  Mesh2d(const char *  filename); 
  ~Mesh2d() { delete [] v; delete [] t; }
  // destuctor => careful with copie operator  
  // no copy operator
  // chech index number
  int CheckV(int i) const { assert( i>=0 && i < nv); return i; } 
  int CheckT(int i) const { assert( i>=0 && i < nt); return i; } 
  int operator()(const Vertex & vv) const { return CheckV(&vv-v);}
  int operator()(const  Simplex & tt) const  { return CheckT(&tt-t);}
  int operator()(const Vertex * vv)const  { return CheckV(vv-v);}  // (1)
  int operator()(const  Simplex * tt) const { return CheckT(tt-t);}
  Simplex & operator[](int k) { return t[CheckT(k)]; }
  const Simplex & operator[](int k) const { return t[CheckT(k)]; }
  int  operator()(int k,int i) const { return  operator()(t[k].v[i]); }// call (1)

private:
  Mesh2d(const Mesh2d &);
  Mesh2d & operator=(const Mesh2d &);
 
};
