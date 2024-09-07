all: playground unit_test

CXXFLAGS=-g -O0 -fno-stack-protector -Wno-builtin-declaration-mismatch -nostdlib -nostdlib++ -fno-exceptions -I../include

playground: ./playground.cpp ../brb.a
	g++ ${CXXFLAGS} -o $@ $^

unit_test: ./unit_test.cpp ../brb.a
	g++ ${CXXFLAGS} -o $@ $^

clean:
	rm ./playground ./unit_test

.PHONY: clean
