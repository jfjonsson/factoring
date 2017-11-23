all:
	g++ factoring.cpp -lgmpxx -lgmp -I/usr/local/include/ -L/usr/local/lib/ -Wall -o FACTORING
windows: 
	g++ factoring.cpp -lgmpxx -lgmp -o FACTORING.exe
