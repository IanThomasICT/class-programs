output : main.o
	g++ -Wall -Wextra main.o -o output

main.o : main.cpp Car.hpp RentalManagement.hpp
	g++ -Wall -Wextra -c main.cpp

clean :
	rm *.o output