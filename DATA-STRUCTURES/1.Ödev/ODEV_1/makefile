hepsi: derle calistir
Nesneler :=  ./lib/Vektor.o ./lib/Yolcu.o ./lib/Otobus.o 

derle:
	g++ -I ./include/ -o ./lib/Vektor.o -c ./src/Vektor.cpp
	g++ -I ./include/ -o ./lib/Otobus.o -c ./src/Otobus.cpp
	g++ -I ./include/ -o ./lib/Yolcu.o -c ./src/Yolcu.cpp
	g++ -I ./include/ -o ./bin/Main $(Nesneler) ./src/Main.cpp
	
calistir:
	./bin/Main