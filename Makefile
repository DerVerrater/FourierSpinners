EXE = Series
SRCS = Spinner.cpp Series.cpp CircularBuffer.cpp Fourier.cpp Chain.cpp
OPTIMIZATION_LEVEL = "-O2"

CXXFLAGS += $(shell sdl2-config --cflags) $(OPTIMIZATION_LEVEL) -std=c++17
LDFLAGS += $(shell sdl2-config --libs)

.PHONY: all clean install

# target 'all' depends on the executable existing
all: $(EXE)

# The only build artefact at this time is the finished executable.
clean:
	rm $(EXE)

# Install the program into `/usr/bin/` according to the FHS
# `DESTDIR` is normally empty and will have no effect. It's for future Debian
# packaging (dpkg-buildpackage installs to a fake root, and uses that to do it)
install: $(EXE)
	install -o root -g root -m 755 -C -D $(DESTDIR)/usr/bin/Series

# the executable depends on the sources existing
$(EXE): $(SRCS)
	$(CXX) $(SRCS) $(CXXFLAGS) $(LDFLAGS) -o $@

