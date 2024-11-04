SHELL = /bin/sh

all: build run

build: target/main

run: build
	./target/main

target:
	mkdir target

target/main: target src/main.cpp
	g++ -ggdb src/main.cpp -o target/main

clean:
	rm -rf target
