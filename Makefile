#compiler:
CC = g++ -Wall -ansi

all: project

project:
	$(CC) -o project project.cpp


clean: 
	rm -f ./project