
FLAGS:=-lgtest -lpthread  -fprofile-arcs #-ftest-coverage

all: test

build:
	g++ ../controller/*.cpp ../model/*.cpp tests.cpp -pthread -lgtest -o test

test: build
	./test

gcov_report: test
	gcovr --html --html-details -o report/coverage_report.html

debug:
	g++ ../controller/*.cpp ../model/*.cpp main.cpp -pthread -lgtest
	./a.out

valgrind:
	valgrind ./test

clean:
	rm -rf *.o
	rm -rf *.gc*
	rm -rf *.a
	rm -rf test
	rm -rf a.out
	rm -rf report/*
