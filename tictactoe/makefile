tictactoe.exe : main.o
	g++ -Wall -Wextra main.o -o tictactoe.exe

main.o : main.cpp tictactoe.h
	g++ -Wall -Wextra -c main.cpp

clean : *.o tictactoe.exe
