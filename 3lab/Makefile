main: main.o lab_3.o
	g++ -o main main.o lab_3.o
main.o: main.cpp lab_3.h
	g++ -c main.cpp
lab_3.o: lab_3.cpp lab_3.h
	g++ -c lab_3.cpp
clean:
	rm -f *.o main
