
q: clean test valgrind

all: gcov_report valgrind

gcov_report: testg
	gcovr -r ../ --html --html-details -o report/coverage_report.html


testg:
	g++ -std=c++17 -pthread tests.cpp ../controller/*.cpp ../model/*.cpp --coverage -lgtest_main -lgtest -lpthread -lgcov -o testg
	./testg

test:
	g++ -std=c++17 -pthread tests.cpp ../controller/*.cpp ../model/*.cpp -lgtest_main -lgtest -lpthread -lgcov -o test
	./test

valgrind:
	valgrind ./test

clean:
	rm -rf *.o *.gc* *.a test testg a.out report/*

