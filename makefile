# Compiler
CC = gcc

# Executable name
TARGET = bin/a

# Source and include directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Source files
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/indexbuffer.c $(SRC_DIR)/renderer.c $(SRC_DIR)/shader.c $(SRC_DIR)/vertexarray.c $(SRC_DIR)/vertexbuffer.c $(SRC_DIR)/vertexbufferlayout.c

# Object files (build directory + source file name with .o extension)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Detect the operating system
ifeq ($(OS), Windows_NT)
    # Windows-specific settings
    INCLUDES = -I$(INC_DIR)
    
    DYN_LIBS = 

    STATIC_LIBS = -lglew32 -lglfw3 -lopengl32 -lgdi32 -lglu32

    LDFLAGS = -L/ucrt64/lib -Wl,-Bdynamic $(DYN_LIBS) -Wl,-Bstatic $(STATIC_LIBS) -mwindows
else
    # Linux-specific settings
    INCLUDES = -I$(INC_DIR)
    LIBS = -lGLEW -lglfw -lGL -lGLU -lX11
    LDFLAGS = $(LIBS)
endif

# Compiler flags
CFLAGS = $(INCLUDES) -Wall -Wextra -O2

# Default rule
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

# Rule to compile source files into object files (with new paths)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure the build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean up build files
clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET)

# Rebuild the project
rebuild: clean all