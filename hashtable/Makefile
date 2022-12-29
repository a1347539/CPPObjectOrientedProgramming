CPPFLAGS = -std=c++11

all: out.exe

out.exe: doubleHashingHashTable.o linearProbingHashTable.o openAddressingHashTable.o quadraticProbingHashTable.o shop.o main.o
	g++ -o $@ $(CPPFLAGS) doubleHashingHashTable.o linearProbingHashTable.o openAddressingHashTable.o quadraticProbingHashTable.o shop.o main.o

%.o: %.cpp
	g++ $(CPPFLAGS) -c $< -o $@ 

clean:
	del *.o *.exe
# On Windows, use: del *.o *.exe
# On Linux or MacOS, use: rm -f *.o *.exe