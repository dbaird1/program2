COMPILER = g++
FLAGS = -g -Wall -std=c++0x
EXECUTABLE = memgen
all: memgen.o
	$(COMPILER) $(FLAGS) -o $(EXECUTABLE) memgen.o
memgen.o: memgen.cpp
	$(COMPILER) $(FLAGS) -c memgen.cpp
clean:
	rm -f $(EXECUTABLE) *.o
