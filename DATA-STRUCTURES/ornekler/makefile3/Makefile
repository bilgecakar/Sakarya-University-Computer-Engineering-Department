hepsi:derle test
derle:
	g++ -I./include -c ./src/islem.cpp -o ./lib/islem.o
	g++ -I./include -o ./bin/uyg1 ./src/uyg1.cpp  ./lib/islem.o
test:
	./bin/uyg1
temizle:
	del .\lib\islem.o
	del .\bin\uyg1.exe