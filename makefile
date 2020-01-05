doublets: doublets.o main.o
	g++ -Wall -g doublets.o main.o -o doublets

doublets.o: doublets.cpp doublets.h
	g++ -Wall -c doublets.cpp -O3

main.o: main.cpp doublets.h
	g++ -Wall -c main.cpp -O3