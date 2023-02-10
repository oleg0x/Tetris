CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra

TARGET = tetris
OBJ = bits4x4.o figure.o field.o tetris.o main.o

.PHONY: all clean  # prevent make from confusing the phony target with a file name

all: $(TARGET)

clean:
	rm -rf $(TARGET) *.o

re: clean all

bits4x4.o: bits4x4.h bits4x4.cpp

figure.o: bits4x4.h bits4x4.cpp figure.h figure.cpp
	$(CXX) $(CXXFLAGS) -c figure.cpp

field.o: field.h field.cpp
	$(CXX) $(CXXFLAGS) -c field.cpp

tetris.o: figure.h figure.cpp field.h field.cpp tetris.h tetris.cpp
	$(CXX) $(CXXFLAGS) -c tetris.cpp

main.o: tetris.h main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -lncurses -o $(TARGET) $(OBJ)
