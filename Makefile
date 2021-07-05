CFLAGS  = `pkg-config --cflags sdl2`
LDFLAGS = `pkg-config --libs sdl2`

OBJECTS = \
	draw.o \
	event.o \
	main.o \
	init.o

all: game

game: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o game

clean:
	rm -f game
	rm -f $(OBJECTS)

PHONY: all game clean
