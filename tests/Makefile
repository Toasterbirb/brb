all: brb_test

brb_test: brb_test.cpp ../brb.a
	g++ -g -O0 -fno-stack-protector -Wno-builtin-declaration-mismatch -nostdlib -nostdlib++ -I../include -o $@ $^

clean:
	rm ./brb_test

.PHONY: clean
