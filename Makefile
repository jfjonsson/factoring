all:
	g++ factoring.cpp -Wall -lgmpxx -lgmp -I/usr/local/include/ -L/usr/local/lib/ -o FACTORING -std=c++11
windows: 
	g++ factoring.cpp -lgmpxx -lgmp -o FACTORING.exe
