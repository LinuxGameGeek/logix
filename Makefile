all: logix

WARNINGS = -Wall
DEBUG = -ggdb -fno-omit-frame-pointer
OPTIMIZE = -O2
CXX = g++
CXXFLAGS =  $(WARNINGS) $(DEBUG) $(OPTIMIZE)
GTKFLAGS = `pkg-config gtkmm-3.0 --cflags --libs`
INCLUDES = -I./src -I/src/viewport
LIBS = -lm -lepoxy

logix: logix.o ui.o renderer.o shader.o vertexbuffer.o indexbuffer.o
	$(CXX) $(GTKFLAGS)  $(LIBS) logix.o ui.o renderer.o shader.o vertexbuffer.o indexbuffer.o -o logix

logix.o: ./src/logix.cpp
	$(CXX) $(GTKFLAGS) -c $(CXXFLAGS) ./src/logix.cpp $(LIBS)

ui.o: ./src/ui.cpp
	$(CXX) $(GTKFLAGS) -c $(CXXFLAGS) ./src/ui.cpp $(LIBS)

renderer.o: ./src/renderer.cpp
	$(CXX) $(GTKFLAGS) -c $(CXXFLAGS) ./src/renderer.cpp $(LIBS)

shader.o: ./src/viewport/shader.cpp
	$(CXX) -c $(CXXFLAGS) ./src/viewport/shader.cpp $(LIBS)

vertexbuffer.o: ./src/viewport/vertexbuffer.cpp
	$(CXX) -c $(CXXFLAGS) ./src/viewport/vertexbuffer.cpp $(LIBS)

indexbuffer.o: ./src/viewport/indexbuffer.cpp
	$(CXX) -c $(CXXFLAGS) ./src/viewport/indexbuffer.cpp $(LIBS)

clean:
	rm -f ./logix ./logix.o ./ui.o ./renderer.o

install:
	echo "Installing is not supported"

run:
	./logix
