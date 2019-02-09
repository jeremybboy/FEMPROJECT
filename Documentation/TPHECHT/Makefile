PROGS = plot
CXXFLAGS = -std=c++11 -O3 
	
all:$(PROGS)
	
plot:plot.o EF2d-base.o
	$(CXX) $^ -o $@ $(CXXFLAGS) $(LDFLAGS) $(LIBS) 
arete:arete.o EF2d-base.o
	$(CXX) $^ -o $@ $(CXXFLAGS) $(LDFLAGS) $(LIBS)
arete-map:arete-map.o EF2d-base.o
	$(CXX) $^ -o $@ $(CXXFLAGS) $(LDFLAGS) $(LIBS)
arete-sort:arete-sort.o EF2d-base.o
	$(CXX) $^ -o $@ $(CXXFLAGS) $(LDFLAGS) $(LIBS)
clean:
		-rm -r $(PROGS) *.o *.dDSYM gp 
# les dependances 
#plot.o:: EF2d-base.hpp R2.hpp 
#EF2d-base.o:: EF2d-base.hpp R2.hpp 
	