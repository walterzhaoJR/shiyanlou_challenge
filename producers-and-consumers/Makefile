main:main.o function.o
	g++ -o main main.o function.o -lpthread

main.o:main.cpp
	g++ -c main.cpp

function.o:function.cpp
	g++ -c function.cpp

clean:
	rm -rf *.o main
