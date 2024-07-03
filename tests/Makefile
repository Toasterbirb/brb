all: brb_test

brb_test: brb_test.cpp ../brb.a
	g++ -fno-stack-protector -Wno-builtin-declaration-mismatch -nostdlib -nostdlib++ -I../include -o $@ $^

clean:
	rm ./brb_test

.PHONY: clean
