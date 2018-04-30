CXX = g++
CXXFLAGS = -std=c++17 -Wall
OBJECTS = port.o block.o blockArithmetic.o

icp: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f *.o icp

$(OBJECTS): port.h block.h blockArithmetic.h
