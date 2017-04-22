CXX = clang
CFLAGS = -Wall -g
LIBS = -lstdc++
SRC = main.cpp
BIN = smallworld

all:
	$(CXX) $(CFLAGS) $(LIBS) $$(sdl2-config --libs --cflags) -o $(BIN) $(SRC)

.PHONY: clean
clean:
	rm -f $(BIN)