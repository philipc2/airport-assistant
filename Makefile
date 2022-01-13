EXENAME = finalproj
OBJS = main.o parser.o Dijkstra.o BFS.o pagerank.o airport.o

LD = clang++ 
FILES = Dijkstra.cpp  BFS.cpp  airport.cpp pagerank.cpp parser.cpp

.PHONY: all test clean output_msg

all: $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME): output_msg $(OBJS)
	$(LD) $(OBJS) -o $(EXENAME) 

main.o: main.cpp parser.cpp  Dijkstra.cpp BFS.cpp pagerank.cpp  airport.cpp
	clang++ -c  main.cpp

parser.o: parser.cpp airport.cpp
	clang++ -c parser.cpp airport.cpp 

Dijkstra.o: Dijkstra.cpp BFS.cpp  airport.cpp
	clang++ -c  Dijkstra.cpp

BFS.o: BFS.cpp airport.cpp
	clang++ -c  BFS.cpp

pagerank.o: pagerank.cpp airport.cpp
	clang++ -c  pagerank.cpp 

airport.o: airport.cpp
	clang++ -c  airport.cpp

test: output_msg catchmain.cpp testcases.cpp $(FILES)
	$(LD) catchmain.cpp testcases.cpp $(FILES) $(LDFLAGS) -o test
clean:
	 -rm -f *.o $(EXENAME) test

