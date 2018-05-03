CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
OBJECTS = blocks/port.o blocks/block.o blocks/blockArithmetic.o blocks/blockLogic.o blocks/scheme.o


all: compile

compile: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o ../blockeditor $^

$(OBJECTS): blocks/port.h blocks/block.h blocks/blockArithmetic.h blocks/blockLogic.h blocks/scheme.h
