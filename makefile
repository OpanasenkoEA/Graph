all: main_gpaph.cpp
	g++ -o main_test.exe -std=c++17 main_graph.cpp 
clean:
	rm *.o
