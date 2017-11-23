all:
	g++ factoring.cpp -Wall -lgmpxx -lgmp -I/usr/local/include/ -L/usr/local/lib/ -o FACTORING
windows: 
	g++ factoring.cpp -lgmpxx -lgmp -o FACTORING.exe
