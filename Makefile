EXE = Series
SRC_DIR = .
BUILD_DIR = ./build

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
OPTIMIZATION_LEVEL = "-O2"

CXXFLAGS += $(shell sdl2-config --cflags) $(OPTIMIZATION_LEVEL) -std=c++17
LDFLAGS += $(shell sdl2-config --libs)

.PHONY: all clean install

# target 'all' depends on the executable existing
all: $(EXE)

# The only build artefact at this time is the finished executable.
clean:
	rm -f $(EXE)
	rm -rf $(BUILD_DIR)

# Install the program into `/usr/bin/` according to the FHS
# `DESTDIR` is normally empty and will have no effect. It's for future Debian
# packaging (dpkg-buildpackage installs to a fake root, and uses that to do it)
install: $(EXE)
	install -m 755 -C ./Series -D $(DESTDIR)/usr/bin/Series

# the executable depends on the sources existing
$(EXE): $(OBJS)
	$(CXX) $^ $(CXXFLAGS) $(LDFLAGS) -o $@

$(BUILD_DIR):
	mkdir $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
