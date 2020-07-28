CC = g++
CFLAGS = -Wall -std=c++11 -I ./src
LDFLAGS = -lSDL2 -lSDL2_image

ifeq ($(DEBUG), yes)
	CFLAGS += -g
else
	CFLAGS += -O3
endif

EXEC = build/main
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)

build/%.o: build src/%.cpp
	@ echo "[building object files]"
	@ $(CC) $(CFLAGS) -c $< -o $@
	@ echo "[done]"

$(EXEC): $(OBJ)
	@ echo "[building executable]"
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@ echo "[done]"

build:
	@ echo "[creating build dir]"
	@ mkdir -p build/
	@ echo "[done]"

clean:
	rm -f build/*.o

mrproper: clean
	rm -f $(EXEC)