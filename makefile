main:
	g++ -o programa main.cpp -std=c++14 && ./programa
main2:
	g++ -o programa main2.cpp functions.cpp -std=c++14 && ./programa
rm:
	rm *.txt *.exe
