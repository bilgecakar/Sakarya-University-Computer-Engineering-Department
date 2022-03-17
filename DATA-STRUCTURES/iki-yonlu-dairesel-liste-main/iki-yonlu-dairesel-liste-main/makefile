all:compile link run

compile:
	g++ -I./include -c ./src/ListeDugumu.cpp -o ./lib/listedugumu.o
	g++ -I./include -c ./src/Liste.cpp -o ./lib/liste.o
	g++ -I./include -c ./src/main.cpp -o ./lib/main.o
	
link:
	g++      ./lib/listedugumu.o ./lib/liste.o ./lib/main.o -o ./bin/MyProgram.exe
run:
	./bin/MyProgram