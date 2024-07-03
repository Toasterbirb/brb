all: brb_test

brb_test: brb_test.cpp ../brb.a
	g++ -O2 -Wno-builtin-declaration-mismatch -nostdlib -nostdlib++ -I../include -o $@ $^

clean:
	rm ./brb_test

.PHONY: clean
