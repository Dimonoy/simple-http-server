SHELL = /bin/sh

all: build-debug
	./target/debug/main

build-debug: target/debug/main

build-release: target/release/main

target/debug:
	mkdir -p target/debug

target/release:
	mkdir -p target/release

target/debug/main: target/debug src/main.cpp
	g++ \
		-ggdb \
		-Wall \
		-Wextra \
		-Wconversion \
		-Wsign-conversion \
		-Weffc++ \
		src/main.cpp \
		-o target/debug/main

target/release/main: target/release src/main.cpp
	g++ -O2 src/main.cpp -o target/release/main

clean:
	rm -rf target
