all:
	g++ factoring.cpp -lgmpxx -lgmp -I/usr/local/include/ -L/usr/local/lib/ -o FACTORING
windows: 
	-g++ -Wextra -O2 -std=gnu++11  *.cpp -o FACTORING
