hepsi: derle calistir
Nesneler :=  ./lib/Karakter.o ./lib/Node.o ./lib/Stack.o 

derle:
	g++ -I ./include/ -o ./lib/Karakter.o -c ./src/Karakter.cpp
	g++ -I ./include/ -o ./lib/Node.o -c ./src/Node.cpp
	g++ -I ./include/ -o ./lib/Stack.o -c ./src/Stack.cpp
	g++ -I ./include/ -o ./bin/Main $(Nesneler) ./src/Main.cpp
	
calistir:
	./bin/Main