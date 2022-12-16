# detected_OS := $(shell sh -c 'uname -s 2>/dev/null || echo not')

all: install start

test:
	$(MAKE) -C tests

clean:
	$(MAKE) -C tests clean

install:
	cmake -B"build" -H"build"
	$(MAKE) -C build
	mv build/calc app

start:
	./app/calc

uninstall:
	rm -rf app/calc
	rm -rf build-*
	rm -rf build/cmake_install.cmake
	rm -rf build/CMakeCache.txt
	rm -rf build/CMakeFiles
	rm -rf build/Makefile
	rm -rf build/calc_autogen
	rm -rf build/calc.app
	rm -rf app/calc
	rm -rf build/CMakeLists.txt.user
	rm -rf build/.cmake
	rm -rf build/calc.cbp
	rm -rf build-build-Desktop-Debug
