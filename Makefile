# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I. -Iinclude -Isrc -Idraw -Ilogic
DEBUG_FLAGS = -g  # Debug flag for debugging builds
TARGET = dungeon

# Find all source files recursively
SRCS := $(shell find . -name '*.cpp')
OBJS := $(SRCS:.cpp=.o)

# PCH (Precompiled Header)
PCH = pch.h
PCHGCH = $(PCH).gch

# SDL2 flags
SDL_FLAGS = `sdl2-config --cflags --libs`
SDL_MIXER_FLAGS = `sdl2-config --cflags` -lSDL2_mixer

# If we are building for debugging, add -g flag
ifeq ($(DEBUG), 1)
    CXXFLAGS += $(DEBUG_FLAGS)
endif

# Default build target
build: $(TARGET)

# Link the final binary
$(TARGET): $(PCHGCH) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) -lncurses $(SDL_FLAGS) $(SDL_MIXER_FLAGS)

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -include $(PCH) -c $< -o $@

# Precompile the header
$(PCHGCH): $(PCH)
	$(CXX) $(CXXFLAGS) -x c++-header $(PCH) -o $(PCHGCH)

# Clean build
clean:
	rm -f $(TARGET) $(OBJS) $(PCHGCH)
