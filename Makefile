BIN=brb.a
PREFIX=/usr/local
INC_DIR=./include

CXX=g++
WARNINGS=-pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wsign-promo -Wstrict-null-sentinel -Wundef -Werror -Wno-unused
CXXFLAGS=-static --entry=__brb_start -Wno-builtin-declaration-mismatch -nostdlib -nostdlib++ -I$(INC_DIR) $(WARNINGS)
LDFLAGS=

SRC_FILES := $(wildcard ./src/*.cpp)

all: $(BIN)

$(BIN): ./*.o
	ar rvs $@ $^

%.o: ./src/%.cpp
	$(CXX) $(CXXFLAGS) -c $(LDFLAGS) $^

install:
	cp ./$(BIN) $(DESTDIR)$(PREFIX)/lib/
	cp -r $(INC_DIR) $(DESTDIR)$(PREFIX)/include/brb

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/$(BIN)
	rm -rf $(DESTDIR)$(PREFIX)/include/brb

clean:
	rm -f ./$(BIN) *.o

.PHONY: clean
