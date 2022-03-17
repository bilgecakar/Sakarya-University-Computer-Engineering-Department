hepsi: derle calistir
Nesneler :=  ./lib/BST.o ./lib/Liste.o ./lib/Node.o 

derle:
	g++ -I ./include/ -o ./lib/BST.o -c ./src/BST.cpp
	g++ -I ./include/ -o ./lib/Liste.o -c ./src/Liste.cpp
	g++ -I ./include/ -o ./lib/Node.o -c ./src/Node.cpp
	g++ -I ./include/ -o ./bin/Source $(Nesneler) ./src/Source.cpp
	
calistir:
	./bin/Source