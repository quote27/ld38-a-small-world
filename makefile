CXX = clang
CFLAGS = -Wall -g --std=c++1z
LIBS = -lstdc++ -lSDL2_image
SRC = main.cpp state.cpp spritesheet.cpp player.cpp map.cpp entity.cpp camera.cpp interactable.cpp
BIN = smallworld

all:
	$(CXX) $(CFLAGS) $(LIBS) $$(sdl2-config --libs --cflags) -o $(BIN) $(SRC)

.PHONY: clean
clean:
	rm -f $(BIN)
