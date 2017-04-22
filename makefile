CXX = clang
CFLAGS = -Wall -g
LIBS = -lstdc++ --std=c++1z
SRC = main.cpp state.cpp player.cpp
BIN = smallworld

all:
	$(CXX) $(CFLAGS) $(LIBS) $$(sdl2-config --libs --cflags) -o $(BIN) $(SRC)

.PHONY: clean
clean:
	rm -f $(BIN)
