CFLAGS := -I/usr/include/SDL2 -D_REENTRANT -Wall -fPIC
LIBS := -lSDL2 -lGL

all:
	gcc main.c $(DEPS) -o main $(CFLAGS) $(LIBS)
	./main

clean:
	rm main
