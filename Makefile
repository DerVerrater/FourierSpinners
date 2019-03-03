
OBJ_NAME = Series
OBJS = Spinner.cpp Series.cpp CircularBuffer.cpp Fourier.cpp Chain.cpp

CC=g++

CFLAGS = -w -lSDL2
LFLAGS = `sdl2-config --cflags --libs`

all: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LFLAGS) -o $(OBJ_NAME)