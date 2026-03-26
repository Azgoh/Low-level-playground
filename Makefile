CXX = g++
FLAGS = -ggdb -Wall

main: gilpin.cc
	${CXX} ${FLAGS} -o bin/gilpin gilpin.cc

clean:
	rm -f gilpin