PROGS = EF3D
CXXFLAGS = -std=c++11 -O3 
	
all:$(PROGS)
	
EF2D:EF3D.o EF3d-base.o GC.o 
	$(CXX) $^ -o $@ $(CXXFLAGS) $(LDFLAGS) $(LIBS) 
clean:
		-rm -r $(PROGS) *.o *.dDSYM gp 
# les dependances 
EF3D.o: EF3d-base.hpp R3.hpp GC.hpp 
EF3d-base.o: EF3d-base.hpp R3.hpp GC.hpp
GC.o:GC.hpp		