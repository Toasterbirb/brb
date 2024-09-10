all: playground unit_test unit_test_optimized

CXXFLAGS=-Wno-builtin-declaration-mismatch -nostdlib -nostdlib++ -nodefaultlibs -fno-exceptions -I../include
#-fno-stack-protector  # add this back in if things break

playground: ./playground.cpp ../brb.a
	g++ ${CXXFLAGS} -O0 -g -o $@ $^

unit_test: ./unit_test.cpp ../brb.a
	g++ ${CXXFLAGS} -O0 -g -o $@ $^

unit_test_optimized: ./unit_test.cpp ../brb.a
	g++ ${CXXFLAGS} -DNDEBUG -O1 -o $@ $^

clean:
	rm -f ./playground ./unit_test ./unit_test_optimized

.PHONY: clean
