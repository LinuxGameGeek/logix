all: logix

WARNINGS = -Wall
DEBUG = -ggdb -fno-omit-frame-pointer
OPTIMIZE = -O2
CXX = g++
CXXFLAGS =  $(WARNINGS) $(DEBUG) $(OPTIMIZE)
LIBS=

logix: logix.o
	$(CXX) $(LIBS) logix.o -o logix

logix.o: ./src/logix.cpp
	$(CXX) -c $(CXXFLAGS) ./src/logix.cpp
#logix.o: logix.cpp

clean:
	rm -f ./logix ./logix.o

run:
	./logix
