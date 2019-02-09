PROGS = EF2D

all:$(PROGS)
	
EF2D:EF2D.o EF2d-base.o GC.o 
	$(CXX) $^ -o $@ $(CXXFLAGS) $(LDFLAGS) $(LIBS) 
clean:
		-rm -r $(PROGS) *.o *.dDSYM gp 
# les dependances 
EF2D.o: EF2d-base.hpp R2.hpp GC.hpp 
EF2d-base.o: EF2d-base.hpp R2.hpp GC.hpp
GC.o:GC.hpp		