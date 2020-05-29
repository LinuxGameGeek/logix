all: logix

WARNINGS = -Wall
DEBUG = -ggdb -fno-omit-frame-pointer
OPTIMIZE = -O2 #-Ofast -funroll-loops
CXX = g++ -std=c++17
CXXFLAGS = $(WARNINGS) $(DEBUG) $(OPTIMIZE)
GTKFLAGS = `pkg-config gtkmm-3.0 --cflags --libs`
INCLUDES = -I./src -I/src/viewport
LIBS = -lstdc++fs -lm -lepoxy

logix: logix.o ui.o renderer.o shader.o vertexbuffer.o indexbuffer.o vertexarray.o node.o and.o
	$(CXX) $(LIBS) $(GTKFLAGS) logix.o ui.o renderer.o shader.o vertexbuffer.o indexbuffer.o vertexarray.o node.o and.o -o logix

logix.o: ./src/logix.cpp
	$(CXX) $(GTKFLAGS) -c $(CXXFLAGS) ./src/logix.cpp $(LIBS)

ui.o: ./src/ui.cpp
	$(CXX) $(GTKFLAGS) -c $(CXXFLAGS) ./src/ui.cpp $(LIBS)

renderer.o: ./src/renderer.cpp
	$(CXX) $(GTKFLAGS) -c $(CXXFLAGS) ./src/renderer.cpp $(LIBS)

shader.o: ./src/viewport/shader.cpp
	$(CXX) -c $(CXXFLAGS) ./src/viewport/shader.cpp $(LIBS)

vertexbuffer.o: ./src/viewport/vertexbuffer.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) ./src/viewport/vertexbuffer.cpp $(LIBS)

indexbuffer.o: ./src/viewport/indexbuffer.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) ./src/viewport/indexbuffer.cpp $(LIBS)

vertexarray.o: ./src/viewport/vertexarray.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) ./src/viewport/vertexarray.cpp $(LIBS)

node.o: ./src/viewport/nodes/node.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) ./src/viewport/nodes/node.cpp $(LIBS)

and.o: ./src/viewport/nodes/and.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) ./src/viewport/nodes/and.cpp $(LIBS)
clean:
	rm -f ./logix ./logix.o ./ui.o ./renderer.o ./shader.o ./vertexbuffer.o ./indexbuffer.o ./vertexarray.o ./node.o ./and.o

install:
	echo "Installing is not supported"

run:
	./logix
