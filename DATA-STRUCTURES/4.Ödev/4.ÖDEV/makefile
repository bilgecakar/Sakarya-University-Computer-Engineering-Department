hepsi: derle calistir
Nesneler :=  ./lib/huffman.o ./lib/Node.o

derle:
	g++ -I ./include/ -o ./lib/huffman.o -c ./src/huffman.cpp
	g++ -I ./include/ -o ./lib/Node.o -c ./src/Node.cpp
	g++ -I ./include/ -o ./bin/Source $(Nesneler) ./src/Source.cpp
	
calistir:
	./bin/Source