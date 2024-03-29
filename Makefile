CFLAGS  = `pkg-config --cflags sdl2 sdl2_image`
LDFLAGS = `pkg-config --libs sdl2 sdl2_image`

OBJECTS = \
	draw.o \
	event.o \
	main.o \
	init.o \
	entity.o

all: game

game: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o game

clean:
	rm -f game
	rm -f $(OBJECTS)

PHONY: all game clean
