dog_program : dog.o main.o
	g++ -std=c++17 dog.o main.o -o dog_program

dog.o : dog.cpp dog.hpp
	g++ -std=c++17 -c dog.cpp

main.o : main.cpp
	g++ -std=c++17 -c main.cpp

clean : 
	rm -f dog_program *.o
