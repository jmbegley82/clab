CXX=g++
CXXFLAGS=-I.
DEPS = Atom.h Node.h Notype.h String.h Integer.h Float.h
OBJ = StrSplit.o Atom.o Node.o Notype.o String.o Integer.o Float.o main.o

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

test: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

clean:
	rm -f *.o *~ test test.exe
