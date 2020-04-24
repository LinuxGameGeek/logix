all: logix

WARNINGS = -Wall
DEBUG = -ggdb -fno-omit-frame-pointer
OPTIMIZE = -O2
CXX = g++
CXXFLAGS =  $(WARNINGS) $(DEBUG) $(OPTIMIZE)
GTKFLAGS = `pkg-config gtkmm-3.0 --cflags --libs`
INCLUDES = -I./src
LIBS = -lm -lepoxy

logix: logix.o ui.o renderer.o
	$(CXX) $(GTKFLAGS)  $(LIBS) logix.o ui.o renderer.o -o logix

logix.o: ./src/logix.cpp
	$(CXX) $(GTKFLAGS) -c $(CXXFLAGS) ./src/logix.cpp $(LIBS)

ui.o: ./src/ui.cpp
	$(CXX) $(GTKFLAGS) -c $(CXXFLAGS) ./src/ui.cpp $(LIBS)

renderer.o: ./src/renderer.cpp
	$(CXX) $(GTKFLAGS) -c $(CXXFLAGS) ./src/renderer.cpp $(LIBS)

clean:
	rm -f ./logix ./logix.o ./ui.o ./renderer.o

install:
	echo "Installing is not supported"

run:
	./logix
