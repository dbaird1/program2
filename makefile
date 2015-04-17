COMPILER = g++
FLAGS = -g -Wall -std=c++0x
EXECUTABLE = lab5
all: lab5.o
	$(COMPILER) $(FLAGS) -o $(EXECUTABLE) lab5.o
lab5.o: lab5.cpp
	$(COMPILER) $(FLAGS) -c lab5.cpp
clean:
	rm -f $(EXECUTABLE) *.o
