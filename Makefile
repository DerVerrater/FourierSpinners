EXE = Series
SRCS = Spinner.cpp Series.cpp CircularBuffer.cpp Fourier.cpp Chain.cpp
OPTIMIZATION_LEVEL = "-O2"
CC=g++

CXXFLAGS = -w -lSDL2 $(OPTIMIZATION_LEVEL)
LDFLAGS = $(sdl2-config --cflags --libs)

# target 'all' depends on the executable existing
all: $(EXE)

# the executable depends on the sources existing
$(EXE): $(SRCS)
	$(CXX) $(SRCS) $(CXXFLAGS) $(LDFLAGS) -o $@

# for larger projects one would compile object files
# to selectively recompile and relink.
# Iterative builds and all

# Gen objects like so, and make target EXE depend on .o's instead of .cpp's
# $(OBJS): $(SRCS)
# 	$(CXX) $(SRCS) $(CXXFLAGS) -o $@ -c $<
