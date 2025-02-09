.PHONY: run compile

run: compile
	./main

compile: main.cpp
	g++ -std=c++17 -o main main.cpp
