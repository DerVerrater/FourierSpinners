
OBJ_NAME = Series
OBJS = Spinner.cpp Series.cpp CircularBuffer.cpp Fourier.cpp Chain.cpp

CC=g++

CFLAGS = -w -lSDL2 -O1
LFLAGS = `sdl2-config --cflags --static-libs`

all: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LFLAGS) -o $(OBJ_NAME)